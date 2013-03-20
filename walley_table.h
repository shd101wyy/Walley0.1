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