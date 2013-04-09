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
bool INCOMPLETE_STATEMENT=FALSE;

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

Function_List *FUNCTION_LIST;
Operation_List *OPERATION_LIST;


//=============


struct VAR;
struct TOKEN;



char *TEMP_FUNCTION_PARAMETER;
char *TEMP_FUNCTION_NAME;

//void Walley_Initialize_Settings_File(char *settings_file_name);
//void Walley_Initialize_Var_File(char *file_var_name);
void Walley_Initialize();
void Walley_Finalize();
char *Walley_Print(struct VAR **struct_var,char ***FUNCTION_functions, char *input_str);
char *Walley_Println(struct VAR **struct_var,char ***FUNCTION_functions, char *input_str);
void Walley_Initialize_Var(struct VAR **var);
void Walley_Initialize_Settings(struct VAR **settings);
char *Walley_Run_One_Function_And_Return_Value_From_Var(char *input_str,struct VAR **struct_var,char ***FUNCTION_function);
void Walley_Update_Var_And_Var_Value_To_Var(struct VAR **struct_var, char *var_name, char *var_value);
void Walley_Eval_And_Update_Var_And_Value_To_Var(struct VAR **struct_var,char ***FUNCTION_functions,char* input_str) ;
void Walley_Judge_Run_Anotation_For_While_Def_Class(struct VAR **struct_var,struct VAR **struct_settings,char ***FUNCTION_functions,char *input_str,struct TOKEN *token);
char *Walley_Translate_To_Function_From_Var(char *input_str, char *best_match_sentence, struct VAR **struct_var);

void Walley_Update_Functions_And_Vars_While_Importing(char *temp_file_to_run, struct VAR **struct_var, char ***FUNCTION_functions);
void Walley_Run(char *input_str);

char *Walley_Slice(char *var_value, char *slice,struct VAR **struct_var, char ***FUNCTION_functions);
void Walley_Next(struct TOKEN *token, int *current_index, char **current_value, struct VAR **struct_var, char **FUNCTION_functions);

char *cleanUpSentence(char *input_str);


void Walley_Parse_Simple_String(struct VAR **struct_var, struct VAR **struct_settings, char* existing_file, char ***FUNCTION_functions, char *input_str);
void Walley_Parse_String_List(struct VAR **struct_var, struct VAR **struct_settings, char *existing_file, char ***FUNCTION_functions, char **input_str);
char *Walley_Run_One_Function_And_Return_Value_From_Var(char *input_str,struct VAR **struct_var, char ***FUNCTION_functions);
char *Walley_Substitute_Var_And_Function_According_To_Token(struct TOKEN **token_list,struct VAR **struct_var, char ***FUNCTION_functions);
void Walley_Eval_And_Update_Var_And_Value_To_Var_According_To_Token(struct VAR **struct_var,char ***FUNCTION_functions,struct TOKEN *var_name_token_list,struct TOKEN *var_value_token_list);
void Walley_Judge_Run_Anotation_For_While_Def_Class_According_To_Token(struct VAR **struct_var,struct VAR **struct_settings,char ***FUNCTION_functions, struct TOKEN *token_list);
bool Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_According_To_Token(struct TOKEN *token_list, struct VAR **struct_var, char ***FUNCTION_functions);
