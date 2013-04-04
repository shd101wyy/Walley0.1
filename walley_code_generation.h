//
//  walley_code_generation.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_vm.h"

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
        if (local_var_list->current_var.var_name!=NULL) {
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

void Code_Generation(TREE tree, Operation_List **ol, Var_List **local_var_list){
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
            SL_addString(&WHILE_LIST_OL_INDEX, intToCString(current_while_index));
            
            nl=nl->next;
            Code_Generation(nl->node, ol, local_var_list);
            
            //finish dealing with relation and simple relation
            
            // meet TEST
            GLOBAL_VAR_LIST--;
            op.opcode=TEST;
            op.arg0=intToCString(GLOBAL_OFFSET);
            OL_append(ol, op);
            
            GLOBAL_OFFSET++;
            
            SL_addString(STATEMENTS_LIST, "while");
        }
        // if statements
        if (term(nl->node.name, "if")) {
            nl=nl->next;
            Code_Generation(nl->node, ol, local_var_list);
            
            //finish dealing with relation and simple relation
            
            // meet TEST
            GLOBAL_VAR_LIST--;
            op.opcode=TEST;
            op.arg0=intToCString(GLOBAL_OFFSET);
            OL_append(ol, op);
            
            GLOBAL_OFFSET++;
            
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
            Code_Generation(nl->node, ol, local_var_list);
            
            //finish dealing with relation and simple relation
            
            // meet TEST
            GLOBAL_VAR_LIST--;
            op.opcode=TEST;
            op.arg0=intToCString(GLOBAL_OFFSET);
            OL_append(ol, op);
            
            GLOBAL_OFFSET++;
            
            
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
        else if (term(nl->node.name, "end")){
           
            // only support if elif else now
            // need to check poped statement...
            SL_print(STATEMENTS_LIST);
            // pop ahead
            char *stm=SL_pop(&STATEMENTS_LIST);
            if (term(stm, "while")) {
                
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
                Code_Generation(nl->node, ol,local_var_list);
                nl=nl->next;
            }
            Code_Generation(nl->node, ol,local_var_list);
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
            Code_Generation(nl->node, ol, local_var_list);
            nl=nl->next;
        }
       
        
        GLOBAL_OFFSET-=2;
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
        op.arg0=intToCString(GLOBAL_OFFSET);
        op.arg1=intToCString(GLOBAL_OFFSET);
        op.arg2=intToCString(GLOBAL_OFFSET+1);
        GLOBAL_OFFSET++;
        
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
            Code_Generation(nl->node, ol, local_var_list);
            nl=nl->next;
        }
        
        GLOBAL_OFFSET-=2;
        if (term(temp_tree.name, "and")) {
            op.opcode=AND;
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1=intToCString(GLOBAL_OFFSET);
            op.arg2=intToCString(GLOBAL_OFFSET+1);
        }
        else if (term(temp_tree.name, "or")){
            op.opcode=OR;
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1=intToCString(GLOBAL_OFFSET);
            op.arg2=intToCString(GLOBAL_OFFSET+1);
        }
        else if (term(temp_tree.name, "not")){
            GLOBAL_OFFSET++;
            op.opcode=NOT;
            op.arg0=intToCString(GLOBAL_OFFSET);
        }
        else{
            printf("Relation Error %s\n",temp_tree.name);
        }
        
        OL_append(ol, op);
        
        GLOBAL_OFFSET++;
        return;
    }
    
    // num or id
    if (term(tree.token_class, "num")||term(tree.token_class, "id")) {
        op.opcode=SETG;
        op.arg0=intToCString(GLOBAL_OFFSET);
        op.arg1=getValue(tree, *local_var_list);
        op.arg2=NULL;
        
        GLOBAL_OFFSET++;
        OL_append(ol, op);
        return;
    }
    // value
    if (term(tree.name, "value")) {
        Code_Generation(tree.node_list->node, ol, local_var_list);
        return;
    }
    // table
    if (term(tree.token_class, "table")) {
        op.opcode=NEWTABLE;
        op.arg0=intToCString(GLOBAL_OFFSET);
        OL_append(ol, op);
        GLOBAL_OFFSET++;
        
        Node_List *nl=tree.node_list;
        int i=0;
        int length_of_nl=NL_length(nl);
        for (; i<length_of_nl; i++) {
            Code_Generation(nl->node, ol, local_var_list);
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
            Code_Generation(value_tree, ol, local_var_list);
        }
        // not table
        else{
            Code_Generation(value_tree, ol, local_var_list);
        // add value
        GLOBAL_OFFSET--;
        op.opcode=TADD;
        op.arg0=intToCString(GLOBAL_OFFSET);
        
        OL_append(ol, op);
        }
        
    }
    
    // global
    if (term(tree.name, "=")) {
        
        // x=12+3
        Node_List *nl=tree.node_list;
        // x=12+3
        if (NL_length(nl)==2) {
            // add current_global_offset to 
            // save the offset for var_name
            // check var_name address
            char *var_name_address=getValue(tree.node_list->node, *local_var_list);
            int current_global_offset;// =GLOBAL_OFFSET;
            // does not exsit
            if (term(var_name_address, "none")) {
                // save var_name
                current_global_offset=GLOBAL_OFFSET;
                op.opcode=SETG;
                op.arg0=intToCString(current_global_offset);
                op.arg1="none";
                
                // add to global var list
                var.address=GLOBAL_OFFSET;
                var.var_name=nl->node.name;
                VL_addVar(&GLOBAL_VAR_LIST, var);
                
                
                OL_append(ol, op);
                
                GLOBAL_OFFSET++;
            }
            // exist
            else{
                current_global_offset=atoi(var_name_address);
                
            }
           
            // right side
            Code_Generation(nl->next->node, ol, local_var_list);
            
            
            //GLOBAL_OFFSET-=2;
            op.opcode=SETG;
            op.arg0=intToCString(current_global_offset);
            op.arg1=intToCString(current_global_offset+1);
            
            OL_append(ol, op);
            
            //GLOBAL_OFFSET++;
            GLOBAL_OFFSET=current_global_offset+1;
            
            
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
            Code_Generation(nl->node, ol, local_var_list);
        }
        else{
            // num or id
            Code_Generation(nl->node, ol, local_var_list);
        }
        
        // right
        if (ism_operator(nl->next->node.name)) {
            Code_Generation(nl->next->node, ol, local_var_list);
        }
        else{
            // num or id
            Code_Generation(nl->next->node, ol, local_var_list);

        }
        
        
        GLOBAL_OFFSET-=2;
        
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
        
        op.arg0=intToCString(GLOBAL_OFFSET);
        op.arg1=intToCString(GLOBAL_OFFSET);
        op.arg2=intToCString(GLOBAL_OFFSET+1);
        
        OL_append(ol, op);
        
        GLOBAL_OFFSET++;
        
    }
    
    
    
    
}



















