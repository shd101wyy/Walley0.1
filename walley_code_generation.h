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
        while (nl->next!=NULL) {
            Code_Generation(nl->node, ol,local_var_list);
            nl=nl->next;
        }
        Code_Generation(nl->node, ol,local_var_list);
        return ;
    }
    
    // global
    if (term(tree.name, "=")) {
        
        // x=12+3
        Node_List *nl=tree.node_list;
        // x=12+3
        if (NL_length(nl)==2) {
            // save var_name
            op.opcode=SETG;
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1="none";
            
            // add to global var list
            var.address=GLOBAL_OFFSET;
            var.var_name=nl->node.name;
            VL_addVar(&GLOBAL_VAR_LIST, var);
            
            OL_append(ol, op);
            
            GLOBAL_OFFSET++;
            
            if (ism_operator(nl->next->node.name)) {
                // x=12+3
                // add 12+3
                Code_Generation(nl->next->node,ol,local_var_list);
            }
            else{
                // x=12
                // 12
                op.opcode=SETG;
                op.arg0=intToCString(GLOBAL_OFFSET);
                op.arg1=getValue(nl->next->node, *local_var_list);
                
                OL_append(ol, op);
                
                GLOBAL_OFFSET++;
            }
            
            
            GLOBAL_OFFSET-=2;
            op.opcode=SETG;
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1=intToCString(GLOBAL_OFFSET+1);
            
            OL_append(ol, op);
            
            GLOBAL_OFFSET++;
            
            
            
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
            op.opcode=SETG;
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1=getValue(nl->node, *local_var_list);
            
            OL_append(ol, op);
            GLOBAL_OFFSET++;
        }
        
        // right
        if (ism_operator(nl->next->node.name)) {
            Code_Generation(nl->next->node, ol, local_var_list);
        }
        else{
            op.opcode=SETG;
            op.arg0=intToCString(GLOBAL_OFFSET);
            op.arg1=getValue(nl->next->node, *local_var_list);
            
            OL_append(ol, op);
            GLOBAL_OFFSET++;
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



















