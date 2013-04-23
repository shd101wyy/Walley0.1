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
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
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
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
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
        
        // THIS PLACE HAS PROBLEM WHILE PARSING KEY
        
        TREE_addNode(tree, new_key, "key");
        int index=TREE_INDEX;
        TREE_addNode(tree, "value", "");
        return value(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(tl, 3, length_of_tl));
    }
    
    // id '=' value
    else if (term(tl->current_token.TOKEN_CLASS, "id") && term(tl->next->current_token.TOKEN_STRING, "=")) {
        int index1=TREE_INDEX;
        TREE_addNode(tree, "key", "");
        
        
        
        Token_List *key_tl=Walley_Lexical_Analyzie(toString(tl->current_token.TOKEN_STRING));
        TREE key_tree;
        TREE_initWithName(&key_tree, "key");
        value(&key_tree, key_tl);
        
        TREE_addTree(TREE_getTreeAccordingToIndex(tree, index1),key_tree);

        
        
        int index2=TREE_INDEX;
        TREE_addNode(tree, "value", "");
        return value(TREE_getTreeAccordingToIndex(tree, index2), TL_subtl(tl, 2, length_of_tl));
    }
    //              0           1       2
    //    |'[' (string|int) ']' '=' (value)
    else if (term(tl->current_token.TOKEN_CLASS, "list_table") && term(tl->next->current_token.TOKEN_STRING, "=")){
        // THIS PLACE HAS SOME PROBLEM
        printf("'[' (string|int) ']' '=' (value)  HAS NOT BEEN IMPLEMENTED\n");
        
        int length=(int)strlen(tl->current_token.TOKEN_STRING);
        char *string_inside=(char*)malloc(sizeof(char)*(length-2+1));
        int i=0;
        for (; i<length-2; i++) {
            string_inside[i]=tl->current_token.TOKEN_STRING[i+1];
        }
        string_inside[i]=0;
      
        
        int index1=TREE_INDEX;
        TREE_addNode(tree, "key", "");
        
        
        Token_List *key_tl=Walley_Lexical_Analyzie(string_inside);
        TREE key_tree;
        TREE_initWithName(&key_tree, "key");
        value(&key_tree, key_tl);
        
        TREE_addTree(TREE_getTreeAccordingToIndex(tree, index1),key_tree);
        
        int index2=TREE_INDEX;
        TREE_addNode(tree, "value", "");
        
        
        return value(TREE_getTreeAccordingToIndex(tree, index2),TL_subtl(tl, 2, length_of_tl));

    }
    //value
    else{
        int index1=TREE_INDEX;
        TREE_addNode(tree, "key", "");
        
        Token_List *key_tl=Walley_Lexical_Analyzie(intToCString((*key_index)));
        TREE key_tree;
        TREE_initWithName(&key_tree, "key");
        value(&key_tree, key_tl);
        
        TREE_addTree(TREE_getTreeAccordingToIndex(tree, index1),key_tree);
        
        
        int index=TREE_INDEX;
        TREE_addNode(tree, "value", "");
        //int index2=TREE_INDEX;
        //TREE_addNode(TREE_getTreeAccordingToIndex(tree, index), "value", "");
        
        (*key_index)=(*key_index)+1;
        
        //return value(TREE_getTreeAccordingToIndex(tree, index2),tl);
        return value(TREE_getTreeAccordingToIndex(tree, index),tl);

    }
    return FALSE;
}

//table    -> '[' table_elements ']'
bool table(TREE *tree, Token_List *tl,int *key_index){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
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
/*

 table_value_key->
 | [(string|num)value]
 | '.' id
 | '.' func
 | '.' func table_value_key                            // behind is [] or '.'
 | [(string|num)value] table_value_key                 // behind is [] or '.'
 | '.' id table_value_key                              // behind is [] or '.'
 
table_value ->
            id table_value_key
 
        // new support 
            string table_value_key              // "hello".length()
            list_table table_value_key          // [1,2,3].length()
            num table_value_key                 //  13.toString()
            expr table_value_key                //  ("He"+"llo").length() where expr can only be  inside '()' 

*/

/*
 table_value ->
        id table_value_key
 
        // new support
        string table_value_key              // "hello".length()
        list_table table_value_key          // [1,2,3].length()
        num table_value_key                 //  13.toString()
        expr table_value_key                //  ("He"+"llo").length()   where expr can only be  inside '()' 

 */
bool table_value(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    printf("TABLE_VALUE=======\n");
    TL_print(tl);
    int length_of_tl=TL_length(tl);
    /*
     id table_value_key
     
     // new support
     string table_value_key              // "hello".length()
     list_table table_value_key          // [1,2,3].length()
     num table_value_key                 //  13.toString()
     */
    if (length_of_tl>=2 &&
        (term(tl->current_token.TOKEN_CLASS, "id")
         ||term(tl->current_token.TOKEN_CLASS, "string")
         ||term(tl->current_token.TOKEN_CLASS, "list_table")
         ||term(tl->current_token.TOKEN_CLASS, "num")
        )
        &&
        (term(tl->next->current_token.TOKEN_STRING, ".")||term(tl->next->current_token.TOKEN_CLASS, "list_table"))
        ) {
        int index=TREE_INDEX;
        TREE_addNode(tree, "table_value", "");
        
        
        TREE_addNode(TREE_getTreeAccordingToIndex(tree, index), tl->current_token.TOKEN_STRING, tl->current_token.TOKEN_CLASS);
        return table_value_key(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(tl, 1, length_of_tl));
    }
    else{
        if (term(tl->current_token.TOKEN_STRING, "(")) {
            
           
           
            int index_of_right=-1;
            Token_List *temp_tl=tl;
            int i=0;
            int count=0;
            for (; i<length_of_tl; i++) {
                if (term(temp_tl->current_token.TOKEN_STRING, "(")) {
                    count++;
                }
                else if (term(temp_tl->current_token.TOKEN_STRING, ")")) {
                    count--;
                }
                if (count==0) {
                    index_of_right=i;
                    break;
                }
                temp_tl=temp_tl->next;
            }
            
            
          
            
            if (index_of_right==-1) {
                return FALSE;
            }
            else{
                int index=TREE_INDEX;
                TREE_addNode(tree, "table_value", "");
               
                int index2=TREE_INDEX;
                TREE_addNode(TREE_getTreeAccordingToIndex(tree, index), "expr", "");
               
                return expr(TREE_getTreeAccordingToIndex(tree, index2), TL_subtl(tl, 0, index_of_right+1))&&
                table_value_key(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(tl, index_of_right+1, length_of_tl));
            }
        }
        
        
        
        return FALSE;
    }
}




/*
 table_value_key->
 | [(string|num)value]
 | '.' id
 | '.' func
 | '.' func table_value_key                            // behind is [] or '.'
 | [(string|num)value] table_value_key                 // behind is [] or '.'
 | '.' id table_value_key                              // behind is [] or '.'
 
 */

bool table_value_key(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    
    // [(string|num)value]
    if (length_of_tl==1 && term(tl->current_token.TOKEN_CLASS, "list_table")) {
        // get string inside []
        int length=(int)strlen(tl->current_token.TOKEN_STRING);
        char *string_inside=(char*)malloc(sizeof(char)*(length-2+1));
        int i=0;
        for (; i<length-2; i++) {
            string_inside[i]=tl->current_token.TOKEN_STRING[i+1];
        }
        string_inside[i]=0;
        //====================
        
        int index1=TREE_INDEX;
        TREE_addNode(tree, "key", "");
        
        
        Token_List *key_tl=Walley_Lexical_Analyzie(string_inside);
        TREE key_tree;
        TREE_initWithName(&key_tree, "key");
        value(&key_tree, key_tl);
        
        TREE_addTree(TREE_getTreeAccordingToIndex(tree, index1),key_tree);

        return TRUE;
    }
    //| '.' id
    else if (length_of_tl==2 && term(tl->current_token.TOKEN_STRING,".")&&term(tl->next->current_token.TOKEN_CLASS, "id")){
        int index1=TREE_INDEX;
        TREE_addNode(tree, "key", "");
        
        Token_List *key_tl=Walley_Lexical_Analyzie(toString(tl->next->current_token.TOKEN_STRING));
        TREE key_tree;
        TREE_initWithName(&key_tree, "key");
        value(&key_tree, key_tl);
        
        TREE_addTree(TREE_getTreeAccordingToIndex(tree, index1),key_tree);
        
        return TRUE;
    }
    //| '.' func
    //| '.' func table_value_key                            // behind is [] or '.'
    else if (length_of_tl>=4 && term(tl->current_token.TOKEN_STRING,".")&&term(tl->next->current_token.TOKEN_CLASS, "id") && term(tl->next->next->current_token.TOKEN_STRING, "(")){
        
        // find index_of_right
        Token_List *temp_tl=tl;
        int count=0;
        int i=2;
        temp_tl=temp_tl->next->next;
        int index_of_right=-1;
        for (; i<length_of_tl; i++) {
            if (term(temp_tl->current_token.TOKEN_STRING, "(")) {
                count++;
            }
            else if (term(temp_tl->current_token.TOKEN_STRING, ")")){
                count--;
            }
            if (count==0) {
                index_of_right=i;
                break;
            }
            temp_tl=temp_tl->next;
        }
        if (index_of_right==-1) {
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }

        
        //| '.' func
        if (index_of_right==length_of_tl-1) {
            int index1=TREE_INDEX;
            TREE_addNode(tree, "key", "");
            
            return func(TREE_getTreeAccordingToIndex(tree, index1), TL_subtl(tl, 1, length_of_tl));
        }
        
        //| '.' func table_value_key                            // behind is [] or '.'
        else{
            
            
            return table_value_key(tree, TL_subtl(tl, 0, index_of_right+1))&&table_value_key(tree, TL_subtl(tl, index_of_right+1, length_of_tl));
        }
       
        
    }
    //| [(string|num)value] table_value_key
    else if (length_of_tl>=2 && term(tl->current_token.TOKEN_CLASS, "list_table") &&
             (term(tl->next->current_token.TOKEN_STRING, ".")||term(tl->next->current_token.TOKEN_CLASS, "list_table"))
             ){
        return table_value_key(tree, TL_subtl(tl, 0, 1)) && table_value_key(tree, TL_subtl(tl, 1, length_of_tl));
    }
    //| '.' id table_value_key                              // behind is [] or '.'
    else if (length_of_tl>=3 && term(tl->current_token.TOKEN_STRING, ".")&&term(tl->next->current_token.TOKEN_CLASS, "id")
             &&(term(tl->next->next->current_token.TOKEN_STRING, ".")||term(tl->next->next->current_token.TOKEN_CLASS, "list_table"))
             ){
        return table_value_key(tree, TL_subtl(tl, 0, 2))&&table_value_key(tree, TL_subtl(tl, 2, length_of_tl));
    }
    else{
        return FALSE;
    }
    
}
