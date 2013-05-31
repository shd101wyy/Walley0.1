//
//  walley_math_parser.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-20.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_table.h"
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
 
 Calculation version 1.2
 expr-> expr '+' expr
 | expr '-' expr
 | s_term
 s_term -> s_term "*" p_term
 |  s_term "/" p_term
 |  p_term
 p_term -> p_term "^" factor
 |  factor
 factor -> num
 | (expr)
 
 Calculation version 1.3
 expr-> expr '+' expr
 | expr '-' expr
 | s_term
 s_term -> s_term "*" p_term
 |  s_term "/" p_term
 |  s_term "%" p_term
 |  p_term
 p_term -> p_term "^" factor
 |  factor
 factor -> value
 | (expr)
 
 
 where "*" "/" "+" "-" are sign not in () from behind
 */






bool expr(TREE *tree, Token_List *tl){
    
    Token_List *original_tl=tl;

    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    
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
                        
            // solve x=-1 or x=+1 problem
            if (index_of_first_sign==0) {
                Token_List *temp_tl;
                Token token;
                token.TOKEN_STRING="0";
                token.TOKEN_CLASS="num";
                token.TOKEN_START=-1;
                token.TOKEN_END=-1;
                TL_initWithToken(&temp_tl,token);
                temp_tl->next=original_tl;
                
                return expr(tree, temp_tl);
                
            }
            
            
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
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    //s_term -> s_term "*" p_term
    //|  s_term "/" p_term
    //|  p_term
    
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
        //    s_term "*" p_term
        // |  s_term "/" p_term
        if (count_of_parenthesis==0 && (strcmp("*", tl->current_token.TOKEN_STRING)==0 || strcmp("/", tl->current_token.TOKEN_STRING)==0 || strcmp("%", tl->current_token.TOKEN_STRING)==0)) {
            char *sign=tl->current_token.TOKEN_STRING;
            
            tl=temp_tl;
            int index_of_first_sign=i;
            Token_List *tl1=TL_subtl(tl, 0, index_of_first_sign);
            Token_List *tl2=TL_subtl(tl, index_of_first_sign+1, length_of_tl);
            
            
            //TREE_addNode(tree, sign);
            tree->name=sign;
            
            int current_index=tree->index;
            TREE_addNode(tree, "s_term","");
            TREE_addNodeAtIndex(tree, current_index, "p_term","");
            
            int index_of_node1=TREE_INDEX-2;
            int index_of_node2=TREE_INDEX-1;
            
            
            return
            s_term(TREE_getTreeAccordingToIndex(tree,index_of_node1), tl1)
            &&
            p_term(TREE_getTreeAccordingToIndex(tree,index_of_node2), tl2);
        }
        
        
        tl=tl->ahead;
        
        
        
    }
    
    tl=temp_tl;
    
    // p_term
    return p_term(tree, tl);
}

bool p_term(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    
    //p_term -> p_term "^" factor
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
        
        //    p_term "^" factor
        if (count_of_parenthesis==0 && (strcmp("^", tl->current_token.TOKEN_STRING)==0
                                            ||strcmp("**", tl->current_token.TOKEN_STRING)==0 )) {
            //char *sign=tl->current_token.TOKEN_STRING;
            char *sign="^";

            tl=temp_tl;
            int index_of_first_sign=i;
            Token_List *tl1=TL_subtl(tl, 0, index_of_first_sign);
            Token_List *tl2=TL_subtl(tl, index_of_first_sign+1, length_of_tl);
            
            //TREE_addNode(tree, sign);
            tree->name=sign;
            
            int current_index=tree->index;
            TREE_addNode(tree, "p_term","");
            TREE_addNodeAtIndex(tree, current_index, "factor","");
            
            int index_of_node1=TREE_INDEX-2;
            int index_of_node2=TREE_INDEX-1;
            
            
            return
            p_term(TREE_getTreeAccordingToIndex(tree,index_of_node1), tl1)
            &&
            factor(TREE_getTreeAccordingToIndex(tree,index_of_node2), tl2);
        }
        
        
        tl=tl->ahead;
        
        
        
    }
    
    tl=temp_tl;
    
    // factor
    return factor(tree, tl);
}

//factor -> value
//| (expr)
bool factor(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    //| (expr)
    if (term(TL_tokenAtIndex(tl, 0).TOKEN_STRING,"(")&&term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, ")")) {
        tree->name="expr";
        tree->token_class="";
        
        
        return expr(tree, TL_subtl(tl, 1, length_of_tl-1));
    }
    // value
    else{
        return value(tree, tl);
    }
}






















