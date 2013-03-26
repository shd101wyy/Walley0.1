//
//  walley_top_down_parser.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-7.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_statements.h"

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








// Generate AST
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
    //TREE_initWithName(&output_tree,"list");
    //list(&output_tree, tl);
    //TREE_print(output_tree);
    
    // test pairs
    //TREE_initWithName(&output_tree,"pairs");
    //pairs(&output_tree, tl);
    //TREE_print(output_tree);
    
    // test assignment
    //TREE_initWithName(&output_tree,"assignment");
    //assignment(&output_tree, tl);
    //TREE_print(output_tree);
   
    // test params
    //TREE_initWithName(&output_tree,"params");
    //params(&output_tree, tl);
    //TREE_print(output_tree);
    
    // test func
    //TREE_initWithName(&output_tree,"func");
    //func(&output_tree, tl);
    //TREE_print(output_tree);

    // test class_property
    //TREE_initWithName(&output_tree,"class_property");
    //class_property(&output_tree, tl);
    //TREE_print(output_tree);
    
    
    // test simple_relation
    //TREE_initWithName(&output_tree,"simple_relation");
    //simple_relation(&output_tree, tl);
    //TREE_print(output_tree);
    
    // test relation
    //TREE_initWithName(&output_tree,"relation");
    //relation(&output_tree, tl);
    //TREE_print(output_tree);
    
    
    // test statements
    TREE_initWithName(&output_tree,"statements");
    statements(&output_tree, tl);
    TREE_print(output_tree);

    //exit(0);
    
    return output_tree;
}



// Convert AST to token list
/*
    +
   / \
   3  4
 
 convert to ->
 
 3 4 +
 
    +
   / \
  *   /
 / \  / \
 1 2  3  4
 
 conver to ->
 
 1 2 * 3 4 / +
 
 */

Token_List *TREE_convertAST(TREE tree){
    Token_List *output_tl;
    TL_init(&output_tl);
    
    Node_List *nl=tree.node_list;
    int length_of_nl=NL_length(nl);
    
    if (length_of_nl!=0) {
        int i=0;
        for (; i<length_of_nl; i++) {
            TREE temp_tree=nl->node;
            
            Token_List *temp_tl=TREE_convertAST(temp_tree);
            int length_of_temp_tl=TL_length(temp_tl);
            int j=0;
            for (; j<length_of_temp_tl; j++) {
                TL_addToken(&output_tl, temp_tl->current_token);
                temp_tl=temp_tl->next;
            }
            
            nl=nl->next;
        }
        
        Token addToken;
        addToken.TOKEN_STRING=tree.name;
        addToken.TOKEN_CLASS=tree.token_class;
        addToken.TOKEN_START=0;
        addToken.TOKEN_END=0;
        TL_addToken(&output_tl, addToken);

        
    }
    else{
        Token addToken;
        addToken.TOKEN_STRING=tree.name;
        addToken.TOKEN_CLASS=tree.token_class;
        addToken.TOKEN_START=0;
        addToken.TOKEN_END=0;
        TL_addToken(&output_tl, addToken);
        return output_tl;
    }
    
    return output_tl;
    
}












