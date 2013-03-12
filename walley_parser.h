//
//  walley_top_down_parser.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-7.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_lexical.h"
/*
    PARSER SO HARD
    I GIVE UP NOW
 */
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

