//
//  walley_assignment_function.h
//  Walley0.1
//
//  Created by shd101wyy on 13-4-6.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_assignment.h"
/*
 def '(' params ')' then
 
 def func_name(params):
 ------------------
 func
 
 func-> id '(' params ')'

 
 ==========================
 the second way:
 x = def (params) then  # func_name :x params : params
     ------------------
     func_assign
 
 statements       # run statements
 end			  # end of defining a function

  
 func_assign -> def '(' param ')' then
 
 return_stm -> 'return' value;
 
 func_value -> func_assign walley_statements 'end'

*/
// func_assign -> def '(' param ')' then
bool func_assign(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    if (length_of_tl>=4 && term(tl->current_token.TOKEN_STRING, "def")&&term(tl->next->current_token.TOKEN_STRING, "(")) {
        int index_of_right=-1;
        Token_List *temp_tl=tl;
        int count=0;
        while (tl->next!=NULL) {
            if (term(tl->current_token.TOKEN_STRING, "(")) {
                count++;
                tl=tl->next;
                index_of_right++;
                continue;
            }
            if (term(tl->current_token.TOKEN_STRING, ")")) {
                count--;
                index_of_right++;

                if (count==0) {
                    break;
                }
                tl=tl->next;
                continue;
            }
            index_of_right++;
            tl=tl->next;
        }
        
        tl=temp_tl;
        if (index_of_right==-1) {
            INCOMPLETE_STATEMENT=TRUE;
            printf("INCOMPLETE_STATEMENT func_assign\n");
            exit(0);
        }
        else{
            printf("ENTER HERE %d\n",index_of_right);
            TREE_addNode(tree, "def", "");
            int index=TREE_INDEX;
            TREE_addNode(tree, "params", "");
            
            Token_List *params_tl;
            // has params
            if (index_of_right!=2) {
                params_tl=TL_subtl(tl, 2, index_of_right);
            }
            // does not have params
            else{
                TL_init(&params_tl);
                Token add_token;
                add_token.TOKEN_CLASS="id";
                add_token.TOKEN_STRING="none";
                TL_addToken(&params_tl, add_token);
            }
            
           
            
            return params(TREE_getTreeAccordingToIndex(tree, index), params_tl);
                         
        }
        
        
        
    }
    
    return FALSE;
    
}


// return_stm -> 'return' value;
bool return_stm(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    if (length_of_tl>=2 && term(tl->current_token.TOKEN_STRING, "return")) {
        TREE_addNode(tree, "return", "");
        int index=TREE_INDEX;
        TREE_addNode(tree, "value", "");
        
        return value(TREE_getTreeAccordingToIndex(tree, index),TL_subtl(tl, 1, length_of_tl));
    }
    return FALSE;
}


// func_value -> func_assign walley_statements 'end'
bool func_value(TREE *tree, Token_List *tl){
   
    
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    TL_print(tl);
    int length_of_tl=TL_length(tl);
    if (term(tl->current_token.TOKEN_STRING, "def")&&term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "end")) {
        //int index1=TREE_INDEX;
        //TREE_addNode(tree, "func_assign", "");
        tree->name="func_value";
        tree->token_class="";
        
        int index_of_then=TL_indexOfTokenThatHasTokenString(tl, "then");
        if (index_of_then==-1) {
            printf("FUNC VALUE  did not find then\n");
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
        
        
       
        return func_assign(tree, TL_subtl(tl, 0, index_of_then+1))
        && walley_statements(tree, TL_subtl(tl, index_of_then+1, length_of_tl-1));

    }
    
    return FALSE;
}

