//
//  walley_function.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_assignment_function.h"
/*
 
 x = def '(' params ')' then
 
 def func_name(params):
     ------------------
     func
 
 func-> id '(' params ')'
 */


/*
 
 version 1.0
 params-> value ',' params
       -> value
 
 version 2.0
 params-> assignment ',' params
        | value ',' params
        | assignment
        | value
 
 */

bool params(TREE *tree, Token_List *tl){
      
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    // has no params
    if (tl==NULL) {
        return TRUE;
    }
    int length_of_tl=TL_length(tl);
    //int index_of_comma=TL_indexOfTokenThatHasTokenString(tl, ",");
    
    Token_List *temp_tl=tl;
    int count=0;
    int index_of_comma=-1;
    int i=0;
    while (tl->next!=NULL) {
        if (term(tl->current_token.TOKEN_STRING, "(")) {
            count++;
            tl=tl->next;
            i++;
            continue;
        }
        if (term(tl->current_token.TOKEN_STRING, ")")) {
            count--;
            tl=tl->next;
            i++;
            continue;
        }
        if(count==0 && term(tl->current_token.TOKEN_STRING, ",")){
            index_of_comma=i;
            break;
        }
        
        i++;
        tl=tl->next;
    }
    tl=temp_tl;
        
    // -> assignment
    // -> value
    if (index_of_comma==-1) {
        
        if (assignment(tree, tl)) {
            return TRUE;
        }
        else{
                    
            int index=TREE_INDEX;
            TREE_addNode(tree, "value", "");
            
            return value(TREE_getTreeAccordingToIndex(tree, index), tl);
        }
      
    }
    // -> assignment ',' params
    // -> value ',' params
    else{
        
        Token_List *tl1=TL_subtl(tl, 0, index_of_comma);
        Token_List *tl2=TL_subtl(tl, index_of_comma+1, length_of_tl);
        
    
        if (assignment(tree, tl1)) {
            return params(tree, tl2);
        }
        else{
                        
            
            int index_of_tl1=TREE_INDEX;
            TREE_addNode(tree, "value","");
            return value(TREE_getTreeAccordingToIndex(tree, index_of_tl1), tl1)
            && params(tree,tl2);
        }
    }
}

bool func(TREE *tree, Token_List *tl){
       
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    // id '(' params ')'
    int index_of_left=TL_indexOfTokenThatHasTokenString(tl, "(");
    int index_of_right=-1; // get right )
    
    Token_List *temp_tl=tl;
    int i=0;
    int count=0;
    while (temp_tl!=NULL) {
        if (term(temp_tl->current_token.TOKEN_STRING, "(")) {
            count++;
        }
        else if (term(temp_tl->current_token.TOKEN_STRING, ")")){
            count--;
            if (count==0) {
                index_of_right=i;
                break;
            }
        }
        i=i+1;
        temp_tl=temp_tl->next;
    }
    
    if (index_of_right==-1) {
        INCOMPLETE_STATEMENT=TRUE;
        return FALSE;
    }
    
    // false
    if (index_of_right+1!=length_of_tl||index_of_left==-1||index_of_left==0) {
        return FALSE;
    }
    else{        
        
        Token_List *test_id=TL_subtl(tl, 0, index_of_left);
        Token_List *params_tl;
        // no params
        if (index_of_left+1==index_of_right) {
            
            params_tl=NULL;
        }
        // has params
        else{
            params_tl=TL_subtl(tl, index_of_left+1, index_of_right);
        }
        

        
        int length_of_test_id=TL_length(test_id);
        if (length_of_test_id!=1||strcmp(test_id->current_token.TOKEN_CLASS, "id")!=0) {
            return FALSE;
        }

        
        tree->name="func";
        tree->token_class="";
        TREE_addNode(tree, "", "call");
        TREE_addNode(TREE_getTreeAccordingToIndex(tree, TREE_INDEX-1),toString(test_id->current_token.TOKEN_STRING), "string");
        int index=TREE_INDEX;
        TREE_addNode(tree, "params", "");
        
      
    
        
        return params(TREE_getTreeAccordingToIndex(tree, index), params_tl);
        
    }
}
