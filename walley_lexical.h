//
//  walley_lexical.h
//  Walley
//
//  Created by shd101wyy on 13-2-12.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_data.h"
/*
    m_operator-> add_sign
             | minus_sign
             | mult_sign
             | div_sign
             | mode_sign
             | pow_sign
 
    add_sign   -> '+'
    minus_sign -> '-'
    mult_sign  -> '*'
    div_sign   -> '/'
    mode_sign  -> '%'
    pow_sign   -> '**'
                | '^'
 
    punctuation -> ','
                | ';'
                | '.'
                | ':'
 
 
    judge_sign -> '>'
                | '<'
                | '=='
                | '>='
                | '<='
                | '!='
 
    l_annotation -> '#~'
    annotation   -> '#'
    r_annotation -> '~#'
 
    keyword  -> if_stat
     |switch_stat
     |for_stat
     |while_stat
     |def_stat
     |class_stat
 
     if_stat-> 'if'
     | 'elif'
     | 'else'
 
     switch_stat -> 'switch'
     | 'case'
     
     while_stat -> 'while'
     
     for_stat -> 'for'
     
     def_stat -> 'def'
     
     class_stat -> 'class'

 
    assignment_operator -> '='
 
 
 //   left_p     -> '('
 //   right_p    -> ')'
 //  left_rp    -> '['
 //   right_rp   -> ']'
 //   left_fep   -> '{'   //function expression parenthesis
 //   right_fep  -> '}'
 
     (     -> '('
     )    -> ')'
     [    -> '['
     ]   -> ']'
     {   -> '{'   //function expression parenthesis
     }  -> '}'

 
 
 
    double_quote -> "
    // no single quote available
 
    string       -> double_quote content double_quote

 
    num      -> int
              | double
 
    int      -> [0-9]+
    double   -> [0-9]+ '.' [0-9]+
 
    id       -> [a-zA-Z_][a-zA-Z0-9_]*

    white_space -> (' '|'\n'|'\t')+
 
    * can not be analyzed
 
 =============================================================================================================
 */












bool is_id(char *input_str){
    int i=0;
    int length=(int)strlen(input_str);
    
    bool has_alpha=FALSE;
    
    // check whether has alpha
    for (; i<length; i++) {
        if (isalpha(input_str[0])) {
            has_alpha=TRUE;
            break;
        }
    }
    if (has_alpha==FALSE) {
        return FALSE;
    }
    
    // 2a is not allowed
    if (isdigit(input_str[0])) {
        return FALSE;
    }
    return TRUE;
}

char *Walley_Analyze_Token_Class(char *input_str){
        // m_operator
    if (strcmp(input_str, "+")==0
        ||strcmp(input_str, "-")==0
        ||strcmp(input_str, "*")==0
        ||strcmp(input_str, "/")==0
        ||strcmp(input_str, "%")==0
        ||strcmp(input_str, "^")==0
        ||strcmp(input_str, "**")==0
        ) {
        return "m_operator";
    }
    
    if (strcmp(input_str, ",")==0
        ||strcmp(input_str, ";")==0
        ||strcmp(input_str, ".")==0
        ||strcmp(input_str, ":")==0
        ) {
        return "punctuation";
    }
    
    if (strcmp(input_str, ">")==0
        ||strcmp(input_str, "<")==0
        ||strcmp(input_str, "==")==0
        ||strcmp(input_str, ">=")==0
        ||strcmp(input_str, "<=")==0
        ||strcmp(input_str, "!=")==0

        ) {
        return "judge_sign";
    }
    
    if (strcmp(input_str, "#~")==0) {
        return "l_annotation";
    }
    

    if (strcmp(input_str, "~#")==0) {
        return "r_annotation";
    }

    if(strcmp(input_str, "if")==0
       ||strcmp(input_str, "elif")==0
       ||strcmp(input_str, "else")==0
       ||strcmp(input_str, "switch")==0
       ||strcmp(input_str, "case")==0
       ||strcmp(input_str, "for")==0
       ||strcmp(input_str, "while")==0
       ||strcmp(input_str, "def")==0
       ||strcmp(input_str, "class")==0
       ){
        return "keyword";
    }

    if(strcmp(input_str, "=")==0)
        return "assignment_operator";

    


    if(strcmp(input_str, "#")==0){
        return "annotation";
    }

    if(strcmp(input_str, "(")==0
       ||strcmp(input_str, ")")==0
       ||strcmp(input_str, "[")==0
       ||strcmp(input_str, "]")==0
       ||strcmp(input_str, "{")==0
       ||strcmp(input_str, "}")==0
       ){
        return input_str;
    }

    if(input_str[0]=='"' && input_str[(int)strlen(input_str)-1]=='"'){
        return "string";
    }

    if(stringIsDigit(input_str))
        return "num";

    int i=0;
    bool is_white_space=TRUE;
    for (i=0; i<(int)strlen(input_str); i++) {
            if(input_str[i]!=' '
               &&input_str[i]!='\n'
               &&input_str[i]!='\t'){
                is_white_space=FALSE;
                break;
            }
    }
    if(is_white_space){
        return "white_space";
    }

    bool isid=is_id(input_str);
    if (isid) {
        return "id";
    }
    
    printf("Can not analyze %s\n",input_str);
    exit(0);
}


struct TL * Walley_Lexical_Analyzie(char *input_str){
    int i=0;
    int length=(int)strlen(input_str);
    Token_List *tl;
    TL_init(&tl);
    
    int start=0;
    int end=0;
    
    
    
    return NULL;
}
































 /*
 ============================================================================================================
 
    math_exp -> m_add
               |m_mult
               |m_div
               |m_minus
               |m_mode
               |m_pow
 
    m_add -> num
            | '(' num ')'
            | num '+' num
            | num '+' math_exp
    m_minus -> num
            | '(' num ')'
            | num '-' num
            | num '-' math_exp
    m_mult -> num
            | '(' num ')'
            | num '*' num
            | num '*' math_exp
    m_div -> num
        | '(' num ')'
        | num '/' num
        | num '+' math_exp
    m_mode -> num
        | '(' num ')'
        | num '%' num
        | num '%' math_exp
    m_power -> num
        | '(' num ')'
        | num pow_sign num
        | num pow_sign math_exp
 
 
 
    value    ->num
             | id
             | string
             | list
             | table
 
 
    //------ LIST -------
 
    list     -> '[' elements ']'
    elements -> value ',' elements
             -> value
    
    //------ TABLE ------
 
    table    -> '[' table_elements ']'
    table_elements -> table_expr
                    | table_expr ',' table_elements
    // table_expr  ["a"]=12 [0]=14
    table_expr -> '[' (string|int) ']' '=' (value)
    
 
  
 
    if -> 'if' judge_expr ':'
        | 'elif' judge_expr ':'
        | 'else' ':'
     
    judge_exp->
    
*/