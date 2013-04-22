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
 value    ->
 |(null)   kong de
 |num
 | id
 | string
 | list
 | table
 | func_value
 | func
 | class_property
 | expr

 
//------ LIST -------

list     -> '[' elements ']'
elements -> value ',' elements
-> value

 
*/


bool list(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    // check = existed
    bool existed_equal=FALSE;
    
    if (length_of_tl==1) {
        char *list_string=tl->current_token.TOKEN_STRING;
        int length_of_list_string=(int)strlen(list_string);
        if (list_string[0]=='[' && list_string[length_of_list_string-1]==']') {
            // list_string [1,2]
            // list_string2 1,2
            char *list_string2=(char*)malloc(sizeof(char)*(length_of_list_string-2+1));
            int i=0;
            for (; i<length_of_list_string-2; i++) {
                list_string2[i]=list_string[i+1];
            }
            list_string2[i]=0;
            
            // check whether it is table
            Token_List *list_tl=Walley_Lexical_Analyzie(list_string2);
            Token_List *temp_tl=list_tl;
            while (list_tl->next!=NULL) {
                if (strcmp(list_tl->current_token.TOKEN_STRING, "=")==0) {
                    existed_equal=TRUE;
                    break;
                }
                list_tl=list_tl->next;
            }
            list_tl=temp_tl;
            
            
            if (existed_equal) {
                tree->name=list_string;
                tree->token_class="table";
                printf("IT IS TABLE BUT NOT LIST\n");
                //return pairs(tree, list_tl);
                exit(0);
            }
            
            
            else{
                tree->name=list_string;
                tree->token_class="list";
                return elements(tree, list_tl);
            }
            
        }
        else
            return FALSE;
    }
    else
        return FALSE;
}


bool elements(TREE *tree, Token_List *tl){
    int length_of_tl=TL_length(tl);
    int index_of_comma=TL_indexOfTokenThatHasTokenString(tl, ",");
    // value
    if (index_of_comma==-1) {
        int index_of_tl=TREE_INDEX;
        TREE_addNode(tree,"value","");
        
        return value(TREE_getTreeAccordingToIndex(tree, index_of_tl), tl);
    }
    // value ',' elements
    else{
        Token_List *tl1=TL_subtl(tl, 0, index_of_comma);
        Token_List *tl2=TL_subtl(tl, index_of_comma+1,length_of_tl);
        
        int index_of_tl1=TREE_INDEX;
        TREE_addNode(tree,"value","");
       
        
        return value(TREE_getTreeAccordingToIndex(tree, index_of_tl1), tl1)&&
        //elements(TREE_getTreeAccordingToIndex(tree, index_of_tl2), tl2);
        elements(tree, tl2);
    }
}


bool value(TREE *tree, Token_List *tl){
    
    int length_of_tl=TL_length(tl);

    // (null)
    if(length_of_tl==0){
        tree->name="none";
        tree->token_class="id";
    }
    else if (length_of_tl==1) {
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
        // | list
        // | table
        else if (strcmp("list_table", tl->current_token.TOKEN_CLASS)==0){
            tree->name=tl->current_token.TOKEN_STRING;
            //tree->token_class=tl->current_token.TOKEN_CLASS;
            tree->token_class="table";
            //printf("LIST_TABLE\n");
            int key_index=0;
            return table(tree, tl,&key_index);
        }
        else{
            return FALSE;
        }
    }
    // func_value
    // func
    // class_property
    // expr
    else{
        return func_value(tree, tl)||func(tree, tl)|| class_property(tree, tl) ||expr(tree, tl);
    }
}

