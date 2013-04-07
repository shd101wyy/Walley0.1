//
//  walley_code_generation.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_function_data_type.h"

/*
 x = 12-5*6
 
    =
   / \
  x   -
     /  \
    12   *
        / \
        5  6
 
 x 12 5 6 * - =
 
 register_offset=0
 
 
 #x  LOADG 0 #x  $register_offset+=1 -> 1
    
  0 x
 
 #12 LOADG 1 #12 $register_offset+=1 -> 2
 
  1   12
  0   x
 
 #5  LOADG 2 #5  $register_offset+=1 -> 3
 
  2  5                                          only 2 registers
  1  12                                         1  12
  0  x                                          0  5   move x to other place

 #6  LOADG 3 #6  $register_offset+=1 -> 4
 
  3  6         only 3 registers                 only 2 registers
  2  5         2  5                             1  6  move 12 to other place
  1  12        1  12  move x to other place     0  5
  0  x         0  6 
 
 #*  register_offset-=2 --> 2
     MULT 2 2 3
 
  3  6         only 3 registers                 only 2 registers
  2  30        2 30                             1 6
  1  12        1 12                             0 30
  0  x         0  6
 
     register_offset+=1 --> 3
 
 #-  register_offset-=2 --> 1
     MINUS 1 1 2
 
  3  6        only 3 registers                  only 2 registers
  2  30       2 30                              can not calculate
  1  -18      1 -18
  0  x        0 6
 
     register_offset+=1 --> 2
 
 #=  register_offset-=2 --> 0
 
    SETG stack_offset r1
    
 ==
 end
 */

/*
 x=3*4-5/6
 
    =
   x -
    *   /
   3 4 5 6
 
 x 3 4 * 5 6 / - =
 because x does not exist in value_list
 
 offset=0;
 #x  SETNONE 0
 offset++ ->1
 
 #3  SETCONS 1 3
 offset++ ->2
 
 #4  SETCONS 2 4
 offset++ ->3
 
 #*  offset-=2 ->1
    MULT 1 1 2
 offset++ ->2
 
 #5 SETCONS 2 5
 offset++ ->3
 
 #6 SETCONS 3 6
 offset++ ->4
 
 #/ offset-=2 ->2
    DIV 2 2 3
    offset++ -> 3
 
 #- offset-=2 -> 1
    MINUS 1 1 2
    offset++ ->2
 
 #= offset-=2 ->0
    SET 0 1
    offset++ ->1
 
 
 
 */
/*
    LOGIC
 
    not
     |
    and
   /   \
   <    <
  3 4  6 5
 
 3 4 < 6 5 < and
 
 offset=0
 #3 SETCONS 0 3
    offset++ ->1
 
 #4 SETCONS 1 4
    offset++ ->2
 
 offset-=2 --> 0
 #< LT 0 0 1   $if < then save true, else save false;
 offset++ -> 1
 
 #6 SETCONS 1 6
 offset++ ->2
 
 #5 SETCONS 2 5
 offset++ ->3
 
 offset-=2 -> 1
 #< LT 1 1 2
 offset++ -> 2
 
 //now register
   1 false
   0 true
 
 offset-=2 -> 0
 #and
 AND 0 0 1
 offset++ -> 1
 // now register
    1 false
    0 false
 
 offset-=1
 #not
 NOT 0
 offset++ ->1
 // now register
    1 false
    0 true
 
 NOT
 */

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
    if (term(tree.token_class, "num")) {
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
        while (temp_vls->next!=NULL) {
            Var_List *local_var_list=temp_vls->current_var_list;
            
            if (local_var_list->current_var.var_name!=NULL && local_var_list!=GLOBAL_VAR_LIST) {
                // check local
                while (local_var_list->next!=NULL) {
                    // find
                    if (term(local_var_list->current_var.var_name, tree.name)) {
                        *var_set_index=temp_vls->index;
                        *var_value=intToCString(local_var_list->current_var.address);
                        return;
                    }
                    local_var_list=local_var_list->next;
                }
                if (term(local_var_list->current_var.var_name, tree.name)) {
                    *var_set_index=temp_vls->index;
                    *var_value=intToCString(local_var_list->current_var.address);
                    return;
                }
                
            }

            temp_vls=temp_vls->next;
        }
        
              
       
        if (GLOBAL_VAR_LIST->current_var.var_name!=NULL) {
            // check global
            while (GLOBAL_VAR_LIST->next!=NULL) {
                if (term(GLOBAL_VAR_LIST->current_var.var_name, tree.name)) {
                    *var_set_index=0;
                    *var_value=intToCString(GLOBAL_VAR_LIST->current_var.address);
                    return;
                }
                GLOBAL_VAR_LIST=GLOBAL_VAR_LIST->next;
            }
            if (term(GLOBAL_VAR_LIST->current_var.var_name, tree.name)) {
                *var_set_index=0;
                *var_value=intToCString(GLOBAL_VAR_LIST->current_var.address);
                return;
            }

        }
       
    }
    
    *var_set_index=-1;
    *var_value="none";
}

void Code_Generation(TREE tree, Operation_List **ol, Function_List **fl){
    OPERATION op;
    op.arg0=NULL;
    op.arg1=NULL;
    op.arg2=NULL;
    

    
    int CURRENT_VAR_SET_INDEX=VLS_length(LOCAL_VAR_SET);
    printf("current_var_set_index %d\n",CURRENT_VAR_SET_INDEX);
    
    bool NOW_LOCAL=FALSE;
    if (SL_length(STATEMENTS_LIST)!=0) {
        NOW_LOCAL=TRUE;
    }
    printf("NOW_LOCAL %d\n",NOW_LOCAL);

    // statements..
    if (term(tree.name, "statements")) {
        Node_List *nl=tree.node_list;
        
        // while statements
        if (term(nl->node.name, "while")) {
            SL_addString(&STATEMENTS_LIST, "while");

            int current_while_index=OL_length(*ol);
            printf("@@@@ %d\n",current_while_index);
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
            
            return;
        }
        // if statements
        else if (term(nl->node.name, "if")) {
            SL_addString(&STATEMENTS_LIST, "if");

            
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
            OL_append(ol, op);
            
            LOCAL_OFFSET++;
            
            return;
            
        }
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
            
            
            return;
        }
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
            
        
            return;
        }
        // def statements
        else if (term(nl->node.name, "def")){
            printf("Begin to Define a function\n");
            
            // push def
            SL_addString(&STATEMENTS_LIST, "def");

            // begin new var set
            VLS_push(&LOCAL_VAR_SET);
            
            // backup local offset
            SL_addString(&LOCAL_OFFSET_LIST, intToCString(LOCAL_OFFSET));
            LOCAL_OFFSET=0;
            

            // backup local offset
            SL_addString(&LOCAL_OFFSET_LIST, intToCString(LOCAL_OFFSET));


            
            //( statements( def)( func(call add)( params(id num1)(id num2))))
            TREE func_tree=nl->next->node;
            char *func_name=func_tree.node_list->node.name;
            
            // add func_name
            FL_addFuncName(fl, func_name);
            
            
            // begin new local registers
            op.opcode=BEGINLOCAL;
            FL_addOperation(fl, op);

            
            TREE param_tree=func_tree.node_list->next->node;
            int params_num=NL_length(param_tree.node_list);
            
            Node_List *params_nl=param_tree.node_list;
            //add params to local var list and local operation list;
            int i=0;
            for (; i<params_num; i++) {
                char *param_name=params_nl->node.name;
                
                // add to local var list
                Var param_var;
                param_var.address=LOCAL_OFFSET;
                param_var.var_name=param_name;
                VL_addVar(VLS_finalVL(&LOCAL_VAR_SET), param_var);
                
                // add to local operation list
                OPERATION temp_op;
                temp_op.opcode=SETL;
                temp_op.arg0=intToCString(LOCAL_OFFSET);
                temp_op.arg1="none";
                temp_op.arg2=NULL;
                FL_addOperation(fl, temp_op);
                
                
                LOCAL_OFFSET++;
                
                params_nl=params_nl->next;
                
            }
            
            // add return
            // add to local var list
            Var param_var;
            param_var.address=LOCAL_OFFSET;
            param_var.var_name="return";
            VL_addVar(VLS_finalVL(&LOCAL_VAR_SET), param_var);
            
            // add to local operation list
            OPERATION temp_op;
            temp_op.opcode=SETL;
            temp_op.arg0=intToCString(LOCAL_OFFSET);
            temp_op.arg1="none";
            temp_op.arg2=NULL;
            FL_addOperation(fl, temp_op);
            
            
            LOCAL_OFFSET++;
                
            NOW_FUNCTION=TRUE;
            
            
            // init fl inside function
            FL_init(&((*fl)->next_in_function));
        }
        else if (term(nl->node.name, "end")){
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
                FL_addOperation(fl, op);
                
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
    
    // num
    if (term(tree.token_class, "num")) {
        // local
        if (NOW_LOCAL) {
            
            op.opcode=SETL;
            
            op.arg0=intToCString(LOCAL_OFFSET);
            
            int var_set_index;
            char *var_value;
            getValue(tree, &var_set_index, &var_value);
            op.arg1=var_value;
            
            op.arg2=NULL;
            
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
                
                LOCAL_OFFSET++;
                OL_append(ol, op);

            }
            // exist and
            // is current var set
            else if(CURRENT_VAR_SET_INDEX==var_set_index){
                op.opcode=SETL;
                op.arg0=intToCString(LOCAL_OFFSET);
                op.arg1=var_value;
                
                
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
        if (NOW_LOCAL) {
            op.opcode=NEWTABLE;
            op.arg0=intToCString(LOCAL_OFFSET);
            OL_append(ol, op);
            LOCAL_OFFSET++;
        }
        else{
            op.opcode=NEWTABLE;
            op.arg0=intToCString(GLOBAL_OFFSET);
            OL_append(ol, op);
            GLOBAL_OFFSET++;
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
    
    //table_expr
    if (term(tree.name, "table_expr")) {
        TREE value_tree=tree.node_list->next->node;
        
        // value
        
        // table
        if (term(value_tree.node_list->node.token_class,"table")) {
            Code_Generation(value_tree, ol,fl);
        }
        // not table
        else{
            Code_Generation(value_tree, ol,fl);
        // add value
            // local
            if (NOW_LOCAL) {
                LOCAL_OFFSET--;
                op.opcode=TADD;
                op.arg0=intToCString(LOCAL_OFFSET);
                
                OL_append(ol, op);

            }
            // global
            else{
                GLOBAL_OFFSET--;
                op.opcode=TADD;
                op.arg0=intToCString(GLOBAL_OFFSET);
                
                OL_append(ol, op);
            }
        }
        
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
        NL_print(nl);
        // x=12+3
        if (length_of_nl==2||(length_of_nl==3&&IS_LOCAL_VAR)) {
            // global
            // so OFFSET == GLOBAL_OFFSET
            if (NOW_LOCAL==FALSE) {
                char *var_name_address; 
                int var_set_index;
                getValue(nl->node, &var_set_index, &var_name_address);
                
                printf("var_set_index %d    var_name_adderss %s\n",var_set_index,var_name_address);
                
                int current__offset;
                int value__offset;
                
                // var does not exist
                if (term(var_name_address, "none")) {
                    current__offset=GLOBAL_OFFSET;
                    op.opcode=SETG;
                    
                    op.arg0=intToCString(current__offset);
                    op.arg1="none";
                    
                    OL_append(ol, op);
                    
                    Var temp_var;
                    temp_var.address=current__offset;
                    temp_var.var_name=nl->node.name;
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
                    
                    int var_name_offset;
                    int var_value_offset;
                    
                    // same var exist in local registers
                    if (var_set_index==CURRENT_VAR_SET_INDEX) {
                        var_name_offset=atoi(var_name_address);
                        var_value_offset=LOCAL_OFFSET;
                    }
                    // var does not exist in that local registers
                    else{
                        var_name_offset=LOCAL_OFFSET;
                        
                        op.opcode=SETL;
                        op.arg0=intToCString(LOCAL_OFFSET);
                        op.arg1="none";
                        
                        OL_append(ol, op);
                        
                        LOCAL_OFFSET++;
                        var_value_offset=LOCAL_OFFSET;
                        
                        Var temp_var;
                        temp_var.var_name=nl->node.name;
                        temp_var.address=var_name_offset;
                        
                        VL_addVar(VLS_finalVL(&LOCAL_VAR_SET),temp_var);
                    }
                    
                    // right side
                    Code_Generation(nl->next->node, ol,fl);
                    op.opcode=SETL;
                    
                    op.arg0=intToCString(var_name_offset);
                    op.arg1=intToCString(var_value_offset);
                    
                    OL_append(ol, op);
                    
                    LOCAL_OFFSET=var_value_offset;

                }
                // not local
                // global
                else{
                    char *var_name_address;
                    int var_set_index;
                    getValue(nl->node, &var_set_index, &var_name_address);
                    
                    int save_to_global_address;
                    int var_name_offset;
                    int value__offset;
                    // does not exist
                    if (term(var_name_address, "none")) {
                        save_to_global_address=GLOBAL_OFFSET;
                        
                        op.opcode=SETL;
                        op.arg0=intToCString(LOCAL_OFFSET);
                        op.arg1="none";
                        
                        var_name_offset=LOCAL_OFFSET;
                        
                        OL_append(ol, op);
                        
                        Var temp_var;
                        temp_var.address=GLOBAL_OFFSET;
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
                    
                    OL_append(ol, op);
                    
                    LOCAL_OFFSET=var_name_offset;

                    // set value back to Global
                    op.opcode=SET;
                    op.arg0="0";
                    op.arg1=intToCString(save_to_global_address);
                    op.arg2=intToCString(var_name_offset);
                    OL_append(ol, op);
            }
           
            }
            /*
            // THE OFFSET HERE HAS A LOT PROBLEMS
            
            // add current_global_offset to 
            // save the offset for var_name
            // check var_name address
            printf("VAR_NAME %s\n",nl->node.name);
            
            char *var_name_address; //=getValue(nl->node, (*fl)->local_var_list);
            int var_set_index;
            getValue(nl->node, &var_set_index, &var_name_address);
            
            int current__offset;// =GLOBAL_OFFSET;
            // does not exsit
            if (term(var_name_address, "none")) {
                // save var_name
                
                current__offset=(*OFFSET);
                op.opcode=SETG;
                
                if (IS_LOCAL_VAR || NOW_FUNCTION) {
                    op.opcode=SETL;
                }
                
                op.arg0=intToCString(current__offset);
                op.arg1="none";
                
                // add to local var list
                if (IS_LOCAL_VAR) {
                    var.address=(*OFFSET);
                    var.var_name=nl->node.name;
                    VL_addVar(VLS_finalVL(&LOCAL_VAR_SET), var);
                }
                // add to global var list
                else{
                    var.address= GLOBAL_OFFSET ;    //(*OFFSET);
                    var.var_name=nl->node.name;
                    VL_addVar(&GLOBAL_VAR_LIST, var);
                    
                    if (GLOBAL_OFFSET!=(*OFFSET)) {
                        GLOBAL_OFFSET++;

                    }
                }
                
                
                OL_append(ol, op);
                
                (*OFFSET)++;
            }
            // exist
            else{
                current__offset=atoi(var_name_address);
                printf("Exist %d\n",current__offset);
                
            }
            
           
            // right side
            Code_Generation(nl->next->node, ol,fl,OFFSET);
            
            
            //GLOBAL_OFFSET-=2;
            op.opcode=SETG;
            if (IS_LOCAL_VAR || NOW_FUNCTION) {
                op.opcode=SETL;
            }
            op.arg0=intToCString(current__offset);
            op.arg1=intToCString(current__offset+1);
            
            OL_append(ol, op);
            
            //GLOBAL_OFFSET++;
            (*OFFSET)=current__offset+1;
            
            if (NOW_FUNCTION==TRUE && IS_LOCAL_VAR==FALSE) {
                op.opcode=LOADTOG;
                //op.arg0=intToCString(GLOBAL_OFFSET-1);
                op.arg0=intToCString(current__offset);
                op.arg1=NULL;
                op.arg2=NULL;
                OL_append(ol, op);
            }
            
            
            
            // check whether in while statements
            // if in statements,
            //increase all arg0, arg1,arg2,arg3 above TEST below while_index(which is stored in WHILE_LIST_OL_INDEX) by 1.
            if (STATEMENTS_LIST->string_content!=NULL&&term(var_name_address,"none")) {
                Str_List *temp_sl=STATEMENTS_LIST;
                while (temp_sl->next!=NULL) {
                    temp_sl=temp_sl->next;
                }
                char *check_while_str=temp_sl->string_content;

                
                if (term("while", check_while_str)) {
                    
                    temp_sl=WHILE_LIST_OL_INDEX;
                    while (temp_sl->next!=NULL) {
                        temp_sl=temp_sl->next;
                    }
                    char* while_index_str=temp_sl->string_content;
                    
                    int while_index=atoi(while_index_str);
                    
                    Operation_List **temp_ol=&(*ol);
                    
                    while ((*temp_ol)->current_index!=while_index) {
                        temp_ol=&((*temp_ol)->next);
                    }
                    
                    while ((*temp_ol)->operation.opcode!=TEST) {
                        if ((*temp_ol)->operation.arg0!=NULL) {
                            (*temp_ol)->operation.arg0=intToCString(atoi((*temp_ol)->operation.arg0)+1);
                        }
                        if ((*temp_ol)->operation.arg1!=NULL&&(*temp_ol)->operation.opcode!=SETG&&(*temp_ol)->operation.opcode!=SETL) {
                            (*temp_ol)->operation.arg1=intToCString(atoi((*temp_ol)->operation.arg1)+1);
                        }
                        if ((*temp_ol)->operation.arg2!=NULL) {
                            (*temp_ol)->operation.arg2=intToCString(atoi((*temp_ol)->operation.arg2)+1);
                        }
                    temp_ol=&((*temp_ol)->next);
                    }

                    // change test
                    if ((*temp_ol)->operation.arg0!=NULL) {
                        (*temp_ol)->operation.arg0=intToCString(atoi((*temp_ol)->operation.arg0)+1);
                    }
                    if ((*temp_ol)->operation.arg1!=NULL) {
                        (*temp_ol)->operation.arg1=intToCString(atoi((*temp_ol)->operation.arg1)+1);
                    }
                    if ((*temp_ol)->operation.arg2!=NULL) {
                        (*temp_ol)->operation.arg2=intToCString(atoi((*temp_ol)->operation.arg2)+1);
                    }
                    
                    OL_print(*ol);
                    
                }
                
                return;
            }
            IS_LOCAL_VAR=FALSE;
             */
            
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
        
        // right
        if (ism_operator(nl->next->node.name)) {
            Code_Generation(nl->next->node, ol,fl);
        }
        else{
            // num or id
            Code_Generation(nl->next->node, ol,fl);

        }
        
        
        
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



















