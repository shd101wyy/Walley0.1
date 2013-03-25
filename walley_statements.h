//
//  walley_statements.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_judge.h"

/*

 if x>=0 :
 
 if_stms  -> 'if' relation ':'
 elif_stms-> 'elif' relation ':'
 else_stms-> 'else' ':'
 
 ===========
 
 while x<=0 :
 
 while_stms -> 'while' relation ':'
 

 ===========
 
 for i=0;i<10;i++:
 for ;i<10;i++:
 for i<10;i++
 
 // not support 'for i in range(10):' kind of for statements now
 
 for_stms ->
 |  'for' simple_relation ';' assignment ':'
 |  'for' ';' simple_relation ';' assignment ':'
 |  'for' assignment ';' simple_relation ';' assignment ':'
 
 
 ===========
 
 def add(num1,num2):
 
 func_stms -> 'def' func ':'
 

 ===========
 does not support:
    class
    switch
    i++
    i--
    +=
    -=
    exp:
now
============
 
 statements ->
 |  if_stms
 |  elif_stms
 |  else_stms
 |  while_stms
 |  for_stms
 |  func_stms
 |  assignment
 |  expr

*/


//============================================================================================
//  if_stms  -> 'if' relation ':'
bool if_stms(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    
    //'if' relation ':'
    if (term(tl->current_token.TOKEN_STRING, "if") &&term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, ":") && length_of_tl>2) {
        
        Token_List *relation_tl=TL_subtl(tl, 1, length_of_tl-1);
        
        TREE_addNode(tree, "if", "");
        int index=TREE_INDEX;
        TREE_addNode(tree, "relation", "");
        return relation(TREE_getTreeAccordingToIndex(tree, index), relation_tl);
    }
    
    return FALSE;
}

// elif_stms-> 'elif' relation ':'
bool elif_stms(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    //'if' relation ':'
    if (term(tl->current_token.TOKEN_STRING, "elif") &&term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, ":") && length_of_tl>2) {
        
        Token_List *relation_tl=TL_subtl(tl, 1, length_of_tl-1);
        
        TREE_addNode(tree, "elif", "");
        int index=TREE_INDEX;
        TREE_addNode(tree, "relation", "");
        return relation(TREE_getTreeAccordingToIndex(tree, index), relation_tl);
    }
    return FALSE;
}

// else_stms-> 'else' ':'
bool else_stms(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    
    // 'else' ':'
    if (length_of_tl==2 && term(tl->current_token.TOKEN_STRING, "else") && term(tl->next->current_token.TOKEN_STRING, ":")) {
        TREE_addNode(tree, "else", "");
        return TRUE;
    }
    
    return FALSE;
}

//==================================================
// while_stms -> 'while' relation ':'
bool while_stms(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    //'while' relation ':'
    if (term(tl->current_token.TOKEN_STRING, "while") && term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, ":") &&length_of_tl>2) {
        Token_List *relation_tl=TL_subtl(tl, 1, length_of_tl-1);
        
        TREE_addNode(tree, "while", "");
        int index=TREE_INDEX;
        TREE_addNode(tree, "relation", "");
        return relation(TREE_getTreeAccordingToIndex(tree, index), relation_tl);
    }
    return FALSE;
}

//=================================================

/*
 ; is not in ()
 for_stms ->
 |  'for' simple_relation ';' assignment ':'
 |  'for' ';' simple_relation ';' assignment ':'
 |  'for' assignment ';' simple_relation ';' assignment ':'
 
 
 */

bool for_stms(TREE *tree, Token_List *tl){
    
    int length_of_tl=TL_length(tl);
    
    int num_of_semi_colon=0;
    int count_of_p=0; // count of ()
    Token_List *temp_tl=tl;
    
    int index_of_semi_colon[3];
    index_of_semi_colon[0]=-1;
    index_of_semi_colon[1]=-1;
    index_of_semi_colon[2]=-1;
    
    int index=0;
    int i=0;
    
    while (tl->next!=NULL) {
        if (term(tl->current_token.TOKEN_STRING, "(")) {
            count_of_p++;
            tl=tl->next;
            i++;
            continue;
        }
        if (term(tl->current_token.TOKEN_STRING, ")")) {
            count_of_p--;
            tl=tl->next;
            i++;
            continue;
        }
        
        if (count_of_p==0 && term(tl->current_token.TOKEN_STRING, ";")) {
            
            
            //mistake... to many ;
            if (index<2) {
                index_of_semi_colon[index]=i;
                index++;
            }
            num_of_semi_colon++;
            
        }
        i++;
        tl=tl->next;
    }
    tl=temp_tl;
    if (term(tl->current_token.TOKEN_STRING, "for")
        &&term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, ":")
        &&length_of_tl!=2
        &&num_of_semi_colon!=0
        &&num_of_semi_colon<=2
        ) {
        // |  'for' simple_relation ';' assignment ':'
        if (num_of_semi_colon==1) {
            Token_List *simple_relation_tl=TL_subtl(tl, 1, index_of_semi_colon[0]);
            Token_List *assignment_tl=TL_subtl(tl, index_of_semi_colon[0]+1, length_of_tl-1);
            
            TREE_addNode(tree, "for", "");
            int index_of_sr=TREE_INDEX;
            TREE_addNode(tree, "simple_relation", "");
            int index_of_a=TREE_INDEX;
            TREE_addNode(tree, "assignment", "");
            
            return simple_relation(TREE_getTreeAccordingToIndex(tree, index_of_sr), simple_relation_tl)
            && assignment(TREE_getTreeAccordingToIndex(tree, index_of_a), assignment_tl);
        }
        //|  'for' ';' simple_relation ';' assignment ':'
        //|  'for' assignment ';' simple_relation ';' assignment ':'
        else{
            //|  'for' ';' simple_relation ';' assignment ':'
            if (term(tl->next->current_token.TOKEN_STRING, ";")) {
                Token_List *simple_relation_tl=TL_subtl(tl, 2, index_of_semi_colon[1]);
                Token_List *assignment_tl=TL_subtl(tl, index_of_semi_colon[1]+1, length_of_tl-1);
                
                TREE_addNode(tree, "for", "");
                int index_of_sr=TREE_INDEX;
                TREE_addNode(tree, "simple_relation", "");
                int index_of_a=TREE_INDEX;
                TREE_addNode(tree, "assignment", "");
                
                return simple_relation(TREE_getTreeAccordingToIndex(tree, index_of_sr), simple_relation_tl)
                && assignment(TREE_getTreeAccordingToIndex(tree, index_of_a), assignment_tl);
            }
            //|  'for' assignment ';' simple_relation ';' assignment ':'
            
            else{
                Token_List *assignment_tl1=TL_subtl(tl, 1, index_of_semi_colon[0]);
                Token_List *simple_relation_tl=TL_subtl(tl, index_of_semi_colon[0]+1, index_of_semi_colon[1]);
                Token_List *assignment_tl2=TL_subtl(tl, index_of_semi_colon[1]+1, length_of_tl-1);
                
                TREE_addNode(tree, "for","");
                int index_of_a_tl1=TREE_INDEX;
                TREE_addNode(tree, "assignment", "");
                int index_of_sr=TREE_INDEX;
                TREE_addNode(tree, "simple_relation","");
                int index_of_a_tl2=TREE_INDEX;
                TREE_addNode(tree, "assignment","");
                
                return assignment(TREE_getTreeAccordingToIndex(tree, index_of_a_tl1), assignment_tl1)
                    && simple_relation(TREE_getTreeAccordingToIndex(tree, index_of_sr),simple_relation_tl)
                && assignment(TREE_getTreeAccordingToIndex(tree, index_of_a_tl2),assignment_tl2);
            }
        }
    }
    return FALSE;
}


//========================
// func_stms -> 'def' func ':'
bool func_stms(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    //'def' func ':'
    if (length_of_tl>2 && term(tl->current_token.TOKEN_STRING, "def")&&term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, ":")) {
        TREE_addNode(tree, "def", "");
        
        Token_List *func_tl=TL_subtl(tl, 1, length_of_tl-1);
        
        int index=TREE_INDEX;
        TREE_addNode(tree, "func","");
        return func(TREE_getTreeAccordingToIndex(tree, index), func_tl);
    }
    return FALSE;

}

//========================
/*
 
 statements -> 
 |  if_stms
 |  elif_stms
 |  else_stms
 |  while_stms
 |  for_stms
 |  func_stms
 |  assignment
 |  expr
 
 
 */

bool statements(TREE *tree, Token_List *tl){
    
    return if_stms(tree, tl)
        ||elif_stms(tree, tl)
        ||else_stms(tree, tl)
        ||while_stms(tree, tl)
        ||for_stms(tree, tl)
        ||func_stms(tree, tl)
        ||assignment(tree, tl)
        ||expr(tree, tl);
    
}







