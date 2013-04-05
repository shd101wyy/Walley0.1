//
//  walley_function_data_type.h
//  Walley0.1
//
//  Created by shd101wyy on 13-4-4.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_vm.h"

struct Function_List{
    char *function_name;
    Operation_List *current_ol;
    struct Function_List *next;
    struct Function_List *next_in_function;
};

void FL_init(Function_List **fl){
    (*fl)=(Function_List *)malloc(sizeof(Function_List)*1);
    (*fl)->function_name=NULL;
    (*fl)->current_ol=NULL;
    (*fl)->next=NULL;
    (*fl)->next_in_function=NULL;
}

void FL_addFuncName(Function_List **fl, char *add_func_name){
    if ((*fl)->function_name==NULL) {
        (*fl)->function_name=add_func_name;
    }
    else{
        Function_List **temp_fl=&(*fl);
        while ((*temp_fl)->next!=NULL) {
            if (term((*temp_fl)->function_name, add_func_name)) {
                printf("Attention.. Same function_name\n");
            }
            temp_fl=&((*temp_fl)->next);
        }
        
        Function_List *add_fl;
        FL_init(&add_fl);
        add_fl->function_name=add_func_name;
        
        (*temp_fl)->next=add_fl;
    }
}

void FL_addOperation(Function_List **fl, OPERATION op){
    if ((*fl)->function_name==NULL) {
        printf("Error.. U need to define a function name at first\n");
    }
    else{
        if ((*fl)->current_ol==NULL) {
            OL_init(&((*fl)->current_ol));
            OL_append(&((*fl)->current_ol), op);
        }
        else{
            Function_List **temp_fl=&(*fl);
            while ((*temp_fl)->next!=NULL) {
                temp_fl=&((*temp_fl)->next);
            }
            if ((*temp_fl)->current_ol==NULL) {
                OL_init(&((*temp_fl)->current_ol));
            }
            OL_append(&((*temp_fl)->current_ol), op);
        }
    }
}

int FL_length(Function_List *fl){
    if (fl->function_name==NULL) {
        return 0;
    }
    int length=0;
    while (fl->next!=NULL) {
        length++;
    }
    return length+1;
}

void FL_print(Function_List *fl){
    if (fl->function_name==NULL) {
        return;
    }
    while (fl->next!=NULL) {
        printf("\n\nfunc_name : %s\n===============\n",fl->function_name);
        OL_print(fl->current_ol);
        fl=fl->next;
    }
    printf("func_name : %s\n",fl->function_name);
    OL_print(fl->current_ol);
}