//
//  walley_assignment.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-20.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_math_parser.h"

/*
 a=12
 a[0]=13
 a,b=13
 
 
 assignment-> var_name '=' var_value
            | 'local' var_name '=' var_value
 
 version 1.0
 var_name->var_name ',' var_name
          | id
          | id '.' var_name
          | id list_s
 
 now use
 version 2.0
 var_name->var_name ',' var_name
          | id
          | table_value
 
 list_s->list_table list_s
       ->list_table
 
    
 var_value->value,var_value
          ->value       # where ',' is the , not inside def if elif else for while
 
*/

bool assignment(TREE *tree, Token_List *tl){
     
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    
    // | 'local' var_name '=' var_value
    bool is_local=FALSE;
    if (term(tl->current_token.TOKEN_STRING, "local")) {
        is_local=TRUE;
    }
    
    Token_List *temp_tl=tl;

    
    int count=0;
    int count_of_equal=0;
    int index_of_equal;
    int i=0;
    while (tl->next!=NULL) {
        if (term(tl->current_token.TOKEN_STRING, "(")
            ||term(tl->current_token.TOKEN_STRING, "if")
            ||term(tl->current_token.TOKEN_STRING, "def")
            ||term(tl->current_token.TOKEN_STRING, "for")
            ||term(tl->current_token.TOKEN_STRING, "while")) {
            count+=1;
        }
        else if (term(tl->current_token.TOKEN_STRING, ")")
                 ||term(tl->current_token.TOKEN_STRING, "end")){
            count-=1;
        }
        if (count==0&&strcmp(tl->current_token.TOKEN_STRING, "=")==0) {
            count_of_equal++;
            index_of_equal=i;
        }
        i++;
        tl=tl->next;
    }
    tl=temp_tl;
   
    // it is not assignment
    if (count_of_equal!=1) {
        return FALSE;
    }
    
    else{
        
        int length_of_tl=TL_length(tl);

        int save_TREE_INDEX=TREE_INDEX;
        
        TREE_INDEX=0;
        TREE var_name_tree;
        TREE_initWithName(&var_name_tree, "var_name");
        Token_List *var_name_list;
        // exclude local
        if (is_local) {
            var_name_list=TL_subtl(tl, 1, index_of_equal);
        }
        else{
            var_name_list=TL_subtl(tl, 0, index_of_equal);
        }
        var_name(&var_name_tree, var_name_list);

        
        TREE_INDEX=0;
        TREE var_value_tree;
        TREE_initWithName(&var_value_tree, "var_value");
        Token_List *var_value_list=TL_subtl(tl, index_of_equal+1, length_of_tl);
        
        
        var_value(&var_value_tree, var_value_list);
        
        TREE_INDEX=save_TREE_INDEX;
        
      

        
        int var_name_num=NL_length(var_name_tree.node_list);
              
        int i=0;
        Node_List *var_name_nl=var_name_tree.node_list;
        Node_List *var_value_nl=var_value_tree.node_list;
        for (; i<var_name_num; i++) {
            int index=TREE_INDEX;
            TREE_addNode(tree, "=", "");
      
            // local variable
            if (is_local) {
                TREE_addNode(TREE_getTreeAccordingToIndex(tree, index),"local", "");
            }
            TREE_addTree(TREE_getTreeAccordingToIndex(tree, index), var_name_nl->node);
            TREE_addTree(TREE_getTreeAccordingToIndex(tree, index), var_value_nl->node);
            
            // eg x,y=12
            // then x=12
            //      y=none
            Node_List *temp_var_value_nl=var_value_nl;
            var_name_nl=var_name_nl->next;
            var_value_nl=var_value_nl->next;
            if (var_value_nl==NULL) {
                var_value_nl=temp_var_value_nl;
                var_value_nl->node.name="none";
                var_value_nl->node.token_class="id";
                var_value_nl->node.node_list=NULL;
                
            }
        }
        
        
        return TRUE;
    }
}
/*
bool list_s(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    
    //list_table
    if (length_of_tl==1) {
        if (strcmp("list_table", tl->current_token.TOKEN_CLASS)==0) {
            tree->name=tl->current_token.TOKEN_STRING;
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    // list_table list_s
    else{
        int index1=TREE_INDEX;
        TREE_addNode(tree, "list_table", "");
        int index2=TREE_INDEX;
        TREE_addNode(tree, "list_s", "");
        
        Token_List *tl1=tl;
        tl1->next=NULL;
        
        return list(TREE_getTreeAccordingToIndex(tree, index1), tl1)
        && list_s(TREE_getTreeAccordingToIndex(tree, index2), tl->next);
    }
}
 */
/*
 var_name->var_name ',' var_name
 | id
 | table_value

 
 */
bool var_name(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int index_of_comma=TL_indexOfTokenThatHasTokenString(tl, ",");
    //var_name ',' var_name
    if (index_of_comma!=-1) {
        int length_of_tl=TL_length(tl);
        Token_List *tl1=TL_subtl(tl, 0, index_of_comma);
        Token_List *tl2=TL_subtl(tl, index_of_comma+1, length_of_tl);
        
        //int index_of_tl1=TREE_INDEX;
        //TREE_addNode(tree, "var_name", "");
        //int index_of_tl2=TREE_INDEX;
        //TREE_addNode(tree, "var_name", "");
        
        //return var_name(TREE_getTreeAccordingToIndex(tree, index_of_tl1), tl1)
        //&& var_name(TREE_getTreeAccordingToIndex(tree, index_of_tl2), tl2);
        return var_name(tree, tl1)
        && var_name(tree, tl2);

    }
    
    else{
        int length_of_tl=TL_length(tl);
        // id
        if (length_of_tl==1) {
            if (strcmp("id", tl->current_token.TOKEN_CLASS)==0){
                TREE_addNode(tree, tl->current_token.TOKEN_STRING,"id");
                
                return TRUE;
                //return value(tree, tl);
            }
            else
                return FALSE;
        }
        // table_value
        else{
            return table_value(tree, tl);
        }
    }
    //wtf wrong here
    return FALSE;
}

//# where ',' is the , not inside def if elif else for while
bool var_value(TREE *tree, Token_List *tl){
   
    
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    int index_of_comma=-1;
    Token_List *temp_tl=tl;
    int i=0;
    int count=0;
    for (; i<length_of_tl; i++) {
        if (term(tl->current_token.TOKEN_STRING, "def")
            ||term(tl->current_token.TOKEN_STRING, "for")
            ||term(tl->current_token.TOKEN_STRING, "if")
            ||term(tl->current_token.TOKEN_STRING, "while")
            ||term(tl->current_token.TOKEN_STRING, "(")) {
            count++;
        }
        if (term(tl->current_token.TOKEN_STRING, "end")
            ||term(tl->current_token.TOKEN_STRING, ")")) {
            count--;
        }
        if (count==0 && term(tl->current_token.TOKEN_STRING, ",")) {
            index_of_comma=i;
            break;
        }
        tl=tl->next;
    }
    
    if (count!=0) {
        INCOMPLETE_STATEMENT=TRUE;
        return FALSE;
    }
    
    
    tl=temp_tl;
    
    
    //int index_of_comma=TL_indexOfTokenThatHasTokenString(tl, ",");
    
    
    
    //value,var_value
    if (index_of_comma!=-1) {
        Token_List *tl1=TL_subtl(tl, 0, index_of_comma);
        Token_List *tl2=TL_subtl(tl, index_of_comma+1, length_of_tl);
        
        int index_of_tl1=TREE_INDEX;
        TREE_addNode(tree, "value", "");
        
        
        return value(TREE_getTreeAccordingToIndex(tree, index_of_tl1), tl1)
        &&var_value(tree,tl2);
        
    }
    //value
    else{
        
        int index_of_tl=TREE_INDEX;
        TREE_addNode(tree,"value","");

        return value(TREE_getTreeAccordingToIndex(tree, index_of_tl), tl);
    }
}