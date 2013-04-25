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

// run script in cmd
void Walley_Run(){
    
    // save incomplete statements
    Str_List *saved_str_list;
    SL_initSL(&saved_str_list);
    
    bool begin=FALSE;
    while (1) {
        
        printf("\n>>> ");
        char *input_str=(char*)malloc(sizeof(char)*1000);
        gets(input_str);
        if (strcmp(input_str, "exit()") == 0)
            break;
        
        Token_List *tl=Walley_Lexical_Analyzie(input_str);
        
        
        // now complete
        if (begin==TRUE && COUNT_THEN_END==0) {
            
            SL_print(saved_str_list);
            begin=FALSE;
            
            char *saved_string=SL_toString(saved_str_list);
            //printf("SAVED_STRING---> %s\n",saved_string);
            
            // reinitialize saved_str_list
            SL_initSL(&saved_str_list);
            
            // append saved_string + input_str
            int malloc_length=(int)strlen(saved_string)+(int)strlen(input_str);
            char *input_str2=(char*)malloc(sizeof(char)*(1+malloc_length));
            strcpy(input_str2, saved_string);
            strcat(input_str2, input_str);
            input_str2[malloc_length]=0;
            
            // regenerate tl
            tl=Walley_Lexical_Analyzie(input_str2);
            
            // reset INCOMPLETE_STATEMENT
            INCOMPLETE_STATEMENT=FALSE;
        }
        
        // incomplete statements
        if (COUNT_THEN_END!=0 || INCOMPLETE_STATEMENT) {
            //printf("COUNT_THEN_END-->%d incomplete \n",COUNT_THEN_END);
            begin=TRUE;
            
            // append space after input_str
            int malloc_length=(int)strlen(input_str);
            char *input_str2=(char*)malloc(sizeof(char)*(2+malloc_length));
            strcpy(input_str2, input_str);
            strcat(input_str2," ");
            input_str2[1+malloc_length]=0;
            
            SL_addString(&saved_str_list, input_str2);
            continue;
        }
        
        //printf("Token_List===============\n");
        //TL_print(tl);
        
        TREE syntax_tree=parser(tl);
        
        
        // incomplete statements
        if (COUNT_THEN_END!=0 || INCOMPLETE_STATEMENT) {
            //printf("COUNT_THEN_END-->%d incomplete \n",COUNT_THEN_END);
            begin=TRUE;
            
            // append space after input_str
            int malloc_length=(int)strlen(input_str);
            char *input_str2=(char*)malloc(sizeof(char)*(2+malloc_length));
            strcpy(input_str2, input_str);
            strcat(input_str2," ");
            input_str2[1+malloc_length]=0;
            
            SL_addString(&saved_str_list, input_str2);
            continue;
        }

        
        
        printf("==========\n");
        if (NOW_FUNCTION) {
            Code_Generation(syntax_tree, &(FUNCTION_LIST->current_ol),&(FUNCTION_LIST->next_in_function));
        }
        
        else{
            Code_Generation(syntax_tree, &OPERATION_LIST,&FUNCTION_LIST);
        }
        
    
        
        printf("\n\nFUNCTION_LIST===========\n");
        FL_print(FUNCTION_LIST);
        printf("OPERATION_LIST============\n");
        
        OL_print(OPERATION_LIST);
         
    }
}


void Test(char *input_str){
    char *to_analyze_str=input_str;
    //printf("input_str--------> %s\n",input_str);
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