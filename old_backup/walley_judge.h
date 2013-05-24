//
//  walley_judge.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_class.h"

/*
 
 lexer:
 
 
 judge_sign -> '>'
 | '<'
 | '=='
 | '>='
 | '<='
 | '!='
 
 true_flase -> 'true'
 | 'false'
 
 relation ->  'and'
 |'or'
 |'not'
 
 
 parser:

if x==1 and x==2:
   -------------
     relation
   ----
    simple relation
 
 < <= ==
 
 // find 'and' and 'or' from behind not in ( )
 
 relation ->
            |relation 'and' relation
            |relation 'or'  relation
            |not relation
            |simple_relation


 // does not support true false now
 
 simple relation -> value judge_sign value
                 -> '(' relation ')'
                 -> expr       (only num, if 0 then false, else true)
                 
 
 
 
 eg:
 
 ./walley parse  "x==y and (y==z or x==z)"
 
 ( relation( and( simple_relation( ==(id x)(id y)))( relation( or( simple_relation( ==(id y)(id z)))( simple_relation( ==(id x)(id z)))))))
 
 
        relation
           |
          and
        /    \
   simple_r  simple_r
        |       |
        ==     relation
       / \        |
       x  y       or
                /     \
            simple_r  simple_r
                |      |
                ==    ==
               /  \   / \
               y  z  x  z
*/
bool relation(TREE *tree, Token_List *tl){
    

    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    
    Token_List *temp_tl=tl;
    while (tl->next!=NULL) {
        tl=tl->next;
    }
    int i=length_of_tl-1;
    int count=0;
    int index_of_and_or=-1;
    for (; i>=0; i--) {
        if (term(tl->current_token.TOKEN_STRING, "(")) {
            count++;
            tl=tl->ahead;
            continue;
        }
        if (term(tl->current_token.TOKEN_STRING, ")")) {
            count--;
            tl=tl->ahead;
            continue;
        }
        // |relation 'and' relation
        // |relation 'or'  relation
        if (count==0 && term(tl->current_token.TOKEN_CLASS, "relation") && strcmp(tl->current_token.TOKEN_STRING, "not")!=0) {
            index_of_and_or=i;
            
            char *and_or_string=tl->current_token.TOKEN_STRING;
            
            tl=temp_tl;
            
            Token_List *tl1=TL_subtl(tl, 0, index_of_and_or);
            Token_List *tl2=TL_subtl(tl, index_of_and_or+1, length_of_tl);
            
            int index=TREE_INDEX;
            TREE_addNode(tree, and_or_string,"");
            int index1=TREE_INDEX;
            TREE_addNodeAtIndex(tree,index, "relation", "");
            int index2=TREE_INDEX;
            TREE_addNodeAtIndex(tree, index, "relation", "");
            
            return relation(TREE_getTreeAccordingToIndex(tree, index1), tl1)
            && relation(TREE_getTreeAccordingToIndex(tree, index2), tl2);
            
        }
        tl=tl->ahead;
    }
    tl=temp_tl;
    
    // |not relation
    if (term(tl->current_token.TOKEN_STRING, "not")) {
        
        TREE_addNode(tree, "not", "");
        int index=TREE_INDEX;
        TREE_addNodeAtIndex(tree, index-1, "relation", "");
        return relation(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(tl, 1, length_of_tl));
    }
    
    return simple_relation(tree, tl);
}


bool simple_relation(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    
    //'(' relation ')'
    if (term("(", TL_tokenAtIndex(tl, 0).TOKEN_STRING) && term(")",TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING)) {
        //int index=TREE_INDEX;
        //TREE_addNode(tree, "relation", "");
        //return relation(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(tl, 1, length_of_tl-1));
        return relation(tree, TL_subtl(tl, 1, length_of_tl-1));
    }
    // value judge_sign value
    // expr
    else{
        
        tree->name="simple_relation";
        
        int index_of_judge_sign=TL_indexOfTokenThatHasTokenClass(tl, "judge_sign");
        
        // expr
        if (index_of_judge_sign==-1) {
            //int index=TREE_INDEX;
            //TREE_addNode(tree, "value", "");
            return expr(tree, tl);
        }
        
        
        // value judge_sign value
        Token_List *tl1=TL_subtl(tl, 0, index_of_judge_sign);
        Token_List *tl2=TL_subtl(tl, index_of_judge_sign+1, length_of_tl);
        
        char *judge_sign=TL_tokenAtIndex(tl, index_of_judge_sign).TOKEN_STRING;

        // swap tl1 and tl2
        // and change judge sign
        // for virtual machine
        if (term(">=", judge_sign) || term(">", judge_sign)) {
            Token_List *temp_tl=tl1;
            tl1=tl2;
            tl2=temp_tl;
            if (term(">=", judge_sign)) {
                judge_sign="<=";
            }
            else{
                judge_sign="<";
            }
        }
        
        int index=TREE_INDEX;
        TREE_addNode(tree, judge_sign, "");
        
        TREE *temp_tree=TREE_getTreeAccordingToIndex(tree, index);
        
        int index1=TREE_INDEX;
        TREE_addNode(temp_tree, "value", "");
        int index2=TREE_INDEX;
        TREE_addNode(temp_tree, "value", "");
        return value(TREE_getTreeAccordingToIndex(tree, index1), tl1)
        && value(TREE_getTreeAccordingToIndex(tree, index2), tl2);
        
        
    }
    
    return FALSE;
}






















