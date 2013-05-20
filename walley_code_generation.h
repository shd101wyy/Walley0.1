//
//  walley_code_generation.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_calculation.h"
bool TABLE_FUNCTION=FALSE;
bool TABLE_VALUE_VAR_NAME=FALSE;





/*
 ===========================================================
 ===========================================================
 ===========================================================
 ===========      PRE CODE GENERATION        ===============
 ===========================================================
 ===========================================================
 ===========================================================
 
 */
int TEMP_OFFSET=0;
char *TEMP_VARS[]={
  "TEMP1","TEMP2"
};

char *getTEMP_VARS(int temp_offset){
    return TEMP_VARS[(temp_offset+2)%2];
}

void Pre_Code_Generation(Operation_List **ol, TREE tree){
    OPERATION op;
    //op.opcode=NULL;
    op.arg0=NULL;
    op.arg1=NULL;
    op.arg2=NULL;
    
    // walley_statements
    if (term(tree.name, "walley_statements")) {
        Node_List *nl=tree.node_list;
        while (nl!=NULL) {
            Pre_Code_Generation(ol, nl->node);
            nl=nl->next;
        }
        return;
    }
    
    // statements
    if (term(tree.name, "statements")) {
        Node_List *nl=tree.node_list;
        while (nl!=NULL) {
            Pre_Code_Generation(ol, nl->node);
            nl=nl->next;
        }
        return;
    }
    
    // =
    if (term(tree.name, "=")) {
        bool now_local=FALSE;
        TREE left;
        TREE right;
        if (term(tree.node_list->node.name, "local")) {
            now_local=TRUE;
            left=tree.node_list->next->node;
            right=tree.node_list->next->next->node;
        }
        else{
            left=tree.node_list->node;
            right=tree.node_list->next->node;
        }
        
        
        // x=12 kind.. not x["a"] kind
        // right side
        Pre_Code_Generation(ol, right);
        // left side
        char *var_name=left.name;
        
        // set
        if (now_local) {
            op.opcode=SETL;
        }
        else{
            op.opcode=SET;
        }
        op.arg0=var_name;
        op.arg1=getTEMP_VARS(TEMP_OFFSET);
        OL_append(ol, op);
    }
    
    // num /string /id
    if (term(tree.token_class, "num")||term(tree.token_class, "string")||term(tree.token_class, "id")) {
        op.opcode=SET;
        op.arg0=getTEMP_VARS(TEMP_OFFSET);
        op.arg1=tree.name;
        OL_append(ol, op);
        return;
    }
    // + - * /
    if (ism_operator(tree.name)) {
        
        TREE left=tree.node_list->node;
        TREE right=tree.node_list->next->node;
        
        // can calculate directly
        if ((term(left.token_class,"string")||term(left.token_class, "num"))
            && (term(right.token_class, "string")||term(right.token_class, "num"))
            ) {
            char *output=Walley_Calculation(left.name, right.name, tree.name);
            op.opcode=SET;
            op.arg0=getTEMP_VARS(TEMP_OFFSET);
            op.arg1=output;
            OL_append(ol, op);
            return;
        }
        else{
            if (term(tree.name, "+")) {
                op.opcode=ADD;
            }
            else if (term(tree.name, "-")) {
                op.opcode=SUB;
            }
            else if (term(tree.name, "*")) {
                op.opcode=MUL;
            }
            else if (term(tree.name, "/")) {
                op.opcode=DIV;
            }
            else if (term(tree.name, "%")) {
                op.opcode=MOD;
            }
            else if (term(tree.name, "^")) {
                op.opcode=POW;
            }
            else{
                printf("m_operator error\n");
                exit(0);
            }
            
            bool left_=ism_operator(left.name);
            bool right_=ism_operator(right.name);
            
            if (left_) {
                if (right_) {
                    Pre_Code_Generation(ol, left);
                    TEMP_OFFSET++;
                    Pre_Code_Generation(ol, right);
                    TEMP_OFFSET--;
                    op.arg0=getTEMP_VARS(TEMP_OFFSET);
                    op.arg1=getTEMP_VARS(TEMP_OFFSET);
                    op.arg2=getTEMP_VARS(TEMP_OFFSET+1);
                    
                }
                else{
                    Pre_Code_Generation(ol, left);
                    op.arg0=getTEMP_VARS(TEMP_OFFSET);
                    op.arg1=getTEMP_VARS(TEMP_OFFSET);
                    op.arg2=right.name;                
                }
            }
            else{
                if (right_) {
                    Pre_Code_Generation(ol, right);
                    op.arg0=getTEMP_VARS(TEMP_OFFSET);
                    op.arg1=left.name;
                    op.arg2=op.arg0;
                }
                else{
                    op.arg0=getTEMP_VARS(TEMP_OFFSET);
                    op.arg1=left.name;
                    op.arg2=right.name;
                }
            }
            OL_append(ol, op);
            return;
        }

    }
    
}

























// NOW I CAN ONLY GENERATE CODE FOR assignmnet
bool ism_operator(char *input_str){
    if (term(input_str, "+")
        ||term(input_str, "-")
        ||term(input_str, "*")
        ||term(input_str, "/")
        ||term(input_str,"^")
        ||term(input_str, "%")) {
        return TRUE;
    }
    return FALSE;
}


// input_str   12 num  --> #12
// input_str   x id   -->  0       $address of x
//                      none    $does not exist
void getValue(TREE tree, int *var_set_index, char **var_value){
    // check number first
    // then
    // check local first
    // then check Global
    if (term(tree.name, "none")) {
        
        *var_set_index=-1;
        *var_value="none";
        return;
    }
    if (term(tree.token_class, "num")||term(tree.token_class, "string")) {
        char *return_value=(char*)malloc(sizeof(char)*(2+(int)strlen(tree.name)));
        return_value[0]='#';
        int i=0;
        for (; i<(int)strlen(tree.name); i++) {
            return_value[i+1]=tree.name[i];
        }
        return_value[i+1]=0;
        *var_value=return_value;
        *var_set_index=-1;
        return;
    }
    else{
        
        Var_List_Set *temp_vls=LOCAL_VAR_SET;
        int length_of_temp_vls=VLS_length(temp_vls);
        int i=0;
        for (i=0; i<length_of_temp_vls; i++){
            Var_List *local_var_list=temp_vls->current_var_list;
            
            if (local_var_list->current_var.var_name!=NULL && local_var_list!=GLOBAL_VAR_LIST) {
                // check local
                while (local_var_list!=NULL) {
                    // find
                    if (term(local_var_list->current_var.var_name, tree.name)) {
                        *var_set_index=temp_vls->index;
                        *var_value=local_var_list->current_var.address;
                        return;
                    }
                    local_var_list=local_var_list->next;
                }
                
            }

            temp_vls=temp_vls->next;
        }
        
        
        Var_List *temp_GLOBAL_VAR_LIST=GLOBAL_VAR_LIST;
        if (temp_GLOBAL_VAR_LIST->current_var.var_name!=NULL) {
            // check global
            while (temp_GLOBAL_VAR_LIST!=NULL) {
                if (term(temp_GLOBAL_VAR_LIST->current_var.var_name, tree.name)) {
                    *var_set_index=0;
                    *var_value=temp_GLOBAL_VAR_LIST->current_var.address;
                    return;
                }
                temp_GLOBAL_VAR_LIST=temp_GLOBAL_VAR_LIST->next;
            }
            
        }
       
    }
    
    *var_set_index=-1;
    *var_value="none";
}

/*
 x=12 if x>3 then x=15 end
( walley_statements
    ( statements
        ( =(id x)(num 12))
    )
    ( statements
        ( if)
        ( simple_relation( <(num 3)(id x)))
        ( statements
            ( =(id x)(num 15))
        )
    )
    ( statements( end))
 )
 
 
 x=12 if x>=1 and x<20 then x=15 end
( walley_statements
    ( statements
        ( =(id x)(num 12))
    )
    ( statements
        ( if)
        ( relation
            (and
                ( simple_relation( <=(num 1)(id x)))
                ( simple_relation( <(id x)(num 20)))
            )
        )
        ( statements
            ( =(id x)(num 15))
        )
    )
    ( statements( end))
 )
 
 
 
 add = def (a,b) then return a+b end
 
 
( walley_statements
    ( statements
        ( =
            (id add)
            ( func_value
                ( def)
                ( params
                    (id a)
                    (id b)
                )
                ( statements
                    ( return( +(id a)(id b)))
                )
                ( end)
            )
        )
    )
 )
 
 
 def add(a,b) then return a+b end
 ( walley_statements
    ( statements
        ( =
            (id add)
            ( func_value
                ( def)
                ( params(id a)(id b))
                ( statements
                    ( return
                        ( +(id a)(id b))
                    )
                )
                ( end)
            )
        )
    )
)
 
 x=12 if x>3 then if x>4 then x=14 else x=15 end else x=1 end
 
 ( walley_statements
    ( statements
        ( =(id x)(num 12))
    )
    ( statements
        ( if)
        ( simple_relation( <(num 3)(id x)))
        ( statements
            ( if)
            ( simple_relation( <(num 4)(id x)))
            ( statements( =(id x)(num 14)))
        )
        ( statements
            ( else)
            ( statements( =(id x)(num 15)))
        )
        ( statements( end))
    )
    ( statements
        ( else)
        ( statements( =(id x)(num 1)))
    )
    ( statements( end))
 )
 
 */
void Code_Generation(TREE tree, Operation_List **ol, Function_List **fl){
    OPERATION op;
    op.arg0=NULL;
    op.arg1=NULL;
    op.arg2=NULL;
    op.value=NULL;
    

    
    int CURRENT_VAR_SET_INDEX=VLS_length(LOCAL_VAR_SET);
    //printf("current_var_set_index %d\n",CURRENT_VAR_SET_INDEX);
    
    bool NOW_LOCAL=FALSE;
    if (SL_length(STATEMENTS_LIST)!=0) {
        NOW_LOCAL=TRUE;
    }
    //printf("NOW_LOCAL %d\n",NOW_LOCAL);

    if (term(tree.name, "walley_statements")){
        Node_List *nl=tree.node_list;
        while (nl->next!=NULL) {
            Code_Generation(nl->node, ol,fl);
            nl=nl->next;
        }
        Code_Generation(nl->node, ol,fl);
        return ;

    }
    // statements..
    if (term(tree.name, "statements")) {
        Node_List *nl=tree.node_list;
        
        // while statements
        if (term(nl->node.name, "while")) {
            SL_addString(&STATEMENTS_LIST, "while");

            int current_while_index=OL_length(*ol);
            SL_addString(&WHILE_LIST_OL_INDEX, intToCString(current_while_index));
            
            // begin new local registers
            op.opcode=BEGINLOCAL;
            OL_append(ol, op);
            
            // begin new var set
            VLS_push(&LOCAL_VAR_SET);
            
            // backup local offset
            SL_addString(&LOCAL_OFFSET_LIST, intToCString(LOCAL_OFFSET));
            LOCAL_OFFSET=0;
            
            nl=nl->next;
            Code_Generation(nl->node, ol,fl);
            
            //finish dealing with relation and simple relation
            
            // meet TEST
            LOCAL_OFFSET--;
            op.opcode=TEST;
            op.arg0=intToCString(LOCAL_OFFSET);
            op.arg1=NULL;
            op.arg2=NULL;
            OL_append(ol, op);
            
            LOCAL_OFFSET++;
            
            // run next statements
            nl=nl->next;
            while (nl!=NULL) {
                Code_Generation(nl->node, ol,fl);
                nl=nl->next;
            }
            
            return;
        }
        // if statements
        else if (term(nl->node.name, "if")) {
            SL_addString(&STATEMENTS_LIST, "if");
            printf("ADD If\n");

            
            // begin new local registers
            op.opcode=BEGINLOCAL;
            OL_append(ol, op);
            
            // begin new var set
            VLS_push(&LOCAL_VAR_SET);

            // backup local offset
            SL_addString(&LOCAL_OFFSET_LIST, intToCString(LOCAL_OFFSET));
            LOCAL_OFFSET=0;
            
            // run next relation statements or simple_relation statements
            nl=nl->next;
            Code_Generation(nl->node, ol,fl);
            
            //finish dealing with relation and simple relation
            
            // meet TEST
            LOCAL_OFFSET--;
            op.opcode=TEST;
            op.arg0=intToCString(LOCAL_OFFSET);
            OL_append(ol, op);
            
            LOCAL_OFFSET++;
            
            
            // run next statements
            nl=nl->next;
            while (nl!=NULL) {
                Code_Generation(nl->node, ol,fl);
                nl=nl->next;
            }
            
            return;
            
        }
        /*
         x=1 if x>0 then x=2 elif x<10 then x=5 end
         ( walley_statements
            ( statements
                ( =(id x)(num 1))
            )
            ( statements
                ( if)
                ( simple_relation( <(num 0)(id x)))
                ( statements
                    ( =(id x)(num 2))
                )
            )
            ( statements
                ( elif)
                ( simple_relation( <(id x)(num 10)))
                ( statements( =(id x)(num 5)))
            )
            ( statements( end))
        )

         
         */
        // elif statements
        else if (term(nl->node.name, "elif")){
            
            // pop ahead
            SL_pop(&STATEMENTS_LIST);
            // push elif
            SL_addString(&STATEMENTS_LIST, "elif");
            
            
            
            // jmp back
            int jump_final=OL_length(*ol);
            Operation_List **temp_ol=&(*ol);
            while ((*temp_ol)->next!=NULL) {
                temp_ol=&((*temp_ol)->next);
            }
            while ((*temp_ol)->ahead!=NULL) {
                if ((*temp_ol)->operation.opcode==TEST && (*temp_ol)->operation.arg1==NULL) {
                    (*temp_ol)->operation.arg1=intToCString(jump_final-(*temp_ol)->current_index);
                    break;
                }
                temp_ol=&((*temp_ol)->ahead);
            }
            
            
            
            // free local registers
            op.opcode=FREELOCAL;
            OL_append(ol, op);
            
            // pop var set
            VLS_pop(&LOCAL_VAR_SET);
            
            // begin new local registers
            op.opcode=BEGINLOCAL;
            OL_append(ol, op);
            
            // begin new var set
            VLS_push(&LOCAL_VAR_SET);

            LOCAL_OFFSET=0;
           

            
            // parse judge_statements
            nl=nl->next;
            Code_Generation(nl->node, ol,fl);
            
                    
            //finish dealing with relation and simple relation
            
            // meet TEST
            LOCAL_OFFSET--;
            op.opcode=TEST;
            op.arg0=intToCString(LOCAL_OFFSET);
            OL_append(ol, op);
            
            LOCAL_OFFSET++;
            
            // run next statements
            nl=nl->next;
            while (nl!=NULL) {
                Code_Generation(nl->node, ol,fl);
                nl=nl->next;
            }

            return;
        }
        
        /*
         
         x=12 if x>1 then x=11 else x=15 end
        ( walley_statements
            ( statements
                ( =(id x)(num 12))
            )
            ( statements
                ( if)
                ( simple_relation( <(num 1)(id x)))
                ( statements( =(id x)(num 11)))
            )
            ( statements
                ( else)
                ( statements( =(id x)(num 15)))
            )
            ( statements
                ( end)
            )
         )
         
         */
        else if (term(nl->node.name, "else")){
            
            
            // pop ahead
            SL_pop(&STATEMENTS_LIST);
            // push else
            SL_addString(&STATEMENTS_LIST, "else");
            
                    
            // jmp back
            int jump_final=OL_length(*ol);
            Operation_List **temp_ol=&(*ol);
            while ((*temp_ol)->next!=NULL) {
                temp_ol=&((*temp_ol)->next);
            }
            while ((*temp_ol)->ahead!=NULL) {
                if ((*temp_ol)->operation.opcode==TEST && (*temp_ol)->operation.arg1==NULL) {
                    (*temp_ol)->operation.arg1=intToCString(jump_final-(*temp_ol)->current_index);
                    break;
                }
                temp_ol=&((*temp_ol)->ahead);
            }
            
            
            // free local registers
            //op.opcode=FREELOCAL;
            //OL_append(ol, op);
            
            // begin new local registers
            //op.opcode=BEGINLOCAL;
            //OL_append(ol, op);

            // begin new var set
            //VLS_push(&LOCAL_VAR_SET);
          
            LOCAL_OFFSET=0;
            
            
            temp_ol=&((*temp_ol)->ahead);
            op.opcode=NOT;
            op.arg0=(*temp_ol)->operation.arg0;
            op.arg1=NULL;
            OL_append(ol, op);
            
            op.opcode=TEST;
            op.arg0=(*temp_ol)->operation.arg0;
            op.arg1=NULL;
            OL_append(ol, op);
            
            //finish dealing with relation and simple relation
            //GLOBAL_OFFSET++;
            
            // run next statements
            nl=nl->next;
            while (nl!=NULL) {
                Code_Generation(nl->node, ol, fl);
                nl=nl->next;
            }
            
        
            return;
        }
        
        else{
            while (nl->next!=NULL) {
                Code_Generation(nl->node, ol,fl);
                nl=nl->next;
            }
            Code_Generation(nl->node, ol,fl);
            return ;
        }
    }
    
    /*
     add = def (a,b) then return a+b end
     ( walley_statements
        ( statements
            ( =
                (id add)
                ( func_value
                    ( def)
                    ( params(id a)(id b))
                    ( statements
                        ( return( +(id a)(id b)))
                    )
                    ( end)
                )
            )
        )
    )
     
     */
    
    /*
     return a+b
     ( return
        ( +
            (id a)
            (id b)
        )
     )
     */
    if (term(tree.name, "return")){
        if (NOW_LOCAL==FALSE) {
            Walley_Print_Error(CURRENT_INPUT_STR, "cannot return value in global scopr", 0);
        }
        
        printf("FIND RETURN\n");
        TREE_print(tree);
        
        Node_List *nl=tree.node_list;
        while (nl!=NULL) {
            Code_Generation(nl->node, ol, fl);
            nl=nl->next;
        }
        
        LOCAL_OFFSET-=1;
        
        // RETURN opcode
        op.opcode=RETURN;
        op.arg0=intToCString(LOCAL_OFFSET);
        OL_append(ol, op);
        
        
        LOCAL_OFFSET+=1;
        
        
        
    }
    if (term(tree.name, "func_value")) {
        printf("FUNC_VALUE\n");
        printf("Begin to Define a function\n");
        /*
         ( func_value
            ( def)
            ( params(id a)(id b))
            ( statements
                ( return( +(id a)(id b)))
            )
            ( end)
         )
         
         */
        
        // push def
        SL_addString(&STATEMENTS_LIST, "def");
        
        // begin new var set
        VLS_push(&LOCAL_VAR_SET);
        
        // backup local offset
        SL_addString(&LOCAL_OFFSET_LIST, intToCString(LOCAL_OFFSET));
        LOCAL_OFFSET=0;
        
        
              
        // add func_name
        // add nothing
        FL_addFuncName(fl, "");
                
        /*
         ====== NODE IN SIDE =====
         add = def(a,b) then return a+b end m= def (a,b) then return a-b end
         
         ( walley_statements
            ( statements
                ( =
                    (id add)
                    ( func_value
                        ( def)
                        ( params(id a)(id b))
                        ( statements
                            ( return( +(id a)(id b)))
                        )
                        ( end)
                    )
                )
            )
            ( statements
                ( =
                    (id m)
                    ( func_value
                        ( def)
                        ( params(id a)(id b))
                        ( statements
                            ( return( -(id a)(id b)))
                        )
                        ( end)
                    )
                )
            )
         )
         ====== INSIDE ======
         add = def (a,b) then m = def(a,b) then return a-b end return a+b end
         ( walley_statements
            ( statements
                ( =
                    (id add)
                    ( func_value
                        ( def)
                        ( params(id a)(id b))
                        ( statements
                            ( =
                                (id m)
                                ( func_value
                                    ( def)
                                    ( params(id a)(id b))
                                    ( statements( return( -(id a)(id b))))
                                    ( end)
                                )
                            )
                        )
                        ( statements
                            ( return( +(id a)(id b)))
                        )
                        ( end)
                    )
                )
            )
         )
         add = def (a,b) then m = def(a,b) then return a-b end time = def (a,b) then return a*b end return a+b end
         */
        
        printf("FL_LENGTH---_> %d\n",FL_length(*fl));
        
        // pointer FL
        // get current available functin list
        Function_List **current_fl=&(*fl);
        while ((*current_fl)->next!=NULL) {
            current_fl=&((*current_fl)->next);
        }
        
        printf("CURRENT_ADDRESS===== %p\n",&(*current_fl));
        
        char *current_fl_address_string=(char*)malloc(sizeof(char)*100);
        sprintf(current_fl_address_string, "%p",&(*current_fl));
        printf("CURRENT_ADDRESS STRING===== %s\n",current_fl_address_string);

        /*
         
         Function_List **current_fl;
         sscanf(current_fl_address_string,"%p",&current_fl)
         to get back
         
         */
        
        
        // init function inside function_list
        FL_init(&((*current_fl)->next_in_function));
        
        
        OL_init(&((*current_fl)->current_ol));
        
        // init func id
        char *func_id=append("f", intToCString(FUNC_ID));
        FUNC_ID++;
        
        // begin new func
        op.opcode=BEGINFUNC;
        op.arg0=func_id;
        OL_append(&((*current_fl)->current_ol), op);
        
        // begin new local registers
        op.opcode=BEGINLOCAL;
        op.arg0=NULL;
        OL_append(&((*current_fl)->current_ol), op);

        
        
        TREE param_tree=tree.node_list->next->node;
        int params_num=NL_length(param_tree.node_list);
        
        Node_List *params_nl=param_tree.node_list;
        //add params to local var list and local operation list;
        int i=0;
        for (; i<params_num; i++) {
            char *param_name=params_nl->node.name;
            // assignment param
            if (term(param_name, "=")) {                
                
                // change params to local
                // add = def (a=3) then return a=3
                // change 'a=3' to 'local a=3'
                TREE temp_tree;
                TREE_initWithName(&temp_tree, "=");
                TREE_addNode(&temp_tree, "local", "");
                
                Node_List *temp_nl=params_nl->node.node_list;
                while (temp_nl!=NULL) {
                    TREE_addNode(&temp_tree, temp_nl->node.name, temp_nl->node.token_class);
                    temp_nl=temp_nl->next;
                }
                
                

                
                // this place has problem
                //Code_Generation(temp_tree, &((*fl)->current_ol), &((*fl)->next_in_function));
                Code_Generation(temp_tree, &((*current_fl)->current_ol), &((*current_fl)->next_in_function));
            
            }
            
            // default params
            // set none to them
            // eg add = def(a,b) then return a+b end... set a=none b=none
            else{
                

                // add to local var list
                Var param_var;
                param_var.address=intToCString(LOCAL_OFFSET);
                param_var.var_name=param_name;
                VL_addVar(VLS_finalVL(&LOCAL_VAR_SET), param_var);
                
                // add to local operation list
                OPERATION temp_op;
                temp_op.opcode=SETL;
                temp_op.arg0=intToCString(LOCAL_OFFSET);
                temp_op.arg1="none";
                temp_op.arg2=NULL;
                temp_op.value=param_name;
                OL_append(&((*current_fl)->current_ol), temp_op);
                
                
                LOCAL_OFFSET++;
                 
            }
            params_nl=params_nl->next;
            
        }
        
        
        // FINISH INITIALIZE PARAMS
        op.opcode=ENDPARAMS;
        OL_append(&((*current_fl)->current_ol), op);
        
        // run next statements
        Node_List *temp_nl=tree.node_list->next->next;
        while (temp_nl!=NULL) {
            Code_Generation(temp_nl->node,  &((*current_fl)->current_ol), &((*current_fl)->next_in_function));
            temp_nl=temp_nl->next;
        }
        
        
        // add function to ol
        Operation_List *ol_func=(*current_fl)->current_ol;
        while (ol_func!=NULL) {
            OL_append(ol, ol_func->operation);
            ol_func=ol_func->next;
        }
       

        
        // set func_index
        // local
        if (NOW_LOCAL) {
            
            op.opcode=SETL;
            
            op.arg0=intToCString(LOCAL_OFFSET);
            
            //op.arg1=current_fl_address_string;
            op.arg1=func_id;

            
            op.arg2=NULL;
            
            LOCAL_OFFSET++;
            OL_append(ol, op);
        }
        // global
        else{
            op.opcode=SETG;
            op.arg0=intToCString(GLOBAL_OFFSET);
            
            //op.arg1=current_fl_address_string;
            op.arg1=func_id;

            op.arg2=NULL;
            
            GLOBAL_OFFSET++;
            OL_append(ol, op);
        }
        
        
        printf("NOW HERE=======\n");
        printf("FL==========\n");
        FL_print(*fl);
        printf("OL==========\n");
        OL_print(*ol);
        exit(0);
        
        return;
        
        
    }
    
    
    // end
    if (term(tree.name, "end")){

        
        // restore LOCAL_OFFSET
        LOCAL_OFFSET=atoi(SL_pop(&LOCAL_OFFSET_LIST));
        
        
        // only support if elif else while now
        // need to check poped statement...
        SL_print(STATEMENTS_LIST);
        // pop ahead
        char *stm=SL_pop(&STATEMENTS_LIST);
        if (term(stm, "while")) {
            // end local registers
            op.opcode=FREELOCAL;
            OL_append(ol, op);
            
            // pop var set
            VLS_pop(&LOCAL_VAR_SET);
            
            char *jmp_num_str=SL_pop(&WHILE_LIST_OL_INDEX);
            op.opcode=JMP;
            op.arg0=intToCString(-1*((OL_length(*ol)-atoi(jmp_num_str))));
            OL_append(ol, op);
            
            // jmp back
            int jump_final=OL_length(*ol);
            Operation_List **temp_ol=&(*ol);
            
            while ((*temp_ol)->next!=NULL) {
                temp_ol=&((*temp_ol)->next);
            }
            
            while ((*temp_ol)->ahead!=NULL) {
                if ((*temp_ol)->operation.opcode==TEST && (*temp_ol)->operation.arg1==NULL) {
                    (*temp_ol)->operation.arg1=intToCString(jump_final-(*temp_ol)->current_index);
                    break;
                }
                temp_ol=&((*temp_ol)->ahead);
            }
            
        }
        else if(term(stm, "def")){
            printf("Finish defining function\n");
            
            // free local registers
            op.opcode=FREELOCAL;
            OL_append(ol, op);
            // end defining func
            op.opcode=ENDFUNC;
            OL_append(ol, op);
            

            // pop var set
            VLS_pop(&LOCAL_VAR_SET);
            
            
            if (STATEMENTS_LIST->string_content!=NULL) {
                
                // check whether finish all function define..
                Str_List *temp_sl=STATEMENTS_LIST;
                int length_of_temp_sl=SL_length(temp_sl);
                int i=0;
                NOW_FUNCTION=FALSE;
                for (; i<length_of_temp_sl; i++) {
                    if (term(temp_sl->string_content, "def")) {
                        NOW_FUNCTION=TRUE;
                        break;
                    }
                    temp_sl=temp_sl->next;
                }
                
            }
            else{
                NOW_FUNCTION=FALSE;
            }
            
            
        }
        else{
            // if elif else sentences
            
            // end local registers
            op.opcode=FREELOCAL;
            OL_append(ol, op);
            
            // pop var set
            VLS_pop(&LOCAL_VAR_SET);
            
            // jmp back
            int jump_final=OL_length(*ol)-1;
            Operation_List **temp_ol=&(*ol);
            
            while ((*temp_ol)->next!=NULL) {
                temp_ol=&((*temp_ol)->next);
            }
            
            while ((*temp_ol)->ahead!=NULL) {
                if ((*temp_ol)->operation.opcode==TEST && (*temp_ol)->operation.arg1==NULL) {
                    (*temp_ol)->operation.arg1=intToCString(jump_final-(*temp_ol)->current_index);
                    break;
                }
                temp_ol=&((*temp_ol)->ahead);
            }
        }
        return;
        
    }
    
    if (term(tree.name, "func")) {
        
        /*
            add = def (a,b) then return a+b end
            minus = def(a,b) then return a-b end
            minus(3,4)
         
         
         */
        
        TREE func_tree=tree.node_list->node;
        char *func_name=func_tree.name;
        TREE param_tree=tree.node_list->next->node;
        Node_List *param_nl=param_tree.node_list;
        
        printf("FUNC_NAME----> |%s|\n",func_name);
        TREE_print(param_tree);
        
        char *func_address;
        int var_set_index;
        getValue(func_tree,&var_set_index,&func_address);
    
        printf("func_address %s\n",func_address);
    
        
        
        if (term(func_address, "none")) {
            
            // it is function in table
            // which can not be judged whether existed or not now
            if (TABLE_FUNCTION==TRUE) {
                
                
                // empty func_name
                /*
                 
                 ( func
                    (table_call 
                        (string "a")
                    )
                    ( params(id c)(id d))
                 )
                 */
                if ((int)strlen(func_name)==0) {
                    Code_Generation(tree.node_list->node.node_list->node, ol, fl);
                    if (NOW_LOCAL) {
                        //LOCAL_OFFSET--;
                        func_address=intToCString(LOCAL_OFFSET-1);
                    }
                    else{
                        //GLOBAL_OFFSET--;
                        func_address=intToCString(GLOBAL_OFFSET-1);
                    }
                }
                else{
                    func_address=func_name;
                }
            }
            else{
                printf("\nError..undefined function | %s |\n",func_name);
                exit(0);
            }
        }
        else{
            func_address=append("f", func_address);
        }
        
        
        
        int num_of_params=NL_length(param_nl);
        printf("num_of_params ---> %d\n",num_of_params);
        
        // save offset
        int current_offset;
        if (NOW_LOCAL) {
            current_offset=LOCAL_OFFSET;
        }
        else{
            current_offset=GLOBAL_OFFSET;
        }
        
        while (param_nl!=NULL) {
            Code_Generation(param_nl->node, ol, fl);
            param_nl=param_nl->next;
        }
        
        
        // call function
        op.opcode=CALL;
        op.arg0=func_address;
        op.arg1=intToCString(current_offset);
        op.arg2=intToCString(num_of_params);
        op.value=func_name;
        
        OL_append(ol, op);
        
        // restore offset
        if (NOW_LOCAL) {
            LOCAL_OFFSET=current_offset+1;
        }
        else{
            GLOBAL_OFFSET=current_offset+1;
        }

    }
    
    //simple_relation
    if (term(tree.name, "simple_relation")) {
        TREE temp_tree=tree.node_list->node;
        Node_List *nl=temp_tree.node_list;
        int length_of_nl=NL_length(nl);
        int i=0;
        for (; i<length_of_nl; i++) {
            Code_Generation(nl->node, ol,fl);
            nl=nl->next;
        }
       
        
        LOCAL_OFFSET-=2;
        char *judge_sign=temp_tree.name;
        if (term("<=", judge_sign)) {
            op.opcode=LE;
        }
        else if (term("<", judge_sign)){
            op.opcode=LT;
        }
        else if (term("==",judge_sign)){
            op.opcode=EQ;
        }
        else{
            printf("Judge Sign Error\n");
            exit(0);
        }
        op.arg0=intToCString(LOCAL_OFFSET);
        op.arg1=intToCString(LOCAL_OFFSET);
        op.arg2=intToCString(LOCAL_OFFSET+1);
        LOCAL_OFFSET++;
        
        OL_append(ol, op);
        return;
    }
       
    // relation
    if (term(tree.name, "relation")) {
        TREE temp_tree=tree.node_list->node;
        Node_List *nl=temp_tree.node_list;
        int length_of_nl=NL_length(nl);
        int i=0;
        for (; i<length_of_nl; i++) {
            Code_Generation(nl->node, ol,fl);
            nl=nl->next;
        }
        
        LOCAL_OFFSET-=2;
        if (term(temp_tree.name, "and")) {
            op.opcode=AND;
            op.arg0=intToCString(LOCAL_OFFSET);
            op.arg1=intToCString(LOCAL_OFFSET);
            op.arg2=intToCString(LOCAL_OFFSET+1);
        }
        else if (term(temp_tree.name, "or")){
            op.opcode=OR;
            op.arg0=intToCString(LOCAL_OFFSET);
            op.arg1=intToCString(LOCAL_OFFSET);
            op.arg2=intToCString(LOCAL_OFFSET+1);
        }
        else if (term(temp_tree.name, "not")){
            LOCAL_OFFSET++;
            op.opcode=NOT;
            op.arg0=intToCString(LOCAL_OFFSET);
        }
        else{
            printf("Relation Error %s\n",temp_tree.name);
        }
        
        OL_append(ol, op);
        
        LOCAL_OFFSET++;
        return;
    }
    
    // num or string
    if (term(tree.token_class, "num")||term(tree.token_class, "string")) {
        // local
        if (NOW_LOCAL) {
            
            op.opcode=SETL;
            
            op.arg0=intToCString(LOCAL_OFFSET);
            
            int var_set_index;
            char *var_value;
            getValue(tree, &var_set_index, &var_value);
            op.arg1=var_value;
            
            op.arg2=NULL;
            
            op.value=var_value;
            
            LOCAL_OFFSET++;
            OL_append(ol, op);
        }
        // global
        else{
            op.opcode=SETG;
            op.arg0=intToCString(GLOBAL_OFFSET);
        
            int var_set_index;
            char *var_value;
            getValue(tree, &var_set_index, &var_value);
            op.arg1=var_value;
        
            op.arg2=NULL;
            
            op.value=var_value;
        
            GLOBAL_OFFSET++;
            OL_append(ol, op);
        }
        return;

    }
    // id
    if (term(tree.token_class, "id")) {
        
        // local
        if (NOW_LOCAL) {
            
            int var_set_index;
            char *var_value;
            getValue(tree, &var_set_index, &var_value);
                        
            // does not exist
            if (var_set_index==-1) {
                op.opcode=SETL;
                op.arg0=intToCString(LOCAL_OFFSET);
                op.arg1="none";
                op.value=tree.name;

                
                LOCAL_OFFSET++;
                OL_append(ol, op);

            }
            // exist and
            // is current var set
            else if(CURRENT_VAR_SET_INDEX==var_set_index){
                op.opcode=SETL;
                op.arg0=intToCString(LOCAL_OFFSET);
                op.arg1=var_value;
                op.value=tree.name;

                
               LOCAL_OFFSET++;
                OL_append(ol, op);
            }
            // exist
            // but is not current var set
            else{
                op.opcode=SET;
                op.arg0=intToCString(var_set_index);
                op.arg1=intToCString(LOCAL_OFFSET);
                op.arg2=var_value;
                op.value=tree.name;

                
                LOCAL_OFFSET++;
                OL_append(ol, op);
            }
            
        }
        // global
        else{
            op.opcode=SETG;
            op.arg0=intToCString(GLOBAL_OFFSET);
            
            int var_set_index;
            char *var_value;
            getValue(tree, &var_set_index, &var_value);
            op.arg1=var_value;
            
            op.arg2=NULL;
            
            op.value=tree.name;
            
            GLOBAL_OFFSET++;
            OL_append(ol, op);
        }
        return;
    }
    // value
    if (term(tree.name, "value")) {
        Code_Generation(tree.node_list->node, ol,fl);
        return;
    }
    // table
    if (term(tree.token_class, "table")) {
        
        VLS_push(&TABLE_SET);
        
        if (NOW_LOCAL) {
            op.opcode=NEWTABLE;
            
            op.arg0=intToCString(LOCAL_OFFSET);
            op.arg1=append("t", intToCString(TABLE_INDEX));
            TABLE_INDEX++;
            
            
            //op.arg0=intToCString(LOCAL_OFFSET);
            op.value=tree.name;
            OL_append(ol, op);
            //LOCAL_OFFSET++;
        }
        else{
            op.opcode=NEWTABLE;
            
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1=append("t", intToCString(TABLE_INDEX));
            TABLE_INDEX++;
            
            //op.arg0=intToCString(GLOBAL_OFFSET);
            op.value=tree.name;
            OL_append(ol, op);
            //GLOBAL_OFFSET++;
        }
        
        Node_List *nl=tree.node_list;
        int i=0;
        int length_of_nl=NL_length(nl);
        for (; i<length_of_nl; i++) {
            Code_Generation(nl->node, ol,fl);
            nl=nl->next;
        }
        
        op.opcode=ENDTABLE;
        op.arg0=NULL;
        op.arg1=NULL;
        op.arg2=NULL;
        OL_append(ol, op);
        return;
    }
    
    /*
     
     x=[1,2]
     ( walley_statements
        ( statements
            ( =
                (id x)
                (table [1,2]
                    ( table_expr
                        ( key(num 0))
                        (num 1)
                    )
                    ( table_expr
                        ( key(num 1))
                        (num 2)
                    )
                )
            )
        )
     )
     
     */
    //table_expr
    if (term(tree.name, "table_expr")) {
        TREE value_tree=tree.node_list->next->node;
        
        // value
        
        // table
        if (value_tree.node_list!=NULL && term(value_tree.node_list->node.token_class,"table")) {
            Code_Generation(value_tree, ol,fl);
        }
        // not table
        else{
            
            Var_List **table_vl=VLS_finalVL(&TABLE_SET);
            int length_of_table_vl=VL_length(*table_vl);
            int address_that_need_to_add=length_of_table_vl;
            
            TREE key_tree=tree.node_list->node.node_list->node;
            
            if (term(key_tree.token_class, "num")==FALSE&&term(key_tree.token_class, "string")==FALSE) {
                Walley_Print_Error("", "Error.. invalid way of initing table\ninvalid key", 0);
            }
            
            char *key_name=key_tree.name;
            
            // access key tree
            Code_Generation(key_tree, ol, fl);
            
            
            Code_Generation(value_tree, ol,fl);
        // add value
            // local
            if (NOW_LOCAL) {
                LOCAL_OFFSET--;
                op.opcode=TADD;
                op.arg0=intToCString(LOCAL_COUNT-1);
                op.arg1=intToCString(LOCAL_OFFSET);
                
                OL_append(ol, op);
                
                // add var to table_vl;
                Var key_var;
                key_var.var_name=key_name;
                key_var.address=intToCString(address_that_need_to_add);
                VL_addVar(table_vl, key_var);
                
                

            }
            // global
            else{
                GLOBAL_OFFSET--;
                op.opcode=TADD;
                op.arg0=intToCString(GLOBAL_OFFSET-1);
                op.arg1=intToCString(GLOBAL_OFFSET);
                
                OL_append(ol, op);
                
                // add var to table_vl;
                Var key_var;
                key_var.var_name=key_name;
                key_var.address=intToCString(address_that_need_to_add);
                VL_addVar(table_vl, key_var);
            }
            
            VL_printVL(*table_vl);
            
        }
    }
    
    // table_value
    // valid form is only
    // id '.' ...
    //  ! first must be
    //  !   id
    if (term(tree.name, "table_value")) {
        TABLE_FUNCTION=TRUE;
        
        printf("table_value\n");
        if (term(tree.node_list->node.token_class, "id")==FALSE) {
            Walley_Print_Error("", "invalid table_value\n", 0);
        }
        char *var_name=tree.node_list->node.name;
        if (term(var_name, "table")||term(var_name, "string")) {
            printf("Error.. Buildin functions are still under development");
            exit(0);
        }
        char *var_value;
        int var_set;
        
        getValue(tree.node_list->node, &var_set, &var_value);
        
        printf("VAR_VALUE ---> %s\n",var_value);
        printf("VAR_SET -----> %d\n",var_set);
        
        // does not exist
        if (var_set==-1) {
            printf("Error.. %s does not exist\n",var_name);
            exit(0);
        }
        
        op.opcode=TABLESTART;
        op.arg0=var_value;
        if (NOW_LOCAL) {
            op.arg1=intToCString(LOCAL_OFFSET);
            LOCAL_OFFSET++;
        }
        else{
            op.arg1=intToCString(GLOBAL_OFFSET);
            GLOBAL_OFFSET++;
        }
        OL_append(ol, op);
        op.arg1=NULL;
        
        if (TABLE_VALUE_VAR_NAME) {
            op.opcode=TABLEENTER;
        }
        else{
            op.opcode=TABLEGET;
        }
        
        Node_List *key_nl=tree.node_list->next;
        while (key_nl!=NULL) {
            // deal with key
            TREE key_tree=key_nl->node;
            
            
            Code_Generation(key_tree, ol, fl);
            if (NOW_LOCAL) {
                LOCAL_OFFSET--;
                op.arg0=intToCString(LOCAL_OFFSET);
               
            }
            else{
                GLOBAL_OFFSET--;
                op.arg0=intToCString(GLOBAL_OFFSET);
               
            }
            OL_append(ol, op);
        
            
            key_nl=key_nl->next;
        }
        
        
        op.opcode=ENDTABLE;
        op.arg0=NULL;
        op.arg1=NULL;
        OL_append(ol, op);
        
        
        printf("======HERE\n");
        OL_print(*ol);
        
        TABLE_FUNCTION=FALSE;
        //exit(0);
    }
    // key
    if (term(tree.name, "key")) {
        Code_Generation(tree.node_list->node, ol, fl);
        return;
    }
    
    // global
    if (term(tree.name, "=")) {
        
        // x=12+3
        Node_List *nl=tree.node_list;
        int length_of_nl=NL_length(nl);
        
        // eg
        // x=12         # x is available
        // local y=12   # y is not available
        // can not assign local inside global scope
        if (term(nl->node.name, "local") && CURRENT_VAR_SET_INDEX==0) {
            return;
        }
        if (term(nl->node.name, "local")) {
            printf("### IS LOCAL\n");
            IS_LOCAL_VAR=TRUE;
            nl=nl->next;
        }
        else{
            IS_LOCAL_VAR=FALSE;
        }
        //NL_print(nl);
        // x=12+3
        if (length_of_nl==2||(length_of_nl==3&&IS_LOCAL_VAR)) {
            bool need_to_restore_offset_due_to_table_value_var_name=FALSE;
            // global
            // so OFFSET == GLOBAL_OFFSET
            if (NOW_LOCAL==FALSE) {
                char *var_name_address; 
                int var_set_index;
                getValue(nl->node, &var_set_index, &var_name_address);
                
                //printf("var_set_index %d    var_name_adderss %s\n",var_set_index,var_name_address);
                
                int current__offset=GLOBAL_OFFSET;
                int value__offset=GLOBAL_OFFSET;
                
                
                // table_value_var_name
                if (term(nl->node.name, "table_value")) {
                    printf("table_value var name\n");
                    TABLE_VALUE_VAR_NAME=TRUE;
                    Code_Generation(nl->node, ol, fl);
                    TABLE_VALUE_VAR_NAME=FALSE;
                    need_to_restore_offset_due_to_table_value_var_name=TRUE;
                    value__offset++;
                }
                // var does not exist
                else if (term(var_name_address, "none")) {
                    current__offset=GLOBAL_OFFSET;
                    op.opcode=SETG;
                    
                    op.arg0=intToCString(current__offset);
                    op.arg1="none";
                    op.value=nl->node.name;

                    
                    OL_append(ol, op);
                    
                    Var temp_var;
                    temp_var.address=intToCString(current__offset);
                    temp_var.var_name=nl->node.name;
                    
                    printf("var_name %s   address %s\n",nl->node.name,intToCString(current__offset));
                    
                    VL_addVar(&GLOBAL_VAR_LIST, temp_var);
                    
                    
                    GLOBAL_OFFSET++;
                    value__offset=GLOBAL_OFFSET;
                }
                // var exist
                else{
                    printf("EXIST");
                    current__offset=atoi(var_name_address);
                    value__offset=GLOBAL_OFFSET;
                }
                
                
                
                
                // right side
                Code_Generation(nl->next->node, ol,fl);
                op.opcode=SETG;
                
                op.arg0=intToCString(current__offset);
                op.arg1=intToCString(value__offset);
                op.value=nl->node.name;
                
                OL_append(ol, op);
                
                GLOBAL_OFFSET=value__offset;
                
            }
            
            // local
            else{
                // local y=12
                if (IS_LOCAL_VAR) {
                    char *var_name_address;
                    int var_set_index;
                    getValue(nl->node, &var_set_index, &var_name_address);
                    
                    int var_name_offset=LOCAL_OFFSET;
                    int var_value_offset=LOCAL_OFFSET;
                    
                    
                    // table_value_var_name
                    if (term(nl->node.name, "table_value")) {
                        printf("table_value var name\n");
                        TABLE_VALUE_VAR_NAME=TRUE;
                        Code_Generation(nl->node, ol, fl);
                        TABLE_VALUE_VAR_NAME=FALSE;
                        need_to_restore_offset_due_to_table_value_var_name=TRUE;

                    }
                    // same var exist in local registers
                    else if (var_set_index==CURRENT_VAR_SET_INDEX) {
                        var_name_offset=atoi(var_name_address);
                        var_value_offset=LOCAL_OFFSET;
                    }
                    // var does not exist in that local registers
                    else{
                        var_name_offset=LOCAL_OFFSET;
                        
                        op.opcode=SETL;
                        op.arg0=intToCString(LOCAL_OFFSET);
                        op.arg1="none";
                        op.value=nl->node.name;
                        
                        OL_append(ol, op);
                        
                        LOCAL_OFFSET++;
                        var_value_offset=LOCAL_OFFSET;
                        
                        Var temp_var;
                        temp_var.var_name=nl->node.name;
                        temp_var.address=intToCString(var_name_offset);
                        
                        VL_addVar(VLS_finalVL(&LOCAL_VAR_SET),temp_var);
                    }
                    
                    // right side
                    Code_Generation(nl->next->node, ol,fl);
                    op.opcode=SETL;
                    
                    op.arg0=intToCString(var_name_offset);
                    op.arg1=intToCString(var_value_offset);
                    op.value=nl->node.name;

                    
                    OL_append(ol, op);
                    
                    LOCAL_OFFSET=var_value_offset;

                }
                // not local
                // global
                else{
                    char *var_name_address;
                    int var_set_index;
                    getValue(nl->node, &var_set_index, &var_name_address);
                    
                    int save_to_global_address=GLOBAL_OFFSET;
                    int var_name_offset=LOCAL_OFFSET;
                    int value__offset=LOCAL_OFFSET;
                    
                    // table_value_var_name
                    if (term(nl->node.name, "table_value")) {
                        printf("table_value var name\n");
                        TABLE_VALUE_VAR_NAME=TRUE;
                        Code_Generation(nl->node, ol, fl);
                        TABLE_VALUE_VAR_NAME=FALSE;
                        need_to_restore_offset_due_to_table_value_var_name=TRUE;
                    }
                    // does not exist
                    else if (term(var_name_address, "none")) {
                        save_to_global_address=GLOBAL_OFFSET;
                        
                        op.opcode=SETL;
                        op.arg0=intToCString(LOCAL_OFFSET);
                        op.arg1="none";
                        op.value=nl->node.name;

                        
                        var_name_offset=LOCAL_OFFSET;
                        
                        OL_append(ol, op);
                        
                        Var temp_var;
                        temp_var.address=intToCString(GLOBAL_OFFSET);
                        temp_var.var_name=nl->node.name;
                        
                        LOCAL_OFFSET++;
                        GLOBAL_OFFSET++;
                        
                        value__offset=LOCAL_OFFSET;

                        
                    }
                    // exist
                    else{
                        save_to_global_address=atoi(var_name_address);
                        
                        op.opcode=SETL;
                        op.arg0=intToCString(LOCAL_OFFSET);
                        op.arg1="none";
                        
                        var_name_offset=LOCAL_OFFSET;
                        
                        OL_append(ol, op);
                        
                        
                        LOCAL_OFFSET++;
                        value__offset=LOCAL_OFFSET;
                    }
                
                    
                    // right side
                    Code_Generation(nl->next->node, ol,fl);
                    op.opcode=SETL;
                    
                    op.arg0=intToCString(var_name_offset);
                    op.arg1=intToCString(value__offset);
                    op.value=nl->node.name;

                    
                    OL_append(ol, op);
                    
                    LOCAL_OFFSET=var_name_offset;

                    // set value back to Global
                    op.opcode=SET;
                    op.arg0="0";
                    op.arg1=intToCString(save_to_global_address);
                    op.arg2=intToCString(var_name_offset);
                    op.value=nl->node.name;

                    OL_append(ol, op);
            }
           
            }
            
            if (need_to_restore_offset_due_to_table_value_var_name) {
                if (NOW_LOCAL) {
                    LOCAL_OFFSET--;
                }
                else{
                    GLOBAL_OFFSET--;
                }
            }
        }
        else{
            printf("Does not support function def like x=def (a,b) ... now\n");
            exit(0);
        }
    }
    
    if (ism_operator(tree.name)) {
        // left
        Node_List *nl=tree.node_list;
        if (ism_operator(nl->node.name)) {
            Code_Generation(nl->node, ol,fl);
        }
        else{
            // num or id
            Code_Generation(nl->node, ol,fl);
        }
        
        // check whether string or num
        OPERATION op1=OL_lastOperation(*ol);
        
        
        // right
        if (ism_operator(nl->next->node.name)) {
            Code_Generation(nl->next->node, ol,fl);
        }
        else{
            // num or id
            Code_Generation(nl->next->node, ol,fl);

        }
        
        // check whether string or num
        OPERATION op2=OL_lastOperation(*ol);
        
        // do the calculation directly
        if (op1.arg1[0]=='#' && op2.arg1[0]=='#') {
            printf("BOTH num or string\n");
            
            char *value1=substr(op1.arg1, 1, (int)strlen(op1.arg1));
            char *value2=substr(op2.arg1, 1, (int)strlen(op2.arg1));
            char *output_str=Walley_Calculation(value1,value2,tree.name);
            printf("OUTPUT_str-----> %s\n",output_str);
            
            OL_pop(ol);
            OL_pop(ol);
            
            // append # ahead output_str
            int malloc_length=(int)strlen(output_str)+1;
            char *output=(char*)malloc(sizeof(char)*(malloc_length+1));
            strcpy(output, "#");
            strcat(output, output_str);
            output[malloc_length]=0;
            
            // local
            if (NOW_LOCAL) {
                LOCAL_OFFSET-=2;
                
                op.opcode=SETL;
                op.arg0=intToCString(LOCAL_OFFSET);
                op.arg1=output;
                op.value=output;
                
                OL_append(ol, op);
                
                LOCAL_OFFSET++;
            }
            // GLOBAL
            else{
                GLOBAL_OFFSET-=2;
                
                op.opcode=SETG;
                op.arg0=intToCString(GLOBAL_OFFSET);
                op.arg1=output;
                op.value=output;
                
                OL_append(ol, op);
                
                GLOBAL_OFFSET++;
            }

        }
        
        // can not do the calculation directly
        else
        {
            if (term(tree.name, "+")) {
                op.opcode=ADD;
            }
            else if (term(tree.name, "-")) {
                op.opcode=SUB;
            }
            else if (term(tree.name, "*")) {
                op.opcode=MUL;
            }
            else if (term(tree.name, "/")) {
                op.opcode=DIV;
            }
            else if (term(tree.name, "%")) {
                op.opcode=MOD;
            }
            else if (term(tree.name, "^")) {
                op.opcode=POW;
            }
            else{
                printf("m_operator error\n");
                exit(0);
            }
            
            // local
            if (NOW_LOCAL) {
                LOCAL_OFFSET-=2;
                
                op.arg0=intToCString(LOCAL_OFFSET);
                op.arg1=intToCString(LOCAL_OFFSET);
                op.arg2=intToCString(LOCAL_OFFSET+1);
                
                OL_append(ol, op);
                
                LOCAL_OFFSET++;
            }
            // GLOBAL
            else{
                GLOBAL_OFFSET-=2;
                
                op.arg0=intToCString(GLOBAL_OFFSET);
                op.arg1=intToCString(GLOBAL_OFFSET);
                op.arg2=intToCString(GLOBAL_OFFSET+1);
                
                OL_append(ol, op);
                
                GLOBAL_OFFSET++;
            }
        }
        
        
        
    }
    
    
    
    
}



















