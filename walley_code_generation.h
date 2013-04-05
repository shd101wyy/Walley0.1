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

/*
Operation_List *CG(Token_List *tl){
    Operation_List *ol;
    OL_init(&ol);
    
    
    int length_of_tl=TL_length(tl);
    int i=0;
    
    for (; i<length_of_tl; i++) {
        if (tl->current_token.TOKEN_CLASS==NULL) {
            printf("TOKEN_CLASS==NULL\n");
            exit(0);
        }
        else if (term(tl->current_token.TOKEN_CLASS, "id")) {
            // check whether existed
            int var_address=VL_address(GLOBAL_VAR_LIST, tl->current_token.TOKEN_STRING);
            // dose not exist
            if (var_address==-1) {
                printf("VAR DOES NOT EXIST\n");
                OPERATION op;
                op.opcode=SETCONS;
                op.arg0=intToCString(GLOBAL_OFFSET);
                op.arg1=tl->current_token.TOKEN_STRING;
                op.arg2=NULL;
                OL_append(&ol, op);
                
                GLOBAL_OFFSET++;
            }
            else{
                printf("VAR EXISTED\n");

                OPERATION op;
                op.opcode=SETG;
                op.arg0=intToCString(GLOBAL_OFFSET);
                op.arg1=intToCString(var_address);
                op.arg2=NULL;
                OL_append(&ol, op);
                
                GLOBAL_OFFSET++;
            }
        }
        
        else if(term(tl->current_token.TOKEN_CLASS, "num")){
            OPERATION op;
            op.opcode=SETCONS;
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1=tl->current_token.TOKEN_STRING;
            op.arg2=NULL;
            OL_append(&ol, op);
            
            GLOBAL_OFFSET++;
        }
        
        else if (ism_operator(tl->current_token.TOKEN_STRING)){
            GLOBAL_OFFSET-=2;
            OPERATION op;
            if (term(tl->current_token.TOKEN_STRING, "+")) {
                op.opcode=ADD;
            }
            else if (term(tl->current_token.TOKEN_STRING, "-")) {
                op.opcode=SUB;
            }
            else if (term(tl->current_token.TOKEN_STRING, "*")) {
                op.opcode=MUL;
            }
            else if (term(tl->current_token.TOKEN_STRING, "/")) {
                op.opcode=DIV;
            }
            else if (term(tl->current_token.TOKEN_STRING, "%")) {
                op.opcode=MOD;
            }
            else if (term(tl->current_token.TOKEN_STRING, "^")) {
                op.opcode=POW;
            }
            else{
                printf("m_operator error\n");
                exit(0);
            }
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1=intToCString(GLOBAL_OFFSET);
            op.arg2=intToCString(GLOBAL_OFFSET+1);
            
            
            OL_append(&ol, op);
            
            GLOBAL_OFFSET++;

        }
        else if (term(tl->current_token.TOKEN_STRING, "=")){
            GLOBAL_OFFSET-=2;
            
            VL_addVarAccordingToVarNameAndAddress(&GLOBAL_VAR_LIST, register_w[GLOBAL_OFFSET].value, GLOBAL_OFFSET);
            OPERATION op;
            op.opcode=SETG;
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1=intToCString(GLOBAL_OFFSET+1);
            op.arg2=NULL;
            
            OL_append(&ol, op);
            //register_w[GLOBAL_OFFSET].value=register_w[GLOBAL_OFFSET+1].value;
            
            GLOBAL_OFFSET++;
            
        }
        else if (term(tl->current_token.TOKEN_STRING, "statements")){
            
        }
        
        else{
            printf("ONLY SUPPORT NUM AND ID now\n");
            exit(0);
        }
        tl=tl->next;
    }
    return ol;
}
*/

// input_str   12 num  --> #12
// input_str   x id   -->  0       $address of x
//                      none    $does not exist
char *getValue(TREE tree, Var_List *local_var_list){
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
        return return_value;
    }
    else{
        if (local_var_list->current_var.var_name!=NULL && local_var_list!=GLOBAL_VAR_LIST) {
            // check local
            while (local_var_list->next!=NULL) {
                if (term(local_var_list->current_var.var_name, tree.name)) {
                    return intToCString(local_var_list->current_var.address);
                }
                local_var_list=local_var_list->next;
            }
            if (term(local_var_list->current_var.var_name, tree.name)) {
                return intToCString(local_var_list->current_var.address);
            }

        }
        
       
        if (GLOBAL_VAR_LIST->current_var.var_name!=NULL) {
            // check global
            while (GLOBAL_VAR_LIST->next!=NULL) {
                if (term(GLOBAL_VAR_LIST->current_var.var_name, tree.name)) {
                    return intToCString(GLOBAL_VAR_LIST->current_var.address);
                }
                GLOBAL_VAR_LIST=GLOBAL_VAR_LIST->next;
            }
            if (term(GLOBAL_VAR_LIST->current_var.var_name, tree.name)) {
                return intToCString(GLOBAL_VAR_LIST->current_var.address);
            }

        }
       
    }
    return "none";
}

void Code_Generation(TREE tree, Operation_List **ol, Function_List **fl,Var_List **current_var_list,int *OFFSET){
    Var var;
    OPERATION op;
    op.arg0=NULL;
    op.arg1=NULL;
    op.arg2=NULL;

    // statements..
    if (term(tree.name, "statements")) {
        Node_List *nl=tree.node_list;
        
        // while statements
        if (term(nl->node.name, "while")) {
            int current_while_index=OL_length(*ol);
            printf("@@@@ %d\n",current_while_index);
            SL_addString(&WHILE_LIST_OL_INDEX, intToCString(current_while_index));
            
            nl=nl->next;
            Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
            
            //finish dealing with relation and simple relation
            
            // meet TEST
            (*OFFSET)--;
            op.opcode=TEST;
            op.arg0=intToCString((*OFFSET));
            OL_append(ol, op);
            
            (*OFFSET)++;
            
            SL_addString(&STATEMENTS_LIST, "while");
            return;
        }
        // if statements
        else if (term(nl->node.name, "if")) {
            nl=nl->next;
            Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
            
            //finish dealing with relation and simple relation
            
            // meet TEST
            (*OFFSET)--;
            op.opcode=TEST;
            op.arg0=intToCString((*OFFSET));
            OL_append(ol, op);
            
            (*OFFSET)++;
            
            SL_addString(&STATEMENTS_LIST, "if");
        }
        // elif statements
        else if (term(nl->node.name, "elif")){
            
            // pop ahead
            SL_pop(&STATEMENTS_LIST);
            
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
            // push elif
            SL_addString(&STATEMENTS_LIST, "elif");
            
            nl=nl->next;
            Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
            
            //finish dealing with relation and simple relation
            
            // meet TEST
            (*OFFSET)--;
            op.opcode=TEST;
            op.arg0=intToCString((*OFFSET));
            OL_append(ol, op);
            
            (*OFFSET)++;
            
            
            return;
        }
        else if (term(nl->node.name, "else")){
            
            
            // pop ahead
            SL_pop(&STATEMENTS_LIST);
            
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
            // push else
            SL_addString(&STATEMENTS_LIST, "else");
            
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
            
            LOCAL_OFFSET=0;
            
            //( statements( def)( func(call add)( params(id num1)(id num2))))
            TREE func_tree=nl->next->node;
            char *func_name=func_tree.node_list->node.name;
            
            //add func_name
            FL_addFuncName(fl, func_name);

            
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
                VL_addVar(&((*fl)->local_var_list), param_var);
                
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
            VL_addVar(&((*fl)->local_var_list), param_var);
            
            // add to local operation list
            OPERATION temp_op;
            temp_op.opcode=SETL;
            temp_op.arg0=intToCString(LOCAL_OFFSET);
            temp_op.arg1="none";
            temp_op.arg2=NULL;
            FL_addOperation(fl, temp_op);
            
            
            LOCAL_OFFSET++;
                
            NOW_FUNCTION=TRUE;
            
            SL_addString(&STATEMENTS_LIST, "def");
            
            // init fl inside function
            FL_init(&((*fl)->next_in_function));
        }
        else if (term(nl->node.name, "end")){
           
            // only support if elif else now
            // need to check poped statement...
            SL_print(STATEMENTS_LIST);
            // pop ahead
            char *stm=SL_pop(&STATEMENTS_LIST);
            if (term(stm, "while")) {
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
                Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
                nl=nl->next;
            }
            Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
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
            Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
            nl=nl->next;
        }
       
        
        (*OFFSET)-=2;
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
        op.arg0=intToCString((*OFFSET));
        op.arg1=intToCString((*OFFSET));
        op.arg2=intToCString((*OFFSET)+1);
        (*OFFSET)++;
        
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
            Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
            nl=nl->next;
        }
        
        (*OFFSET)-=2;
        if (term(temp_tree.name, "and")) {
            op.opcode=AND;
            op.arg0=intToCString((*OFFSET));
            op.arg1=intToCString((*OFFSET));
            op.arg2=intToCString((*OFFSET)+1);
        }
        else if (term(temp_tree.name, "or")){
            op.opcode=OR;
            op.arg0=intToCString((*OFFSET));
            op.arg1=intToCString((*OFFSET));
            op.arg2=intToCString((*OFFSET)+1);
        }
        else if (term(temp_tree.name, "not")){
            (*OFFSET)++;
            op.opcode=NOT;
            op.arg0=intToCString((*OFFSET));
        }
        else{
            printf("Relation Error %s\n",temp_tree.name);
        }
        
        OL_append(ol, op);
        
        (*OFFSET)++;
        return;
    }
    
    // num or id
    if (term(tree.token_class, "num")||term(tree.token_class, "id")) {
        op.opcode=SETG;
        if (IS_LOCAL_VAR || NOW_FUNCTION) {
            op.opcode=SETL;
        }
        op.arg0=intToCString((*OFFSET));
        op.arg1=getValue(tree, (*fl)->local_var_list);
        op.arg2=NULL;
        
        (*OFFSET)++;
        OL_append(ol, op);
        return;
    }
    // value
    if (term(tree.name, "value")) {
        Code_Generation(tree.node_list->node, ol,fl,current_var_list,OFFSET);
        return;
    }
    // table
    if (term(tree.token_class, "table")) {
        op.opcode=NEWTABLE;
        op.arg0=intToCString((*OFFSET));
        OL_append(ol, op);
        (*OFFSET)++;
        
        Node_List *nl=tree.node_list;
        int i=0;
        int length_of_nl=NL_length(nl);
        for (; i<length_of_nl; i++) {
            Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
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
            Code_Generation(value_tree, ol,fl,current_var_list,OFFSET);
        }
        // not table
        else{
            Code_Generation(value_tree, ol,fl,current_var_list,OFFSET);
        // add value
        (*OFFSET)--;
        op.opcode=TADD;
        op.arg0=intToCString((*OFFSET));
        
        OL_append(ol, op);
        }
        
    }
    
    // global
    if (term(tree.name, "=")) {
        
        // x=12+3
        Node_List *nl=tree.node_list;
        int length_of_nl=NL_length(nl);
        if (term(nl->node.name, "local")) {
            printf("### IS LOCAL\n");
            IS_LOCAL_VAR=TRUE;
            nl=nl->next;
        }
        NL_print(nl);
        // x=12+3
        if (length_of_nl==2||(length_of_nl==3&&IS_LOCAL_VAR)) {
            

            // THE OFFSET HERE HAS A LOT PROBLEMS
            
            // add current_global_offset to 
            // save the offset for var_name
            // check var_name address
            char *var_name_address=getValue(tree.node_list->node, (*fl)->local_var_list);
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
                    VL_addVar(current_var_list, var);
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
                if (IS_LOCAL_VAR==FALSE) {
                    current__offset=(*OFFSET);
                    (*OFFSET)++;
                }
                
            }
            
           
            // right side
            Code_Generation(nl->next->node, ol,fl,current_var_list,OFFSET);
            
            
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
            Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
        }
        else{
            // num or id
            Code_Generation(nl->node, ol,fl,current_var_list,OFFSET);
        }
        
        // right
        if (ism_operator(nl->next->node.name)) {
            Code_Generation(nl->next->node, ol,fl,current_var_list,OFFSET);
        }
        else{
            // num or id
            Code_Generation(nl->next->node, ol,fl,current_var_list,OFFSET);

        }
        
        
        (*OFFSET)-=2;
        
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
        
        op.arg0=intToCString((*OFFSET));
        op.arg1=intToCString((*OFFSET));
        op.arg2=intToCString((*OFFSET)+1);
        
        OL_append(ol, op);
        
        (*OFFSET)++;
        
    }
    
    
    
    
}



















