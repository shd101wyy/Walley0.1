//
//  walley_pre_functions.h
//  Walley
//
//  Created by shd101wyy on 12-12-5.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

char *CURRENT_INPUT_STR="";

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
//#include <dirent.h>
//#include <math.h>
//#include <cmath>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <time.h>
#ifndef _WIN32
typedef int bool;
#include <math.h>
#include <dirent.h>
#else
#include <cmath>
#include "windows_dirent.h"
#endif


#define TRUE 1
#define FALSE 0


#define USING_MATHOMATIC 1

int main(int argc, char **argv);

// walley_string:
struct SL;
typedef struct SL Str_List;

//walley_data:
struct TOKEN;
struct TL;


// new Global Var on April 1st
// both of them are used for check incomplete
bool INCOMPLETE_STATEMENT=FALSE;
bool COUNT_THEN_END=0;

typedef struct TOKEN Token;
typedef struct TL Token_List;


//walley_tree
struct TREE;
struct Node_List;
typedef struct TREE TREE;
typedef struct Node_List Node_List;


//walley_list:
bool value(TREE *tree, Token_List *tl);
bool elements(TREE *tree, Token_List *tl);
bool list(TREE *tree, Token_List *tl);

//walley_parser:
bool term(char *token_class_string,char *terminal);
Token_List *TREE_convertAST(TREE tree);

//walley_math_parse:
bool factor(TREE *tree, Token_List *tl);
bool expr(TREE *tree, Token_List *tl);
bool s_term(TREE *tree, Token_List *tl);
bool p_term(TREE *tree, Token_List *tl);

//walley_table
bool table(TREE *tree, Token_List *tl,int *key_index);
bool table_elements(TREE *tree, Token_List *tl,int *key_index);
bool table_expr(TREE *tree, Token_List *tl,int *key_index);
bool table_value(TREE *tree, Token_List *tl);
bool table_value_key(TREE *tree, Token_List *tl);
//bool pairs(TREE *tree, Token_List *tl);

//walley_assignment
bool list_s(TREE *tree, Token_List *tl);
bool var_name(TREE *tree, Token_List *tl);
bool var_value(TREE *tree, Token_List *tl);

//walley_assignment_function
bool func_assign(TREE *tree, Token_List *tl);
bool return_stm(TREE *tree, Token_List *tl);
bool func_value(TREE *tree, Token_List *tl);

//walley_function
bool params(TREE *tree, Token_List *tl);
bool func(TREE *tree, Token_List *tl);

//walley_class
bool class_property(TREE *tree, Token_List *tl);

//walley_judge
bool simple_relation(TREE *tree, Token_List *tl);
bool relation(TREE *tree, Token_List *tl);

//walley_statments
bool if_stms(TREE *tree, Token_List *tl);
bool elif_stms(TREE *tree, Token_List *tl);
bool else_stms(TREE *tree, Token_List *tl);
bool while_stms(TREE *tree, Token_List *tl);
bool for_stms(TREE *tree, Token_List *tl);
bool func_stms(TREE *tree, Token_List *tl);
bool end_stm(TREE *tree, Token_List *tl);
bool statements(TREE *tree, Token_List *tl);
bool walley_statements(TREE *tree, Token_List *tl);
bool def_stms(TREE *tree, Token_List *tl);

//walley_var
struct Var;
typedef struct Var Var;
struct Var_List;
typedef struct Var_List Var_List;
void VL_printVL(Var_List *vl);
struct Var_List_Set;
typedef struct Var_List_Set Var_List_Set;

//walley_vm

struct Stack;
typedef struct Stack Stack;
enum OPCODE;
char *OPCODE_getFromOpcode(enum OPCODE opcode);
enum OPCODE OPCODE_getFromString(char *input_str);

struct OPERATION;
typedef struct OPERATION OPERATION;

void OPERATION_print(OPERATION operation);
void REGISTER_Print();
//void STACK_Print();
char *const_value(char *input_str);
//int register_index(char *input_str);
char *load_value(char *input_str);
struct OL;
typedef struct OL Operation_List;
void OL_init(struct OL **ol);
void OL_print(struct OL *ol);
void OL_append(struct OL **ol, OPERATION operation);
int OL_length(struct OL *ol);
OPERATION OL_pop(Operation_List **ol);
OPERATION OL_lastOperation(Operation_List *ol);
void VM_RUN_ONE_COMMAND(OPERATION operation);
bool pass(char *value1, char *value2, enum OPCODE opcode);
void VM_Run_Command(struct OL *ol);
void VM_Run_File(char *file_name);
void VM_init();



//walley_function_data_structure
struct Function_List;
typedef struct Function_List Function_List;
void FL_init(Function_List **fl);
void FL_addFuncName(Function_List **fl, char *add_func_name);
void FL_addOperation(Function_List **fl, OPERATION op);
int FL_length(Function_List *fl);
void FL_print(Function_List *fl);

//walley_calculation
char *Walley_Calculation(char *value1, char *value2, char *sign);
double Walley_Operator(double num1,double num2,char sign);
char *cleanDotZeroAfterNumAndKeepOneZero(char *num);

//walley_code_generation
int TABLE_LIST_INDEX=0;
bool NOW_IF=FALSE;
int IF_START=0;
Str_List *STATEMENTS_LIST;
Str_List *WHILE_LIST_OL_INDEX;  // save ol index for while
bool IS_LOCAL_VAR=FALSE;

int LOCAL_OFFSET=0;
Str_List *LOCAL_OFFSET_LIST;    // save LOCAL_OFFSET
bool NOW_FUNCTION=FALSE;  // if now function, add operation to local operation list

int GLOBAL_OFFSET=0;
Var_List *GLOBAL_VAR_LIST;

Var_List_Set *LOCAL_VAR_SET;

// js
char* Code_Generation_2_Javascript(Str_List **sl,TREE tree);



Function_List *FUNCTION_LIST;
Operation_List *OPERATION_LIST;


