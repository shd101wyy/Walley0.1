//
//  walley.h
//  Walley0.1
//
//  Created by shd101wyy on 13-4-6.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//
#include "walley_code_generation.h"

void Walley_Init(){
    VLS_init(&LOCAL_VAR_SET);
    VL_init(&GLOBAL_VAR_LIST);
    SL_initSL(&STATEMENTS_LIST);
    SL_initSL(&WHILE_LIST_OL_INDEX);
    FL_init(&FUNCTION_LIST);
    OL_init(&OPERATION_LIST);
    SL_initSL(&LOCAL_OFFSET_LIST);
    LOCAL_OFFSET=0;
    GLOBAL_OFFSET=0;
}


void Test(char *input_str){
    char *to_analyze_str=input_str;
    printf("input_str--------> %s\n",input_str);
    struct TL *tl=Walley_Lexical_Analyzie(to_analyze_str);
    TL_print(tl);
    TREE output_tree=parser(tl);
    
    if (NOW_FUNCTION) {
        Code_Generation(output_tree, &(FUNCTION_LIST->current_ol),&(FUNCTION_LIST->next_in_function));
    }
    
    else{
        Code_Generation(output_tree, &OPERATION_LIST,&FUNCTION_LIST);
    }
    
    OPERATION op;
    op.opcode=$;
    op.arg0="===================";
    op.arg1=NULL;
    op.arg2=NULL;
    OL_append(&OPERATION_LIST, op);
    
}