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