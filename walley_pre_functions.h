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
