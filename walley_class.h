//
//  walley_class.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//
#include "walley_function.h"

/*
 
 // I GIVE UP THIS PART
 
 a.value
 a.length()
 a.value.length()
 
 
 a.value.length()
 ( ((a)(value)) (func length))
 
                
 where . is found from behind
 
 class_property-> class_property '.' id     // a.length
                | class_property '.' func   // a.length()
                | id
                | string
                | list
                | table
                | table_value
*/

/*
bool class_property(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    Token_List *temp_tl=tl;
    while (tl->next!=NULL) {
        tl=tl->next;
    }
    int count=0; // count of '(' and ')'
    int i=length_of_tl-1;
    int index_of_dot=-1;
    while (tl->ahead!=NULL) {
        if (term(tl->current_token.TOKEN_STRING, "(")) {
            count++;
            tl=tl->ahead;
            i--;
            continue;
        }
        if (term(tl->current_token.TOKEN_STRING, ")")) {
            count--;
            tl=tl->ahead;
            i--;
            continue;
        }
        if (count==0 && term(tl->current_token.TOKEN_STRING, ".")) {
            index_of_dot=i;
            break;
        }
        
        i--;
        tl=tl->ahead;
    }
    tl=temp_tl;

    // id
    // string
    if (index_of_dot==-1&&length_of_tl==1&&(term(tl->current_token.TOKEN_CLASS, "id")||term(tl->current_token.TOKEN_CLASS, "string"))) {
        //int index=TREE_INDEX;
        tree->name=tl->current_token.TOKEN_STRING;
        tree->token_class="instance_name";
        return TRUE;
    }
    // list
    // table 
    else if (index_of_dot==-1&&length_of_tl==1&&term(tl->current_token.TOKEN_CLASS, "list_table")) {
        //int index=TREE_INDEX;
        tree->name=tl->current_token.TOKEN_STRING;
        tree->token_class="instance_name";
        int index=TREE_INDEX;
        TREE_addNode(tree, "list", "");
        //return TRUE;
        return list(TREE_getTreeAccordingToIndex(tree, index), tl);
    }
    else if (index_of_dot==-1){
        return FALSE;
    }
    //class_property '.' id     // a.length
    //class_property '.' func   // a.length()
    else{
        printf("enter here\n");
        TL_print(tl);
        
        Token_List *tl1=TL_subtl(tl, 0, index_of_dot);
        Token_List *tl2=TL_subtl(tl, index_of_dot+1, length_of_tl);
        
            
        //class_property '.' id     // a.length
        if (TL_length(tl2)==1 && term(tl2->current_token.TOKEN_CLASS, "id")) {
            int index=TREE_INDEX;
            TREE_addNode(tree, "class_property","");
            TREE_addNode(tree, tl2->current_token.TOKEN_STRING, "id");
            return class_property(TREE_getTreeAccordingToIndex(tree, index), tl1);
        }
        //class_property '.' func   // a.length()
        else{
            int index1=TREE_INDEX;
            TREE_addNode(tree, "class_property","");
            int index2=TREE_INDEX;
            TREE_addNode(tree, "func", "");
            return class_property(TREE_getTreeAccordingToIndex(tree, index1),tl1)
            && func(TREE_getTreeAccordingToIndex(tree, index2), tl2);
        }
    }
}
*/