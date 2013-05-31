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
    else if (term(tl->current_token.TOKEN_CLASS, "list_table") && tl->next!=NULL && term(tl->next->current_token.TOKEN_STRING, "=")){
        // THIS PLACE HAS SOME PROBLEM
        //printf("'[' (string|int) ']' '=' (value)  HAS NOT BEEN IMPLEMENTED\n");
        
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
            list_string2=trim(list_string2);
            
            // content empty
            // x=[]
            if (strlen(list_string2)==0) {
                return TRUE;
            }
            
            
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
 | [(string|num)value|slice]        # slice need ":"    like ':3' ':3' or '0:3'
 | '.' id
 | '.' func
 | '.' func table_value_key                            // behind is [] or '.'
 | [(string|num)value] table_value_key                 // behind is [] or '.'
 
 // new on 05/18/2013
 | [(string|num)value] '(' params ')' table_value_key
 
 | '.' id table_value_key                              // behind is [] or '.'
 
table_value ->
            id table_value_key
 
        // new support 
            string table_value_key              // "hello".length()
            list_table table_value_key          // [1,2,3].length()
            num table_value_key                 //  13.toString()
            expr table_value_key                //  ("He"+"llo").length() where expr can only be  inside '()' 
        // new support on 05/24/2013
            func table_value_key

*/

/*
 table_value ->
        id table_value_key
 
        // new support
        string table_value_key              // "hello".length()
        list_table table_value_key          // [1,2,3].length()
        num table_value_key                 //  13.toString()
        expr table_value_key                //  ("He"+"llo").length()   where expr can only be  inside '()' 
 
        // new support on 05/24/2013
        func table_value_key


 */
bool table_value(TREE *tree, Token_List *tl){
    
    
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
   
    int length_of_tl=TL_length(tl);
    
    
    // check whether have m_operator to solve a.length-1 parser error
    Token_List *temp_tl=tl;
    while (temp_tl!=NULL) {
        if (term(temp_tl->current_token.TOKEN_CLASS, "m_operator")) {
            return FALSE;
        }
        temp_tl=temp_tl->next;
    }
    
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
    // new support on 05/24/2013
    //func table_value_key
    else if (length_of_tl>=3 && term(tl->current_token.TOKEN_CLASS, "id") && term(tl->next->current_token.TOKEN_STRING, "(")){
        int index=-1; // find index of )
        
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
                    index=i;
                    break;
                }
            }
            temp_tl=temp_tl->next;
            i++;
        }
        
        
        // fix 'add(3,4)' bug
        if (index==length_of_tl-1) {
            return FALSE;
        }
        
        // fix 'a() and b()' bug
        if (term(temp_tl->next->current_token.TOKEN_CLASS, "relation")) {
            return FALSE;
        }
        
        int tree_index=TREE_INDEX;
        TREE_addNode(tree, "table_value", "");
        int tree_index2=TREE_INDEX;
        TREE_addNode(TREE_getTreeAccordingToIndex(tree, tree_index), "func", "");
        func(TREE_getTreeAccordingToIndex(tree, tree_index2), TL_subtl(tl, 0, index+1));
        
        return table_value_key(TREE_getTreeAccordingToIndex(tree, tree_index), TL_subtl(tl, index+1, length_of_tl));
    }
    
    // expr table_value_key                //  ("He"+"llo").length()   where expr can only be  inside '()'
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
                if (index_of_right==length_of_tl-1) {
                    return FALSE;
                }
                
                // solve (a+3)^2 like problem
                if (term(TL_tokenAtIndex(tl, index_of_right+1).TOKEN_CLASS, "list_table")==FALSE || term(TL_tokenAtIndex(tl, index_of_right+1).TOKEN_STRING, ".")==FALSE) {
                    return FALSE;
                }
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
 | [(string|num)value|slice]        # slice need ":"    like ':3' ':3' or '0:3'
 | '.' id
 | '.' func
 | '.' func table_value_key                            // behind is [] or '.'
 | [(string|num)value] table_value_key                 // behind is [] or '.'
 
 // new on 05/18/2013
 | [(string|num)value] '(' params ')' table_value_key
 
 | '.' id table_value_key                              // behind is [] or '.'
 
 */

bool table_value_key(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    
    
    int length_of_tl=TL_length(tl);
    
    // [(string|num)value|slice]        # slice need ":"    like ':3' ':3' or '0:3'
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
        
        
        Token_List *key_tl=Walley_Lexical_Analyzie(string_inside);
        
        // check whether have :
        int index_of_colon=-1;
        Token_List *temp_tl=key_tl;
        int a=0;
        while (temp_tl!=NULL) {
            if (term(temp_tl->current_token.TOKEN_STRING, ":")) {
                index_of_colon=a;
                break;
            }
            a=a+1;
            temp_tl=temp_tl->next;
        }
        
        // not slice
        if (index_of_colon==-1) {
            
            int index1=TREE_INDEX;
            TREE_addNode(tree, "key", "");
            
            
            TREE key_tree;
            TREE_initWithName(&key_tree, "key");
            value(&key_tree, key_tl);
            
            TREE_addTree(TREE_getTreeAccordingToIndex(tree, index1),key_tree);
            
            return TRUE;

        }
        
        // slice
        else{
            int length_of_key_tl=TL_length(key_tl);
            int index1=TREE_INDEX;
            TREE_addNode(tree, "key", "");
            
            
            TREE slice_tree;
            TREE_initWithName(&slice_tree, "slice");
            
            Token_List *left_tl;
            Token_List *right_tl;
            
            // has no left
            if (index_of_colon==0) {
                left_tl=NULL;
            }
            else{
                left_tl=TL_subtl(key_tl, 0, index_of_colon);
            }
            
            // has no right
            if (index_of_colon==length_of_key_tl-1) {
                right_tl=NULL;
            }
            else{
                right_tl=TL_subtl(key_tl, index_of_colon+1, length_of_key_tl);
            }
            // add left
            int index_left=TREE_INDEX;
            if (left_tl==NULL) {
                TREE_addNode(&slice_tree, "0","num");
            }
            else{
                TREE_addNode(&slice_tree, "value", "");
                value(TREE_getTreeAccordingToIndex(&slice_tree, index_left), left_tl);
            }
            
            // add right
            int index_right=TREE_INDEX;
            if (right_tl==NULL) {
                TREE_addNode(&slice_tree, "its_length","special");
            }
            else{
                TREE_addNode(&slice_tree, "value", "");
                value(TREE_getTreeAccordingToIndex(&slice_tree, index_right), right_tl);
            }

            
            
            
            
            
            TREE_addTree(TREE_getTreeAccordingToIndex(tree, index1),slice_tree);
            
            return TRUE;
        }
        
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
    
    //| [(string|num)value] '(' params ')' table_value_key
    else if (length_of_tl>=3 && term(tl->current_token.TOKEN_CLASS, "list_table") && term(tl->next->current_token.TOKEN_STRING, "(")){
       
        // get index_of )
        int index=-1;
        int count=0;
        Token_List *temp_tl=tl;
        int i=0;
        while (temp_tl!=NULL) {
            if (term(temp_tl->current_token.TOKEN_STRING,"(")) {
                count++;
            }
            else if (term(temp_tl->current_token.TOKEN_STRING, ")")){
                count--;
                if (count==0) {
                    index=i;
                    break;
                }
                
            }
            i++;
            temp_tl=temp_tl->next;
        }
        
        // index = -1 incomplete
        if(index==-1){
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
        
        
        TREE func_tree;
        TREE_initWithName(&func_tree, "func");
        int tree_index=TREE_INDEX;
        TREE_addNode(&func_tree, "", "table_call");
        TREE_addNode(TREE_getTreeAccordingToIndex(&func_tree, tree_index), "", "");
        tree_index+=1;

        // get string inside []
        int length=(int)strlen(tl->current_token.TOKEN_STRING);
        char *string_inside=(char*)malloc(sizeof(char)*(length-2+1));
        i=0;
        for (; i<length-2; i++) {
            string_inside[i]=tl->current_token.TOKEN_STRING[i+1];
        }
        string_inside[i]=0;
        //====================
        Token_List *string_inside_tl=Walley_Lexical_Analyzie(string_inside);
        value(TREE_getTreeAccordingToIndex(&func_tree, tree_index), string_inside_tl);

        tree_index=TREE_INDEX;
        TREE_addNode(&func_tree, "params", "");
        if (2!=index) {
            params(TREE_getTreeAccordingToIndex(&func_tree, tree_index), TL_subtl(tl, 2, index));

        }

        TREE_addTree(tree, func_tree);

        if (index==length_of_tl-1) {
            return TRUE;
        }
        exit(0);

        return table_value(tree, TL_subtl(tl, index+1, length_of_tl));


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
