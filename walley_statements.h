//
//  walley_statements.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_judge.h"

/*

 if x>=0 then
 
 if_stms  -> 'if' relation 'then'
 elif_stms-> 'elif' relation 'then'
 else_stms-> 'else'
 
 ===========
 
 while x<=0 then
 
 while_stms -> 'while' relation 'then'
 

 ===========
 
 for i=0,i<10,i++ then
 for i<10,i++ then
 
 // not support 'for i in range(10):' kind of for statements now
 
 for_stms ->
 |  'for' simple_relation ',' assignment 'then'
 |  'for' ',' simple_relation ',' assignment 'then'
 |  'for' assignment ',' simple_relation ',' assignment 'then'
 
 
 ===========
 
 def add(num1,num2) then
 
 func_stms -> 'def' func 'then'
 

 ===========
 end_stm -> 'end'
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
 |  return_stm
 |  if_stms
 |  elif_stms
 |  else_stms
 |  while_stms
 |  for_stms
 |  func_stms
 |  end_stm
 |  assignment
 |  expr
 
============
 walley_statements ->
                    | statements, statements        // use sentences_seperation
*/


//============================================================================================
//  if_stms  -> 'if' relation 'then'

bool if_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    
    //'if' relation ''
    if (term(tl->current_token.TOKEN_STRING, "if")) {
        if (term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "then") && length_of_tl>2) {
            Token_List *relation_tl=TL_subtl(tl, 1, length_of_tl-1);

            TREE_addNode(tree, "if", "");
            int index=TREE_INDEX;
            TREE_addNode(tree, "relation", "");
            return relation(TREE_getTreeAccordingToIndex(tree, index), relation_tl);
        }
        // incomplete
        else{
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
        
    }
    
    return FALSE;
}

// elif_stms-> 'elif' relation 'then'
bool elif_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    //'elif' relation 'then'
    if (term(tl->current_token.TOKEN_STRING, "elif")) {
        if (term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "then") && length_of_tl>2) {
            Token_List *relation_tl=TL_subtl(tl, 1, length_of_tl-1);
            
            TREE_addNode(tree, "elif", "");
            int index=TREE_INDEX;
            TREE_addNode(tree, "relation", "");
            return relation(TREE_getTreeAccordingToIndex(tree, index), relation_tl);

        }
        // incomplete
        else{
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
    }
    return FALSE;
}

// else_stms-> 'else'
bool else_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    
    // 'else'
    if (length_of_tl==1 && term(tl->current_token.TOKEN_STRING, "else")) {
        TREE_addNode(tree, "else", "");
        return TRUE;
    }
    
    return FALSE;
}

//==================================================
// while_stms -> 'while' relation 'then'
bool while_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    //'while' relation 'then'
    if (term(tl->current_token.TOKEN_STRING, "while")) {
        if (term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "then") &&length_of_tl>2) {
            Token_List *relation_tl=TL_subtl(tl, 1, length_of_tl-1);
            
            TREE_addNode(tree, "while", "");
            int index=TREE_INDEX;
            TREE_addNode(tree, "relation", "");
            return relation(TREE_getTreeAccordingToIndex(tree, index), relation_tl);

        }
        // incomplete
        else{
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
    }
    return FALSE;
}

//=================================================

/*
 , is not in ()
 for_stms ->
 |  'for' simple_relation ',' assignment 'then'
 |  'for' ',' simple_relation ',' assignment 'then'
 |  'for' assignment ',' simple_relation ',' assignment 'then'
 
 
 */

// i didn't change semi_colon to comma
// cuz i used to use semi_colon
bool for_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    
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
        
        if (count_of_p==0 && term(tl->current_token.TOKEN_STRING, ",")) {
            
            
            //mistake... to many ,
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
    
    // incomplete
    if (term(tl->current_token.TOKEN_STRING, "for")&&term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "then")==FALSE) {
        INCOMPLETE_STATEMENT=TRUE;
        return FALSE;
    }
    
    if (term(tl->current_token.TOKEN_STRING, "for")
        &&term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "then")
        &&length_of_tl!=2
        &&num_of_semi_colon!=0
        &&num_of_semi_colon<=2
        ) {
        // |  'for' simple_relation ',' assignment 'then'
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
        //|  'for' ',' simple_relation ',' assignment 'then'
        //|  'for' assignment ',' simple_relation ',' assignment 'then'
        else{
            //|  'for' ',' simple_relation ',' assignment 'then'
            if (term(tl->next->current_token.TOKEN_STRING, ",")) {
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
            //|  'for' assignment ',' simple_relation ',' assignment 'then'            
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
// func_stms -> 'def' func 'then'
bool func_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    //'def' func 'then'
    if (term(tl->current_token.TOKEN_STRING, "def")) {
        if (length_of_tl>2 && term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "then")) {
            TREE_addNode(tree, "def", "");
            
            Token_List *func_tl=TL_subtl(tl, 1, length_of_tl-1);
            
            int index=TREE_INDEX;
            TREE_addNode(tree, "func","");
            return func(TREE_getTreeAccordingToIndex(tree, index), func_tl);
        }
        // incomplete 
        else{
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
       
    }
    return FALSE;

}
bool end_stm(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    if (TL_length(tl)==1 && term(tl->current_token.TOKEN_CLASS, "end")) {
        TREE_addNode(tree, "end","");
        return TRUE;
    }
    return FALSE;
}
//========================
/*
 
 statements -> 
 |  return_stm
 |  if_stms
 |  elif_stms
 |  else_stms
 |  while_stms
 |  for_stms
 |  func_stms
 |  end_stm
 |  assignment
 |  expr
 
 
 
 */

bool statements(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    
    return return_stm(tree, tl)
        ||if_stms(tree, tl)
        ||elif_stms(tree, tl)
        ||else_stms(tree, tl)
        ||while_stms(tree, tl)
        ||for_stms(tree, tl)
        ||func_stms(tree, tl)
        ||end_stm(tree, tl)
        ||assignment(tree, tl)
        ||expr(tree, tl);
    
}

//walley_statements ->
//| statements, statements        // use sentences_seperation
bool walley_statements(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    Token_List *temp_tl;
    TL_init(&temp_tl);
    int begin=0;
    
    while (sentences_seperation(tl, &temp_tl, &begin)) {
        if (INCOMPLETE_STATEMENT) {
            return FALSE;
        }
        printf("@============\n");
        TL_print(temp_tl);
        printf("@@============\n");
        int index=TREE_INDEX;
        TREE_addNode(tree, "statements", "");
        if (!statements(TREE_getTreeAccordingToIndex(tree, index), temp_tl)) {
            printf("Walley Statements Parse Error\n");
            return FALSE;
        }
    }
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    return TRUE;
}





