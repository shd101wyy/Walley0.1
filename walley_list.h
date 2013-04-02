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
 | func
 | class_property
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
// x={1,[4]=2,3}
// x[0]->1
// x[1]->3
// x[4]->2
 
 table_expr ->| '@' id '=' value        # instance method
              | id '=' value
              |'[' (string|num) ']' '=' (value)      where (string|num) is value...there maybe some problem
              | value                       

 */





//===============NEW CODE FOR TABLE on April 1=======
bool table_elements(TREE *tree, Token_List *tl,int *key_index){
    int length_of_tl=TL_length(tl);
    Token_List *temp_tl=tl;
    int i=0;
    int index_of_comma=-1;
    for (; i<length_of_tl; i++) {
        if (term(tl->current_token.TOKEN_STRING, ",")) {
            index_of_comma=i;
            break;
        }
        tl=tl->next;
    }
    tl=temp_tl;
    
    //| table_expr ',' table_elements
    if (index_of_comma!=-1) {
        Token_List *table_expr_tl=TL_subtl(tl, 0, index_of_comma);
        Token_List *table_elements_tl=TL_subtl(tl, index_of_comma+1, length_of_tl);
        
        int index1=TREE_INDEX;
        TREE_addNode(tree, "table_expr", "");
        //int index2=TREE_INDEX;
        return table_expr(TREE_getTreeAccordingToIndex(tree, index1), table_expr_tl, key_index)
        && table_elements(tree, table_elements_tl, key_index);
    }
    else{
        int index=TREE_INDEX;
        TREE_addNode(tree, "table_expr", "");
        return table_expr(TREE_getTreeAccordingToIndex(tree, index), tl, key_index);
    }
}
bool table_expr(TREE *tree, Token_List *tl,int *key_index){
    int length_of_tl=TL_length(tl);
    // | '@' id '=' value
    if (length_of_tl>3&&term(tl->current_token.TOKEN_CLASS, "@") && term(tl->next->current_token.TOKEN_CLASS, "id") && term(tl->next->next->current_token.TOKEN_STRING, "=")) {
        char *append_key=tl->next->current_token.TOKEN_STRING;
        int length_of_append_key=(int)strlen(append_key);
        char *new_key=(char*)malloc(sizeof(char)*(length_of_append_key+1+1));
        new_key[0]='@';
        int i=1;
        for (; i<length_of_append_key+1; i++) {
            new_key[i]=append_key[i-1];
        }
        new_key[i]=0;
        
        TREE_addNode(tree, new_key, "key");
        int index=TREE_INDEX;
        TREE_addNode(tree, "value", "");
        return value(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(tl, 3, length_of_tl));
    }

    // id '=' value
    else if (term(tl->current_token.TOKEN_CLASS, "id") && term(tl->next->current_token.TOKEN_STRING, "=")) {
        TREE_addNode(tree, tl->current_token.TOKEN_STRING, "key");
        int index=TREE_INDEX;
        TREE_addNode(tree, "value", "");
        return value(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(tl, 2, length_of_tl));
    }
    
    //    |'[' (string|int) ']' '=' (value)
    else if (term(tl->current_token.TOKEN_CLASS, "list_table")){
            // THIS PLACE HAS SOME PROBLEM
        printf("'[' (string|int) ']' '=' (value)  HAS NOT BEEN IMPLEMENTED\n");
        exit(0);
    }
    //value
    else{
        TREE_addNode(tree, intToCString((*key_index)), "key");
        int index=TREE_INDEX;
        TREE_addNode(tree, "value", "");
        int index2=TREE_INDEX;
        TREE_addNode(TREE_getTreeAccordingToIndex(tree, index), "value", "");
        
        (*key_index)=(*key_index)+1;
        
        return value(TREE_getTreeAccordingToIndex(tree, index2),tl);
    }
    return FALSE;
}

//table    -> '[' table_elements ']'
bool table(TREE *tree, Token_List *tl,int *key_index){
    int length_of_tl=TL_length(tl);
    
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
            
            Token_List *table_tl=Walley_Lexical_Analyzie(list_string2);
            return table_elements(tree, table_tl, key_index);
                        
        }
        else
            return FALSE;
    }
    else
        return FALSE;
}

//====================================================


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
    
    // func
    // class_property
    // expr
    else{
        return func(tree, tl)|| class_property(tree, tl) ||expr(tree, tl);
    }
}

