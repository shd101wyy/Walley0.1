//
//  walley_cg_js.h
//  Walley0.1
//
//  Created by shd101wyy on 13-5-15.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_code_generation.h"

bool js_isTable=FALSE;

/*
    x=[1,2,3]
 
    -->
    x=[];
    x[0]=1;
    x[1]=2;
    x[2]=3;
 
 
 
 */
void JS_Table(Str_List **sl,char *var_name, Node_List *table_expr_nl){
    while (table_expr_nl!=NULL) {
        
        TREE key_tree=table_expr_nl->node.node_list->node;
        TREE value_tree=table_expr_nl->node.node_list->next->node;
        
        //TREE_print(key_tree);
        
        char *key_str=key_tree.node_list->node.name;
        char *value_str=Code_Generation_2_Javascript(sl, value_tree);
        
        table_expr_nl=table_expr_nl->next;
        
        char *append_string=var_name;
        append_string=append(append_string,"[");
        append_string=append(append_string, key_str);
        append_string=append(append_string, "]");
        
        if (term(value_str, "[]")) {
            JS_Table(sl, append_string, value_tree.node_list);
        }
        else{
        
        
            append_string=append(append_string, "=");
            append_string=append(append_string, value_str);
            append_string=append(append_string, ";");
            SL_addString(sl, append_string);

        }
        //printf("---> %s\n",append_string);
    }

}

// compile to javascript
char* Code_Generation_2_Javascript(Str_List **sl,TREE tree){
    if (term(tree.name, "walley_statements")) {
        
        printf("walley_statements\n");
        Node_List *nl=tree.node_list;
        while (nl!=NULL) {
            Code_Generation_2_Javascript(sl, nl->node);
            nl=nl->next;
        }
        
        return "";
    }
    
    else if (term(tree.name, "statements")){
        printf("statements\n");
        Node_List *nl=tree.node_list;
        
        if (term(nl->node.name, "if")) {
            printf("if\n");
            /*
             ( statements
                ( if)
                ( simple_relation
                    ( <(num 4)(id x))
                )
                ( statements
                    ( =(id x)(num 12))
                )
             )
             ( statements( end))
             
             ( statements
                ( if)
                ( relation
                    ( and
                        ( simple_relation( <(num 4)(id x)))
                        ( simple_relation( <(id x)(num 12))))
                )
                ( statements( =(id x)(num 12))))
             ( statements( end))
             */
            
            char *append_str="if (";
            char *judge_str=Code_Generation_2_Javascript(sl, nl->next->node);
            
            printf("judge_str----> %s\n",judge_str);
            
            append_str=append(append_str, judge_str);
            append_str=append(append_str,"){");
            
            printf("append_str----> %s\n",append_str);
            SL_addString(sl, append_str);
            
            nl=nl->next->next;
            while (nl!=NULL) {
                Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
            }
        }
        else if (term(nl->node.name, "elif")){
            SL_addString(sl, "}");
            
            char *append_str="else if (";
            char *judge_str=Code_Generation_2_Javascript(sl, nl->next->node);
            
            printf("judge_str----> %s\n",judge_str);
            
            append_str=append(append_str, judge_str);
            append_str=append(append_str,"){");
            
            printf("append_str----> %s\n",append_str);
            SL_addString(sl, append_str);
            
            nl=nl->next->next;
            while (nl!=NULL) {
                Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
            }
        }
        else if (term(nl->node.name, "else")){
            SL_addString(sl, "}");
            char *append_str="else{";
            SL_addString(sl, append_str);
            nl=nl->next;
            while (nl!=NULL) {
                Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
            }
        }
        else if(term(nl->node.name, "while")){
            /*
             ( walley_statements
                ( statements
                    ( while)
                    ( simple_relation( <(id x)(num 10)))
                    ( statements( =(id x)(num 12)))
                    ( end)
                )
            )
             */
            char *append_str="while (";
            char *judge_str=Code_Generation_2_Javascript(sl, nl->next->node);
            
            printf("judge_str----> %s\n",judge_str);
            
            append_str=append(append_str, judge_str);
            append_str=append(append_str,"){");
            
            printf("append_str----> %s\n",append_str);
            SL_addString(sl, append_str);
            
            nl=nl->next->next;
            while (nl!=NULL) {
                Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
            }
        }
        else if (term(nl->node.name,"for")){
            printf("for\n");
            /*
             // for i=0,i<10,i=i+1 then i=2 end
            ( walley_statements
                ( statements
                    ( for)
                    ( assignment
                        ( =(id i)(num 0))
                    )
                    ( simple_relation
                        ( <(id i)(num 10))
                    )
                    ( assignment( =(id i)( +(id i)(num 1))))
                    ( statements( =(id i)(num 2)))
                    ( end)
                )
             )
             */
            char *append_str="for (";
            
            if (term(nl->next->node.name, "assignment")) {
                printf("assignment\n");
                exit(0);
            }
            else{
                append_str=append(append_str,";");
            }
            
            char *judge_str=Code_Generation_2_Javascript(sl, nl->next->node);
            
            printf("judge_str----> %s\n",judge_str);
            
            append_str=append(append_str, judge_str);
            append_str=append(append_str,"){");
            
            printf("append_str----> %s\n",append_str);
            SL_addString(sl, append_str);
            
            nl=nl->next->next;
            while (nl!=NULL) {
                Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
            }

        }
        else{
            while (nl!=NULL) {
                Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
            }
        }
        
        return "";
    }
    
    // this place has problem
    else if (term(tree.name, "relation")){
        printf("relation\n");
        TREE judge_tree=tree.node_list->node;
        //<(num 4)(id x)
        
        TREE left_tree=judge_tree.node_list->node;
        TREE right_tree=judge_tree.node_list->next->node;
        
        char *left_str=Code_Generation_2_Javascript(sl, left_tree);
        char *right_str=Code_Generation_2_Javascript(sl, right_tree);
        char *append_str=left_str;
        char *relationship;
        if (term(judge_tree.name, "and")) {
            relationship=" && ";
        }
        else{
            relationship=" || ";
        }
        append_str=append(append_str, relationship);
        append_str=append(append_str, right_str);
        
        return append_str;
    }
    
    // this place has problem
    else if (term(tree.name, "simple_relation")){
        printf("simple_relation\n");
        TREE judge_tree=tree.node_list->node;
        //<(num 4)(id x)
        
        TREE left_tree=judge_tree.node_list->node;
        TREE right_tree=judge_tree.node_list->next->node;
        
        char *left_str=Code_Generation_2_Javascript(sl, left_tree);
        char *right_str=Code_Generation_2_Javascript(sl, right_tree);
        char *append_str=left_str;
        append_str=append(append_str, judge_tree.name);
        append_str=append(append_str, right_str);
        
        return append_str;
    }
    
    // append
    else if (term(tree.name,"=")){
        bool is_local=FALSE;
        char *append_string;
        printf("assign\n");
        
        Node_List *nl=tree.node_list;
        TREE var_name_tree=nl->node;
        if (term(var_name_tree.name, "local")) {
            is_local=TRUE;
            var_name_tree=nl->next->node;
        }
        TREE var_value_tree;
        if (is_local) {
            var_value_tree=nl->next->next->node;
        }
        else{
            var_value_tree=nl->next->node;
        }
        
        char *var_name=Code_Generation_2_Javascript(sl, var_name_tree);
        append_string=var_name;
        if (is_local) {
            append_string=append("var ", append_string);
        }
        
        append_string=append(append_string, "=");
        
        //func_value
        if (term(var_value_tree.name, "func_value")) {
            printf("func_value");
            append_string=append(append_string,"function(");
            char *param_str=Code_Generation_2_Javascript(sl, var_value_tree.node_list->next->node);
            append_string=append(append_string, param_str);
            append_string=append(append_string, "){");
            SL_addString(sl, append_string);
            
            //( func_value( def)( params(id none))( statements( =(id a)(num 12)))( end))
            /*
             ( func_value
             ( def)
             ( params(id none))
             ( statements( =(id a)(num 12)))
             ( end)
             )
             
             
             */
            /*
             char *append_string="function(";
             char *param_str=Code_Generation_2_Javascript(sl, tree.node_list->next->node);
             append_string=append(append_string, param_str);
             append_string=append(append_string, "){\n");
             */
            Node_List *nl=var_value_tree.node_list->next->next;
            while (nl->next!=NULL) {
                Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
            }
            SL_addString(sl, "};");
            return "";
        }
        
        char *var_value=Code_Generation_2_Javascript(sl, var_value_tree);
        append_string=append(append_string, var_value);
        append_string=append(append_string,";");

        //printf("append_str----> %s\n",append_string);
        SL_addString(sl, append_string);
        
        // is table
        if (js_isTable) {
            js_isTable=FALSE;
            Node_List *table_expr_nl=var_value_tree.node_list;
            JS_Table(sl, var_name, table_expr_nl);
        }
        
        return "";
        
    }
    
    else if (term(tree.token_class, "table")){
        js_isTable=TRUE;
        return "[]";
    }
    
    else if(term(tree.name, "table_value")){
        Node_List *nl=tree.node_list;
        char *var_name=nl->node.name;
        TREE key_tree=nl->next->node.node_list->node;
        char *key_str=Code_Generation_2_Javascript(sl, key_tree);
        
        printf("key_str %s\n",key_str);
        
        char *append_str=var_name;
        append_str=append(append_str, "[");
        append_str=append(append_str, key_str);
        append_str=append(append_str, "]");
        return append_str;
        

    }
    else if (term(tree.name,"params")){
        char *append_string="";
        Node_List *nl=tree.node_list;
        while (nl!=NULL) {
            if (term(nl->node.name, "=")) {
                printf("Does not support = in params now\n");
                exit(0);
            }
            append_string=append(append_string, Code_Generation_2_Javascript(sl, nl->node));
            if (nl->next!=NULL) {
                append_string=append(append_string, ",");
            }
            nl=nl->next;
        }
        return append_string;
    }
    else if (term(tree.name, "end")){
        SL_addString(sl, "}");
        return "";
    }
    
    else if (term(tree.token_class,"id")){
        return tree.name;
    }
    
    else if (term(tree.token_class, "num")){
        return tree.name;
    }
    
    else if (term(tree.token_class, "string")){
        return tree.name;
    }
    
    else if(ism_operator(tree.name)){
        Node_List *nl=tree.node_list;
        TREE left=nl->node;
        TREE right=nl->next->node;
        
        char *left_str=Code_Generation_2_Javascript(sl, left);
        char *right_str=Code_Generation_2_Javascript(sl, right);
        
        bool left_need_bracket=TRUE;
        bool right_need_bracket=TRUE;
        
        if (term(left.token_class, "id")||term(left.token_class, "string")||term(left.token_class, "num")) {
            left_need_bracket=FALSE;
        }
        
        if (term(right.token_class, "id")||term(right.token_class, "string")||term(right.token_class, "num")) {
            right_need_bracket=FALSE;
        }
        
        
        bool need_bracket=FALSE;
        if (term(tree.name, "*")||term(tree.name, "/")||term(tree.name, "^")||term(tree.name, "%")) {
            need_bracket=TRUE;
        }
        
        if (need_bracket) {
            char *append_str=left_str;
            if (left_need_bracket) {
                append_str=append("(", append_str);
                append_str=append(append_str, ")");
            }
    
            append_str=append(append_str,tree.name);
            if(right_need_bracket){
                append_str=append(append_str,"(");
                append_str=append(append_str, right_str);
                append_str=append(append_str,")");
            }
            else{
                append_str=append(append_str, right_str);
            }
            return append_str;
        }
        else{
            char *append_str=left_str;
            append_str=append(append_str, tree.name);
            append_str=append(append_str, right_str);
            return append_str;
        }
    }
    
    else{
        printf("Code Generation Error..\n");
        exit(0);
    }
    
    
}