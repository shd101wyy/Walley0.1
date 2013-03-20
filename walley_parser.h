//
//  walley_top_down_parser.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-7.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_math_parser.h"

/*
 ============================================================================================================
 
 
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
 
 
 
 Calculation version 1.1
 expr-> expr '+' expr
 | expr '-' expr
 | s_term
 s_term -> s_term "*" factor
 |  s_term "/" factor
 |  factor
 
 factor -> num
 | (expr)
 
 where "*" "/" "+" "-" are sign not in () from behind
 
 
 
 if -> 'if' judge_expr ':'
 | 'elif' judge_expr ':'
 | 'else' ':'
 
 judge_exp->

 */

bool term(char *token_class_string,char *terminal){
    if (strcmp(token_class_string, terminal)==0) {
        return TRUE;
    }
    else
        return FALSE;
}






/*
 def func(params):
 
 func-> id
      | id '.' id
 */


/*
 
 params-> params ',' params
       -> value
 
 */

bool func(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    // id
    if (length_of_tl==1) {
        if(strcmp(tl->current_token.TOKEN_CLASS, "id")==0){
            TREE_addNode(tree,tl->current_token.TOKEN_STRING,"id");
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    // id '.' id
    else if (length_of_tl==3)
    {
        Token token0=TL_tokenAtIndex(tl, 0);
        Token token1=TL_tokenAtIndex(tl, 1);
        Token token2=TL_tokenAtIndex(tl, 2);
        if (term(token0.TOKEN_CLASS, "id")&&term(token1.TOKEN_STRING, ".")&&term(token2.TOKEN_CLASS, "id")) {
            TREE_addNode(tree, token0.TOKEN_STRING,"id");
            TREE_addNode(tree, token1.TOKEN_STRING,"");
            TREE_addNode(tree, token2.TOKEN_STRING,"id");
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    else{
        return FALSE;
    }
}



TREE parser(Token_List *tl){
    // reset TREE_INDEX value
    TREE_INDEX=0;
    
    TREE output_tree;
    
    // test expr
    TREE_initWithName(&output_tree,"expr");
    expr(&output_tree, tl);
    TREE_print(output_tree);
    
    // test value
    //TREE_initWithName(&output_tree,"value");
    //int is_value=value(&output_tree, tl);
    //printf("is_value %d\n",is_value);
    //TREE_print(output_tree);

    // test elements
    //TREE_initWithName(&output_tree,"elements");
    //elements(&output_tree, tl);
    //TREE_print(output_tree);
    
    // test list
    //TREE_initWithName(&output_tree,"list");
    //list(&output_tree, tl);
    //TREE_print(output_tree);
    
   
    
    exit(0);
}














