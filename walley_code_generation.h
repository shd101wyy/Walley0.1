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
                op.opcode=SET;
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
            op.opcode=SET;
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

