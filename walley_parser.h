//
//  walley_top_down_parser.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-7.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_list.h"
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

bool term(char *token_class_string,char *terminal){
    if (strcmp(token_class_string, terminal)==0) {
        return TRUE;
    }
    else
        return FALSE;
}

/*
 value    ->num
 | id
 | string
 | list
 | table
 | expr
 
 list     -> '[' elements ']'
            | '[' ']'
 elements -> value ',' elements
            |value

 
 EXP -> 
 
            
 */






/*
 
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
 */

// get index of '*' ... not in parenthesis
/*
int TL_indexOfSignNotInParenthesis(struct TL *tl){
    int length=TL_length(tl);
    int i=0;
    int count_of_parenthesis=0;
    for (; i<length; i++) {
        if (strcmp(tl->current_token.TOKEN_STRING, "(")==0) {
            count_of_parenthesis++;
            tl=tl->next;
            continue;
        }
        if (strcmp(tl->current_token.TOKEN_STRING, ")")==0) {
            count_of_parenthesis--;
             tl=tl->next;
            continue;
        }
        if (count_of_parenthesis==0 && strcmp("m_operator", tl->current_token.TOKEN_CLASS)==0) {
            return i;
        }
        tl=tl->next;
    }
    return -1;
}
int TL_indexOfRequiredSignNotInParenthesis(struct TL *tl,char *required_sign){
    int length=TL_length(tl);
    int i=0;
    int count_of_parenthesis=0;
    for (; i<length; i++) {
        if (strcmp(tl->current_token.TOKEN_STRING, "(")==0) {
            count_of_parenthesis++;
             tl=tl->next;
            continue;
        }
        if (strcmp(tl->current_token.TOKEN_STRING, ")")==0) {
            count_of_parenthesis--;
             tl=tl->next;
            continue;
        }
        if (count_of_parenthesis==0 && strcmp(required_sign, tl->current_token.TOKEN_STRING)==0) {
            return i;
        }
        tl=tl->next;
    }
    return -1;
}
*/





bool expr(TREE *tree, Token_List *tl){
    // expr-> expr '+' expr
    // | expr '-' expr
    // | s_term
    int length_of_tl=TL_length(tl);
    int count_of_parenthesis=0;
    Token_List *temp_tl=tl;

    while (tl->next!=NULL) {
        tl=tl->next;
    }
    
    int i=length_of_tl-1;
    for (; i>=0; i--) {
        if (strcmp(tl->current_token.TOKEN_STRING, "(")==0) {
            count_of_parenthesis++;
            tl=tl->ahead;
            continue;
        }
        if (strcmp(tl->current_token.TOKEN_STRING, ")")==0) {
            count_of_parenthesis--;
            tl=tl->ahead;
            continue;
        }
        // expr '+' expr
        // expr '-' expr
        if (count_of_parenthesis==0 && (strcmp("+", tl->current_token.TOKEN_STRING)==0 || strcmp("-", tl->current_token.TOKEN_STRING)==0 )) {            
            char *sign=tl->current_token.TOKEN_STRING;

            tl=temp_tl;
            int index_of_first_sign=i;
            Token_List *tl1=TL_subtl(tl, 0, index_of_first_sign);
            Token_List *tl2=TL_subtl(tl, index_of_first_sign+1, length_of_tl);
            
            tree->name=sign;
            //TREE_addNode(tree, sign);
           
            int current_index=tree->index;
            TREE_addNode(tree, "expr","");            
            TREE_addNodeAtIndex(tree, current_index, "expr","");
           
            
            int index_of_expr1_node=TREE_INDEX-2;
            int index_of_expr2_node=TREE_INDEX-1;
            
            return
            expr(TREE_getTreeAccordingToIndex(tree,index_of_expr1_node), tl1)
            &&
            expr(TREE_getTreeAccordingToIndex(tree,index_of_expr2_node), tl2);
        }
        
        
        tl=tl->ahead;
        
        
       
    }
    
    tl=temp_tl;
    // s_term
    return s_term(tree, tl);

}

bool s_term(TREE *tree, Token_List *tl){
    
    //s_term -> s_term "*" factor
    //|  s_term "/" factor
    //|  factor
    
    int length_of_tl=TL_length(tl);
    int count_of_parenthesis=0;
    Token_List *temp_tl=tl;
    
    while (tl->next!=NULL) {
        tl=tl->next;
    }
    
    int i=length_of_tl-1;
    for (; i>=0; i--) {
        if (strcmp(tl->current_token.TOKEN_STRING, "(")==0) {
            count_of_parenthesis++;
            tl=tl->ahead;
            continue;
        }
        if (strcmp(tl->current_token.TOKEN_STRING, ")")==0) {
            count_of_parenthesis--;
            tl=tl->ahead;
            continue;
        }
        //    s_term "*" factor
        // |  s_term "/" factor
        if (count_of_parenthesis==0 && (strcmp("*", tl->current_token.TOKEN_STRING)==0 || strcmp("/", tl->current_token.TOKEN_STRING)==0 )) {
            char *sign=tl->current_token.TOKEN_STRING;
            
            tl=temp_tl;
            int index_of_first_sign=i;
            Token_List *tl1=TL_subtl(tl, 0, index_of_first_sign);
            Token_List *tl2=TL_subtl(tl, index_of_first_sign+1, length_of_tl);
            
            //TREE_addNode(tree, sign);
            tree->name=sign;
            
            int current_index=tree->index;
            TREE_addNode(tree, "s_term","");
            TREE_addNodeAtIndex(tree, current_index, "factor","");
            
            int index_of_node1=TREE_INDEX-2;
            int index_of_node2=TREE_INDEX-1;
            
            
            return
            s_term(TREE_getTreeAccordingToIndex(tree,index_of_node1), tl1)
            &&
            factor(TREE_getTreeAccordingToIndex(tree,index_of_node2), tl2);
        }
        
        
        tl=tl->ahead;
        
        
        
    }
    
    tl=temp_tl;

    // factor
    return factor(tree, tl);
}

bool factor(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    if (length_of_tl==1) {
        
        // |num
        if (term(tl->current_token.TOKEN_CLASS, "num")) {
            tree->name=tl->current_token.TOKEN_STRING;
            tree->token_class="num";
            //TREE_addNode(tree, tl->current_token.TOKEN_STRING);
            return TRUE;
        }
        else
            return FALSE;
    }
    else{
        Token token0=TL_tokenAtIndex(tl, 0);
        Token tokenf=TL_tokenAtIndex(tl, length_of_tl-1);
        // |'(' expr ')'
        if (term(token0.TOKEN_STRING, "(")&&term(tokenf.TOKEN_STRING, ")")) {
           // int index=TREE_INDEX-1;
           // TREE_addNode(tree, "expr");
            tree->name="expr";
            tree->token_class="";
            
            
            return expr(tree, TL_subtl(tl, 1, length_of_tl-1));
;
        }
        else
            return FALSE;
    }
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
    //TREE_initWithName(&output_tree,"expr");
    //expr(&output_tree, tl);
    //TREE_print(output_tree);
    
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
    TREE_initWithName(&output_tree,"list");
    list(&output_tree, tl);
    TREE_print(output_tree);
    
   
    
    exit(0);
}














