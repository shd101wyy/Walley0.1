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
}
typedef struct TREE TREE;
typedef struct Node_List Node_List;
void TREE_addNode(struct TREE *tree, char *name, int index){
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
void TREE_print(TREE tree){
    printf("[%d %d] %s  ",tree.layer,tree.index,tree.name);
    int length_of_node_list=NL_length(tree.node_list);
    int i=0;
    
    if (length_of_node_list==0) {
        printf("\n");
    }
    /*
     for (; i<length_of_node_list; i++) {
     printf("| ");
     }
     */
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
void TREE_changeNameAccordingToIndex(TREE *tree, int index, char *change_to_name){
    TREE *temp_tree=TREE_getTreeAccordingToIndex(tree, index);
    (*temp_tree).name=change_to_name;
}
// return the layer num of TREE
int TREE_layer(TREE tree){
    TREE *temp_tree=TREE_getTreeAccordingToIndex(&tree, TREE_INDEX);
    return (*temp_tree).layer;
}

void TREE_addNodeAtIndex(TREE *tree, int index, char *add_name, int add_index){
    TREE *temp_tree=TREE_getTreeAccordingToIndex(tree, index);
    TREE_addNode(temp_tree, add_name, add_index);
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
 
 list     -> '[' elements ']'
 elements -> value ',' elements
            |value
 
 
 */

TREE parser(Token_List tl){
    TREE output_tree;
    TREE_initWithName(&output_tree,"walley");
    Token_List *current_tl=&tl;
    
    
    
}














