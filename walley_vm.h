//
//  walley_vm.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-11.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_parser.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Stack{
    char *value;
};


// eg var_name :a  address :0
//    then found value of a at address 0
struct Var_Table{
    char *var_name;
    int address;
};


// #3  means const value
// 3   means address 3
// r1  means register 1

enum OPCODE{
    ADD,      // ADD arg0 arg1 arg2 ; +
    SUB,      // SUB arg0 arg1 arg2 ; -
    MUL,      // MUL arg0 arg1 arg2 ; *
    DIV,      // DIV arg0 arg1 arg2 ; /
    MOD,      // MOD arg0 arg1 arg2 ; %
    POW,      // POW arg0 arg1 arg2 ; ^
    LOADG,     // LOADG dest from   ; load global value
    LOADL,     // LOADL dest from   ; load local value
    PRINT,    // PRINT arg0         ;
    HALT,     // HALT               ;
    SETG,     // SETG dest value    ; set global value
    SETL,     // SETL dest value    ; set local value
    MOVE,     // MOVE dest from     ; move value
    JMP       // JMP steps          ; jump steps.. eg jump -2   --> jump back 2 steps
};

typedef struct OPERATION{
    enum OPCODE opcode;
    char *arg0;
    char *arg1;
    char *arg2;
}OPERATION;

typedef struct REGISTER{
    char *value;
}REGISTER;


#define MAX_STACK 256
#define MAX_LOCAL_VALUE 60
#define REGISTER_NUM 4
int PC=0;
int GLOBAL_COUNT=0;
int LOCAL_COUNT=255;
struct Stack stack[MAX_STACK];
REGISTER register_w[REGISTER_NUM];

void REGISTER_Print(){
    int i=0;
    printf("REGISTER\n");
    printf("========\n");
    for (; i<REGISTER_NUM; i++) {
        printf("[%d] --> %s\n",i,register_w[i].value);
    }
    printf("\n\n");
}

void STACK_Print(){
    int i=MAX_STACK-1;
    printf("STACK\n");
    printf("========\n");
    for (; i>=0; i--) {
        if (stack[i].value==NULL) {
            continue;
        }
        printf("[%d] --> %s\n",i,stack[i].value);
    }
    printf("\n\n");
    
}


// #100 return 100
char *const_value(char *input_str){
    int length=(int)strlen(input_str);
    char *return_value=(char*)malloc(sizeof(char)*length);
    int i=0;
    for (; i<length-1; i++) {
        return_value[i]=input_str[i+1];
    }
    return_value[i]=0;
    return return_value;
}

// r1 return 1
int register_index(char *input_str){
    if (input_str[0]!='r') {
        printf("Error..it is not register\n");
        exit(0);
    }
    int length=(int)strlen(input_str);
    char *return_value=(char*)malloc(sizeof(char)*length);
    int i=0;
    for (; i<length-1; i++) {
        return_value[i]=input_str[i+1];
    }
    return_value[i]=0;
    int return_int=atoi(return_value);
    if (return_int>=REGISTER_NUM) {
        printf("Error..unavailable register %d\n",return_int);
        exit(0);
    }
    return return_int;
}

// #100 return 100
// r1 return value in r1
char *load_value(char *input_str){
    if (input_str[0]=='#') {
        return const_value(input_str);
    }
    else if (input_str[0]=='r'){
        return register_w[register_index(input_str)].value;
    }
    else
        return stack[atoi(input_str)].value;
}

void VM_RUN_ONE_COMMAND(OPERATION operation){
    char *arg0=NULL;
    char *arg1=NULL;
    char *arg2=NULL;
    int r_index1=NULL;
    int r_index2=NULL;
    int s_index=NULL;
    
    switch (operation.opcode) {
        case LOADG:
            // LOAD r1 #100
            r_index1=register_index(operation.arg0);
            arg1=load_value(operation.arg1);
            register_w[r_index1].value=arg1;
            break;
            
        case MOVE:
            // MOVE r1 r2
            r_index1=register_index(operation.arg0);
            r_index2=register_index(operation.arg1);
            register_w[r_index1].value=register_w[r_index2].value;
            
        case SETG:
            // SETG 0 r1
            s_index=atoi(operation.arg0);
            arg1=load_value(operation.arg1);
            stack[s_index].value=arg1;
            
        default:
            break;
    }
}

/*
int main(){
    
    struct OPERATION prog[10];
    
    prog[0]=(struct OPERATION){SETG,"0","#1200"};
    prog[1]=(struct OPERATION){LOADG,"r1","0"};
    prog[2]=(struct OPERATION){MOVE,"r0","r1"};
    
    
    VM_RUN_ONE_COMMAND(prog[0]);
    VM_RUN_ONE_COMMAND(prog[1]);
    VM_RUN_ONE_COMMAND(prog[2]);
    
    
    REGISTER_Print();
    STACK_Print();
    
    //prog[1]=(struct OPERATION){SETG,"0","r1"};
    
    
	return 0;
}

*/
























