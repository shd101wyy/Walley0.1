//
//  walley_cg_js.h
//  Walley0.1
//
//  Created by shd101wyy on 13-5-15.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_code_generation.h"

bool js_isTable=FALSE;
bool js_isTableValue=FALSE;

/*
    x=[1,2,3]
 
    -->
    x=[];
    x[0]=1;
    x[1]=2;
    x[2]=3;
 
 
 
 */
// "Hello" is string
// "Hello"+"Hi" is not string
// Hello is not string
Str_List *file_getStringList(char *file_name){
    FILE *fp=fopen(file_name, "r");
    if (fp==NULL) {
        printf("File %s not existed\n",file_name);
        exit(0);
    }
    char c=getc(fp);    
    Str_List *sl;
    SL_initSL(&sl);
    
    Char_List *cl;
    CL_init(&cl);
    while (c!=EOF) {
        if (c!='\n') {
            CL_addChar(&cl, c);
        }
        // new line
        if (c=='\n') {
            SL_addString(&sl, CL_toString(cl));
            CL_init(&cl);
        }
        c=getc(fp);
    }
    SL_addString(&sl, CL_toString(cl));
    fclose(fp);
    
    return sl;
    
}
bool isString(char *input_str){
    if (input_str[0]!='"'||input_str[(int)strlen(input_str)-1]!='"') {
        return FALSE;
    }
    int count=0;
    int i=0;
    int length=(int)strlen(input_str);
    for (; i<length; i++) {
        if (input_str[i]=='"') {
            count++;
        }
    }
    if (count!=2) {
        return FALSE;
    }
    else{
        return TRUE;
    }
}

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
            SL_addString(sl, append(append_string, "=[];"));
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
            char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
            nl=nl->next;
            
            if ((int)strlen(temp_str)!=0) {
                return temp_str;
            }
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
                Code_Generation_2_Javascript(sl, nl->next->node.node_list->node);
                nl=nl->next->next;
                printf("assignment\n");
                //exit(0);
            }
            else{
                nl=nl->next;
            }
            append_str=append(append_str,";");
            
            // nl now is relation
            char *judge_str=Code_Generation_2_Javascript(sl, nl->node);
            
            append_str=append(append_str, judge_str);
            append_str=append(append_str, ";){");
            SL_addString(sl, append_str);
            
            nl=nl->next;
            Node_List *temp_nl;
            bool has_assignment_after_judge=FALSE;
            if (term(nl->node.name, "assignment")) {
                has_assignment_after_judge=TRUE;
                temp_nl=nl;
                nl=nl->next;
            }
            
            while (nl->next!=NULL) {
                Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
            }
            if (has_assignment_after_judge) {
                Code_Generation_2_Javascript(sl, temp_nl->node.node_list->node);
            }
            SL_addString(sl, "}");
            
            //printf("judge_str----> %s\n",judge_str);
            //printf("append_str---> %s\n",append_str);
            //exit(0);
            
           // append_str=append(append_str, judge_str);
           // append_str=append(append_str,"){");
            
           // printf("append_str----> %s\n",append_str);
           // SL_addString(sl, append_str);
            
           // nl=nl->next->next;
           // while (nl!=NULL) {
           //    Code_Generation_2_Javascript(sl, nl->node);
           //     nl=nl->next;
           // }

        }
        /*
         ( walley_statements
            ( statements
                ( foreach)
                (foreach_index i)
                (foreach_value v)
                (foreach_in 
                    ( +(string "Hello")(num 13))
                )
                ( statements( =(id i)(num 2)))
                ( end)
            )
         )
         
         */
        else if (term(nl->node.name, "foreach")){
            printf("For Each\n");
            char *append_str="for(";
            // for i,v in x
            // get i
            char *foreach_index=nl->next->node.name;
            append_str=append(append_str, foreach_index);
            append_str=append(append_str, " in ");
            
            
            bool has_v=TRUE;
            Node_List *foreach_in_nl;
            if (term(nl->next->next->node.name, "")) {
                
                has_v=FALSE;
                foreach_in_nl=nl->next->next->next;
            }
            else{
                foreach_in_nl=nl->next->next->next;
            }
            
            char *foreach_in_value=Code_Generation_2_Javascript(sl, foreach_in_nl->node.node_list->node);
            // append in value
            append_str=append(append_str,foreach_in_value);
            append_str=append(append_str, "){");
            
            printf("append_str----> %s\n",append_str);
            SL_addString(sl, append_str);
            
            if (has_v) {
                
                char *value_var_name=foreach_in_nl->ahead->node.name;
                append_str=append(value_var_name,"=");
                
                char *in_value=append("(", append(foreach_in_value, ")"));
                char *in_value_and_key=append(in_value, append("[", append(foreach_index,"]")));
                
                append_str=append(append_str, in_value_and_key);
                printf("append_str----> %s\n",append_str);
                SL_addString(sl, append_str);
            }
            
            nl=foreach_in_nl->next;
            while (nl!=NULL) {
                Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
            }
            
            return "";
        }
        else{
            while (nl!=NULL) {
                char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
                
                if ((int)strlen(temp_str)!=0) {
                    return temp_str;
                }
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
        js_isTableValue=TRUE;
        Node_List *nl=tree.node_list;
        char *var_name=nl->node.name;
        char *append_str=var_name;

        nl=nl->next;
        while (nl!=NULL) {
            TREE key_tree=nl->node;
            char *key_str=Code_Generation_2_Javascript(sl, key_tree);
            if (term(key_tree.name,"func")) {
                append_str=append(append_str,".");
            }
            
            printf("key_str %s\n",key_str);
            
            append_str=append(append_str, key_str);

            
            nl=nl->next;
        }
        
        printf("append_str---> %s\n",append_str);
        js_isTableValue=FALSE;
        return append_str;
        

    }
    else if (term(tree.name, "key")){
        TREE key_tree=tree.node_list->node;
        return append("[", append(Code_Generation_2_Javascript(sl, key_tree), "]"));
    }
    /*
     ( func
        (call toString)
        ( params
            (id b)
            (id c)
        )
     )
     
     */
    else if (term(tree.name, "func")){
        printf("func\n");
        char *append_str; //=tree.node_list->node.name;
        if (js_isTableValue==FALSE) {
            char *func_name=tree.node_list->node.name;
            // embed func
            if (term(func_name, "puts")) {
                append_str="console.log";
            }
            // not embed func
            else{
                append_str=tree.node_list->node.name;

            }
        }
        else{
            append_str=tree.node_list->node.name;
        }
        
        
        append_str=append(append_str, "(");
        
        TREE params_tree=tree.node_list->next->node;
        Node_List *params_nl=params_tree.node_list;
        while (params_nl!=NULL) {
            append_str=append(append_str,Code_Generation_2_Javascript(sl, params_nl->node));
            if(params_nl->next!=NULL){
                append_str=append(append_str,",");
            }
            params_nl=params_nl->next;
        }
        
        append_str=append(append_str, ")");
        return append_str;
    }
    else if (term(tree.name, "value")){
        Node_List *nl=tree.node_list;
        return Code_Generation_2_Javascript(sl, nl->node);
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
        
        if ((stringIsDigit(left_str)||isString(left_str))&&(stringIsDigit(right_str)||isString(right_str))) {
            printf("Can calculate directly %s %s %s",left_str,right_str,tree.name);
            char *value=Walley_Calculation(left_str, right_str, tree.name);
            return value;
        }
        
        
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
    else if (term(tree.name, "expr")){
        return Code_Generation_2_Javascript(sl, tree.node_list->node);
    }
    else{
        printf("Code Generation Error..\n");
        exit(0);
    }
}

Str_List *Compile_to_JS(char *file_name){
    int length=(int)strlen(file_name);
    if (file_name[length-1]!='y'||file_name[length-2]!='w'||file_name[length-3]!='.') {
        printf("File format wrong.. need .wy file\n");
        exit(0);
    }
    Str_List *sl_in_file=file_getStringList(file_name);
    Str_List *output_sl;
    SL_initSL(&output_sl);
    
    while (sl_in_file!=NULL) {
        Token_List *tl=Walley_Lexical_Analyzie(sl_in_file->string_content);
        TREE tree=parser(tl);
        char *output_str=Code_Generation_2_Javascript(&output_sl, tree);
        
        if (term(output_str, "")==FALSE) {
            SL_addString(&output_sl, output_str);
        }
        sl_in_file=sl_in_file->next;
    }
    
    return output_sl;
}