//
//  walley_table.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-20.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_list.h"
/*
 [["a"]=12,["b"]=[["c"]=14]]
 
 table -> '[' pairs ']'
 
 pairs -> |  pairs,pairs
          | '[' string ']' = value
            ==============
              list


*/
// if it is NOT LIST, then it is TABLE
//bool table(TREE *tree, Token_List *tl){
//
//}
/*
bool pairs(TREE *tree, Token_List *tl){
    int index_of_comma=TL_indexOfTokenThatHasTokenString(tl, ",");
    int length_of_tl=TL_length(tl);
    //pairs,pairs
    if (index_of_comma!=-1) {
        Token_List *tl1=TL_subtl(tl, 0, index_of_comma);
        Token_List *tl2=TL_subtl(tl, index_of_comma+1,length_of_tl);
        
        int index_of_tl1=TREE_INDEX;
        TREE_addNode(tree, "pairs", "");
        int index_of_tl2=TREE_INDEX;
        TREE_addNode(tree, "pairs", "");
        
        return pairs(TREE_getTreeAccordingToIndex(tree, index_of_tl1), tl1)
              && pairs(TREE_getTreeAccordingToIndex(tree, index_of_tl2), tl2);
    }
    //'[' string ']' = value
    else{
        if (strcmp("list_table", tl->current_token.TOKEN_CLASS)==0) {
            // list_string ["a"]
            // list_string2 "a"
            char *list_string=tl->current_token.TOKEN_STRING;
            int length_of_list_string=(int)strlen(list_string);
            char *list_string2=(char*)malloc(sizeof(char)*(length_of_list_string-2+1));
            int i=0;
            for (; i<length_of_list_string-2; i++) {
                list_string2[i]=list_string[i+1];
            }
            list_string2[i]=0;
            
            Token_List *list_tl=Walley_Lexical_Analyzie(list_string2);
            int length_of_list_tl=TL_length(list_tl);
            
            // correct
            if (length_of_list_tl==1 && strcmp("string", list_tl->current_token.TOKEN_CLASS)==0 && strcmp("=", tl->next->current_token.TOKEN_STRING)==0) {
                TREE_addNode(tree, list_string2, "table_dict");
                int index=TREE_INDEX;
                TREE_addNode(tree, "value", "table_value");
                return value(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(tl, 2, length_of_tl));
            }
            else{
                return FALSE;
            }
            

        }
        else{
            return FALSE;
        }
    }
}
*/



/*
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
    else if (term(tl->current_token.TOKEN_CLASS, "list_table") && TL_indexOfTokenThatHasTokenString(tl, "=")!=-1){
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