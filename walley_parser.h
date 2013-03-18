//
//  walley_top_down_parser.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-7.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_lexer.h"
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
struct TREE;
struct Node_List;
int TREE_INDEX=0;
char **TREE_OUTPUT;
struct TREE{
    char *name;
    int index;
    int layer;
    struct Node_List *node_list;
};
struct Node_List{
    struct TREE node;
    struct Node_List *next;
};
void TREE_initWithName(struct TREE *tree,char *name){
    (*tree).name=name;
    (*tree).index=0;
    (*tree).node_list=NULL;
    (*tree).layer=0;
    TREE_INDEX++;
}
typedef struct TREE TREE;
typedef struct Node_List Node_List;
void TREE_addNode(struct TREE *tree, char *name){
    int index=TREE_INDEX;
    // initiate node_list
    if ((*tree).node_list==NULL) {
        (*tree).node_list=(struct Node_List*)malloc(sizeof(struct Node_List)*1);
        (*tree).node_list->next=NULL;
        (*tree).node_list->node.name=name;
        (*tree).node_list->node.index=index;
        (*tree).node_list->node.node_list=NULL;
        (*tree).node_list->node.layer=(*tree).layer+1;
        TREE_INDEX++;
    }
    // append new node
    else{
        Node_List *temp_node_list=(Node_List*)malloc(sizeof(Node_List)*1);
        temp_node_list->node.name=name;
        temp_node_list->node.index=index;
        temp_node_list->node.node_list=NULL;
        Node_List **current_nl=&((*tree).node_list);
        while ((*current_nl)->next!=NULL) {
            current_nl=&((*current_nl)->next);
        }
        temp_node_list->node.layer=(*current_nl)->node.layer;
        (*current_nl)->next=temp_node_list;
        TREE_INDEX++;
    }
}
int NL_length(Node_List *nl){
    int length=0;
    if (nl==NULL) {
        return 0;
    }
    while (nl->next!=NULL) {
        length++;
        nl=nl->next;
    }
    length++;
    return length;
}

TREE *TREE_getTreeAccordingToIndex(TREE *tree,int index){
    
    if (index==tree->index) {
        return tree;
    }
    else{
        Node_List *nl=tree->node_list;
        if (nl==NULL) {
            return NULL;
        }
        int i=0;
        int length=NL_length(nl);
        for (; i<length; i++) {
            if (index==nl->node.index) {
                return &(nl->node);
            }
            else{
                nl=nl->next;
            }
        }
        nl=tree->node_list;
        i=0;
        for (; i<length; i++) {
            TREE *found_tree=TREE_getTreeAccordingToIndex(&(nl->node), index);
            if (found_tree!=NULL) {
                return found_tree;
            }
            else{
                nl=nl->next;
            }
        }
    }
    //printf("DID NOT FOUND NODE %d\n",index);
    return NULL;
}
void NL_print(Node_List *nl);
void TREE_print(TREE tree);
void NL_print(Node_List *nl){
    if (nl==NULL) {
        return;
    }
    TREE_print(nl->node);
    NL_print(nl->next);
}
/*
void TREE_print(TREE tree){
    printf("[%d %d] %s  ",tree.layer,tree.index,tree.name);
    int length_of_node_list=NL_length(tree.node_list);
    
    if (length_of_node_list==0) {
        printf("\n");
    }
   
    
    if (length_of_node_list!=0) {
        //printf("\n");
        printf("[%s : ",tree.name);
        int i=0;
        Node_List *temp_nl=tree.node_list;
        for (; i<length_of_node_list; i++) {
            printf("[%d %d] %s|",temp_nl->node.layer,temp_nl->node.index,temp_nl->node.name);
            temp_nl=temp_nl->next;
        }
        printf("]\n");
        temp_nl=tree.node_list;
        for (i=0; i<length_of_node_list; i++) {
            TREE_print(temp_nl->node);
            temp_nl=temp_nl->next;
        }
        
    }
}
*/
void TREE_print(TREE tree){
    //printf("(%d %s ",tree.index,tree.name);
    printf("(%s ",tree.name);

    int length_of_node_list=NL_length(tree.node_list);
    
   
    if (length_of_node_list!=0) {
        int i=0;
        Node_List *temp_nl=tree.node_list;
        for (i=0; i<length_of_node_list; i++) {
            TREE_print(temp_nl->node);
            temp_nl=temp_nl->next;
        }
    }
    printf(")");
}

void TREE_changeNameAccordingToIndex(TREE *tree, int index, char *change_to_name){
    TREE *temp_tree=TREE_getTreeAccordingToIndex(tree, index);
    (*temp_tree).name=change_to_name;
}
// return the layer num of TREE
int TREE_layer(TREE tree){
    TREE *temp_tree=TREE_getTreeAccordingToIndex(&tree, TREE_INDEX);
    return (*temp_tree).layer;
}

void TREE_addNodeAtIndex(TREE *tree, int index, char *add_name){
    TREE *temp_tree=TREE_getTreeAccordingToIndex(tree, index);
    TREE_addNode(temp_tree, add_name);
}
/*
int main(){
    TREE tree;
    TREE_initWithName(&tree, "walley");
    TREE_addNode(&tree, "x", 1);
    TREE_addNode(&tree, "=", 2);
    TREE_addNode(&tree, "1", 3);
    
    TREE *a=TREE_getTreeAccordingToIndex(&tree, 1);
    TREE_addNode(a, "Hi", 4);
    
    TREE *b=TREE_getTreeAccordingToIndex(&tree, 2);
    TREE_addNode(b, "Hello", 5);
    
    TREE_addNodeAtIndex(&tree, 4, "ADD", 6);
    
    TREE_changeNameAccordingToIndex(&tree, 5,"changed");
    
    printf("%d\n",TREE_INDEX);
    printf("here %d\n",TREE_layer(tree));
    
    
    
    TREE_print(tree);
    return 0;
}
 =====================================================
 OUTPUT--->
 [0 0] walley  [walley : [1 1] x|[1 2] =|[1 3] 1|]
 [1 1] x  [x : [2 4] Hi|]
 [2 4] Hi  [Hi : [3 6] ADD|]
 [3 6] ADD
 [1 2] =  [= : [2 5] changed|]
 [2 5] changed
 [1 3] 1
*/


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
bool list(TREE *tree, Token_List *tl);
bool term(char *token_class,char *terminal){
    if (strcmp(token_class, terminal)==0) {
        return TRUE;
    }
    else
        return FALSE;
}
bool value(TREE *tree, Token_List *tl){
    printf("value\n");
    int length_of_tl=TL_length(tl);
    if (length_of_tl==1) {
        bool can=term("id", tl->current_token.TOKEN_CLASS)
        ||term("num",tl->current_token.TOKEN_CLASS)
        ||term("string",tl->current_token.TOKEN_CLASS);
        printf("here elements |%d|\n",can);
        return term("id", tl->current_token.TOKEN_CLASS)
        ||term("num",tl->current_token.TOKEN_CLASS)
        ||term("string",tl->current_token.TOKEN_CLASS);
    }
    else{
        return list(tree, tl);
    }
}
bool elements(TREE *tree, Token_List *tl){
    printf("elements \n");
    TL_print(tl);
    printf("======\n");
    int length_of_token=TL_length(tl);
    Token first_token=TL_tokenAtIndex(tl, 0);
    Token final_token=TL_tokenAtIndex(tl, length_of_token-1);
    return (
            value(tree, tl)
    );
}
bool list(TREE *tree, Token_List *tl){
    int length_of_token=TL_length(tl);
    Token first_token=TL_tokenAtIndex(tl, 0);
    Token final_token=TL_tokenAtIndex(tl, length_of_token-1);

    return (
            (length_of_token>2&&term(first_token.TOKEN_CLASS, "[") && elements(tree, TL_subtl(tl, 1, length_of_token-1)) && term(final_token.TOKEN_CLASS, "]") )
    ||
        (length_of_token==2 && term(first_token.TOKEN_CLASS, "[") && term(final_token.TOKEN_CLASS, "]"))
            );
}
*/


/*
 first_cal -> num
 | (first_cal)
 | num '+' first_cal
 | num '-' first_cal
 
 */
bool term(char *token_class_string,char *terminal){
    if (strcmp(token_class_string, terminal)==0) {
        return TRUE;
    }
    else
        return FALSE;
}
bool first_cal(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    // | num
    if (length_of_tl==1) {
        TREE_addNode(tree, tl->current_token.TOKEN_STRING);
    }
    else{
        Token first_token=TL_tokenAtIndex(tl, 0);
        Token final_token=TL_tokenAtIndex(tl, length_of_tl-1);
        // | '(' first_cal ')'
        if (strcmp(first_token.TOKEN_STRING, "(")==0 && strcmp(final_token.TOKEN_STRING, ")")==0) {
            TREE_addNode(tree, first_token.TOKEN_STRING);
            int index=TREE_INDEX;
            TREE_addNode(tree, "first_token");
            first_cal(TREE_getTreeAccordingToIndex(tree, index),TL_subtl(tl, 1, length_of_tl-1));
            TREE_addNode(tree, final_token.TOKEN_STRING);
        }
        else{
            Token second_token=TL_tokenAtIndex(tl, 1);
            if (strcmp(second_token.TOKEN_STRING, "+")==0 || strcmp(second_token.TOKEN_STRING, "-")==0) {
                TREE_addNode(tree, first_token.TOKEN_STRING);
                TREE_addNode(tree, second_token.TOKEN_STRING);
                int index=TREE_INDEX;
                TREE_addNode(tree, "first_token");
                first_cal(TREE_getTreeAccordingToIndex(tree, index),TL_subtl(tl, 2, length_of_tl));
            }
            else{
                return FALSE;
            }
        }
        //
    }
    return TRUE;
}


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



bool factor(TREE *tree, Token_List *tl);
bool expr(TREE *tree, Token_List *tl);
bool s_term(TREE *tree, Token_List *tl);



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
            TREE_addNode(tree, "expr");            
            TREE_addNodeAtIndex(tree, current_index, "expr");
           
            
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
            TREE_addNode(tree, "s_term");
            TREE_addNodeAtIndex(tree, current_index, "factor");
            
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

bool func(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    // id
    if (length_of_tl==1) {
        if(strcmp(tl->current_token.TOKEN_CLASS, "id")==0){
            TREE_addNode(tree,tl->current_token.TOKEN_STRING);
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
            TREE_addNode(tree, token0.TOKEN_STRING);
            TREE_addNode(tree, token1.TOKEN_STRING);
            TREE_addNode(tree, token2.TOKEN_STRING);
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
    TREE_initWithName(&output_tree,"expr");
    expr(&output_tree, tl);
    TREE_print(output_tree);
    //Token_List *current_tl=&tl;
    //bool available=list(&output_tree, tl);
    //printf("list available %d\n",available);
    
    exit(0);
}














