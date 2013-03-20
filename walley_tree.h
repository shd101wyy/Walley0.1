//
//  walley_tree.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-19.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_lexer.h"

int TREE_INDEX=0;
char **TREE_OUTPUT;
struct TREE{
    char *name;
    char *token_class;
    int index;
    int layer;
    struct Node_List *node_list;
};
struct Node_List{
    struct TREE node;
    struct Node_List *next;
    struct Node_List *ahead;
};
void TREE_initWithName(struct TREE *tree,char *name){
    (*tree).name=name;
    (*tree).token_class="";
    (*tree).index=0;
    (*tree).node_list=NULL;
    (*tree).layer=0;
    TREE_INDEX++;
}

void TREE_addNode(struct TREE *tree, char *name, char *token_class){
    int index=TREE_INDEX;
    // initiate node_list
    if ((*tree).node_list==NULL) {
        (*tree).node_list=(struct Node_List*)malloc(sizeof(struct Node_List)*1);
        (*tree).node_list->next=NULL;
        (*tree).node_list->ahead=NULL;
        (*tree).node_list->node.name=name;
        (*tree).node_list->node.token_class=token_class;
        (*tree).node_list->node.index=index;
        (*tree).node_list->node.node_list=NULL;
        (*tree).node_list->node.layer=(*tree).layer+1;
        TREE_INDEX++;
    }
    // append new node
    else{
        Node_List *temp_node_list=(Node_List*)malloc(sizeof(Node_List)*1);
        temp_node_list->node.name=name;
        temp_node_list->node.token_class=token_class;
        temp_node_list->node.index=index;
        temp_node_list->node.node_list=NULL;
        temp_node_list->next=NULL;
        
        Node_List **current_nl=&((*tree).node_list);
        while ((*current_nl)->next!=NULL) {
            current_nl=&((*current_nl)->next);
        }
        temp_node_list->node.layer=(*current_nl)->node.layer;
        (*current_nl)->next=temp_node_list;
        (*current_nl)->next->ahead=(*current_nl);
        TREE_INDEX++;
    }
}

void TREE_addTree(struct TREE *tree, struct TREE add_tree){
    int index=TREE_INDEX;
    // initiate node_list
    if ((*tree).node_list==NULL) {
        (*tree).node_list=(struct Node_List*)malloc(sizeof(struct Node_List)*1);
        (*tree).node_list->next=NULL;
        (*tree).node_list->ahead=NULL;
        (*tree).node_list->node=add_tree;
        (*tree).node_list->node.index=index;
        //(*tree).node_list->node.node_list=NULL;
        (*tree).node_list->node.layer=(*tree).layer+1;
        TREE_INDEX++;
    }
    // append new node
    else{
        Node_List *temp_node_list=(Node_List*)malloc(sizeof(Node_List)*1);
        temp_node_list->node=add_tree;
        temp_node_list->node.index=index;
        //temp_node_list->node.node_list=NULL;
        temp_node_list->next=NULL;

        
        Node_List **current_nl=&((*tree).node_list);
        while ((*current_nl)->next!=NULL) {
            current_nl=&((*current_nl)->next);
        }
        temp_node_list->node.layer=(*current_nl)->node.layer;
        (*current_nl)->next=temp_node_list;
        (*current_nl)->next->ahead=(*current_nl);
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
    printf("(%s %s",tree.token_class,tree.name);
    
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

void TREE_addNodeAtIndex(TREE *tree, int index, char *add_name, char *add_token_class){
    TREE *temp_tree=TREE_getTreeAccordingToIndex(tree, index);
    TREE_addNode(temp_tree, add_name, add_token_class);
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
