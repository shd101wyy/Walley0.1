//
//  walley_list.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-19.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_tree.h"
int TL_indexOfFinalBracket(Token_List *tl, int index_of_first_bracket){
    int index=0;
    int count=0;
    
    int i=0;
    while (i<index_of_first_bracket) {
        index++;
        tl=tl->next;
        i++;
    }
    
    //printf("%s\n",tl->current_token.TOKEN_STRING);
    
    while (tl->next!=NULL) {
        //printf("count--> %d %d\n",count,index);
        if (strcmp("[", tl->current_token.TOKEN_STRING)==0) {
            count++;
            tl=tl->next;
            index++;
            continue;
        }
        
        if(strcmp("]", tl->current_token.TOKEN_STRING)==0){
            count--;
            tl=tl->next;
            if(count==0){
                return index;
            }
            index++;
            continue;
        }
        
        index++;
        tl=tl->next;
    }
    
    if (strcmp("]", tl->current_token.TOKEN_STRING)==0) {
        count--;
        if (count==0) {
            return index;
        }
    }
    
    return -1;
}

/*
//------ VALUE ------ 
 value    ->num
 | id
 | string
 | list
 | table
 | expr

 
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
*/

bool elements(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    int index_of_comma=TL_indexOfTokenThatHasTokenString(tl, ",");
    // value
    if (index_of_comma==-1) {
        return value(tree, tl);
    }
    // value ',' elements
    else{
        Token_List *tl1=TL_subtl(tl, 0, index_of_comma);
        Token_List *tl2=TL_subtl(tl, index_of_comma+1,length_of_tl);
        
        int index_of_tl1=TREE_INDEX;
        TREE_addNode(tree,"value","");
        int index_of_tl2=TREE_INDEX;
        TREE_addNode(tree, "elements", "");
        
        return value(TREE_getTreeAccordingToIndex(tree, index_of_tl1), tl1)&&
        elements(TREE_getTreeAccordingToIndex(tree, index_of_tl2), tl2);
        
    }
}


bool value(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    if (length_of_tl==1) {
        //   num
        // | id
        // | string
        if (strcmp("num", tl->current_token.TOKEN_CLASS)==0
            ||strcmp("string", tl->current_token.TOKEN_CLASS)==0
            ||strcmp("id", tl->current_token.TOKEN_CLASS)==0) {
            tree->name=tl->current_token.TOKEN_STRING;
            tree->token_class=tl->current_token.TOKEN_CLASS;
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    else{
        //  table
        // |list
        if (strcmp("[", tl->current_token.TOKEN_CLASS)==0) {
            int index_of_final_bracket=TL_indexOfFinalBracket(tl, 0);
            if (index_of_final_bracket==-1) {
                Walley_Print_Error(TL_toString(tl), "incomplete list or table", 0);
                return FALSE;
            }
            else if (index_of_final_bracket!=length_of_tl-1){
                Walley_Print_Error(TL_toString(tl), "wrong index of ] for list or table", 0);
                return FALSE;

            }
            else{
                Token_List *temp_tl=tl;
                bool is_table=FALSE;
                while (tl->next!=NULL) {
                    if (strcmp(tl->current_token.TOKEN_CLASS, "assignment_operator")==0) {
                        is_table=TRUE;
                        break;
                    }
                    tl=tl->next;
                }
                tl=temp_tl;
                // table
                if (is_table) {
                    tree->name="table";
                    tree->token_class="";
                    printf("It is table\n");
                    exit(0);
                }
                // list
                else{
                    tree->name="list";
                    tree->token_class="";
                    printf("It is list\n");
                    exit(0);
                }
            }
        }
        // expr
        else{
            return expr(tree, tl);
        }
    }
}

