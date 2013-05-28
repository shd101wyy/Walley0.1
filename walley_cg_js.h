//
//  walley_cg_js.h
//  Walley0.1
//
//  Created by shd101wyy on 13-5-15.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_calculation.h"

bool js_isTableValue=FALSE;

/*
 (table [1,2,3]
    ( table_expr
        ( key(num 0))
        (num 1)
    )
    ( table_expr
        ( key(num 1))
        (num 2))
    ( table_expr
        ( key(num 2))
        (num 3)
    )
)
 
 */

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
    if (term("", trim(CL_toString(cl)))==FALSE) {
        SL_addString(&sl, CL_toString(cl));
    }
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
            append_string=append(append_string, ";\n");
            SL_addString(sl, append_string);

        }
        //printf("---> %s\n",append_string);
    }

}

// remove /n
char *JS_min(Str_List *sl){
    char *temp=SL_toString(sl);
    int length=(int)strlen(temp);
    char *output=(char*)malloc(sizeof(char)*(length+1));
    int i=0;
    int count=0;
    int index=0;
    for (; i<length; i++) {
        if (temp[i]=='"') {
            count++;
            output[index]='"';
            index++;
        }
        else if (temp[i]=='\n' && count%2==0){
            continue;
        }
        else{
            output[index]=temp[i];
            index++;
        }
        
    }
    output[index]=0;
    return output;
}

// compile to javascript
char* Code_Generation_2_Javascript(Str_List **sl,TREE tree){
    if (term(tree.name, "walley_statements")) {
        
        Node_List *nl=tree.node_list;
        
        char *output_str="";
        
        while (nl!=NULL) {
            char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
            nl=nl->next;
            
            if ((int)strlen(temp_str)!=0) {
                output_str=append(output_str,temp_str);
                if (output_str[(int)strlen(output_str)-1]!='\n') {
                    output_str=append(output_str, "\n");
                }
            }
        }
        
        return output_str;
    }
    
    else if (term(tree.name, "statements")){
        Node_List *nl=tree.node_list;
        
        if (term(nl->node.name, "if")) {
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
            
            
            append_str=append(append_str, judge_str);
            append_str=append(append_str,"){\n");
            
            
            nl=nl->next->next;
            
            char *output_str="";
            
            while (nl!=NULL) {
                char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
                
                if ((int)strlen(temp_str)!=0) {
                    output_str=append(output_str,temp_str);
                    if (output_str[(int)strlen(output_str)-1]!='\n') {
                        output_str=append(output_str, "\n");
                    }
                }
            }
            append_str=append(append_str, output_str);
            return append_str;
        }
        else if (term(nl->node.name, "elif")){
            //SL_addString(sl, "}\n");
            
            char *append_str="}\nelse if (";
            char *judge_str=Code_Generation_2_Javascript(sl, nl->next->node);
            
            
            append_str=append(append_str, judge_str);
            append_str=append(append_str,"){\n");
            
            //SL_addString(sl, append_str);
            
            nl=nl->next->next;
            char *output_str="";
            
            while (nl!=NULL) {
                char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
                
                if ((int)strlen(temp_str)!=0) {
                    output_str=append(output_str,temp_str);
                    if (output_str[(int)strlen(output_str)-1]!='\n') {
                        output_str=append(output_str, "\n");
                    }
                }
            }
            //SL_addString(sl, output_str);
            append_str=append(append_str, output_str);
            return append_str;
        }
        else if (term(nl->node.name, "else")){
            //SL_addString(sl, "}\n");
            char *append_str="}\nelse{\n";
            //SL_addString(sl, append_str);
            nl=nl->next;
            char *output_str="";
            
            while (nl!=NULL) {
                char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
                
                if ((int)strlen(temp_str)!=0) {
                    output_str=append(output_str,temp_str);
                    if (output_str[(int)strlen(output_str)-1]!='\n') {
                        output_str=append(output_str, "\n");
                    }
                }
            }
            append_str=append(append_str, output_str);
            return append_str;

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
            
            
            append_str=append(append_str, judge_str);
            append_str=append(append_str,"){\n");
            
            //SL_addString(sl, append_str);
            
            nl=nl->next->next;
            char *output_str="";
            
            while (nl!=NULL) {
                char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
                
                if ((int)strlen(temp_str)!=0) {
                    output_str=append(output_str,temp_str);
                    if (output_str[(int)strlen(output_str)-1]!='\n') {
                        output_str=append(output_str, "\n");
                    }
                }
            }
            append_str=append(append_str, output_str);
            return append_str;
        }
        else if (term(nl->node.name,"for")){
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
                append_str=append(append_str,Code_Generation_2_Javascript(sl, nl->next->node.node_list->node));
                nl=nl->next->next;
                //exit(0);
            }
            else{
                append_str=append(append_str, ";");
                nl=nl->next;
            }
            
            // nl now is relation
            char *judge_str=Code_Generation_2_Javascript(sl, nl->node);
            
            append_str=append(append_str, judge_str);
            append_str=append(append_str, ";){\n");
            //SL_addString(sl, append_str);
            
            nl=nl->next;
            Node_List *temp_nl;
            bool has_assignment_after_judge=FALSE;
            if (term(nl->node.name, "assignment")) {
                has_assignment_after_judge=TRUE;
                temp_nl=nl;
                nl=nl->next;
            }
            
            char *output_str="";
            
            while (nl->next!=NULL) {
                char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
                
                if ((int)strlen(temp_str)!=0) {
                    output_str=append(output_str,temp_str);
                    if (output_str[(int)strlen(output_str)-1]!='\n') {
                        output_str=append(output_str, "\n");
                    }
                }
            }
            append_str=append(append_str, output_str);
            //SL_addString(sl, output_str);

            if (has_assignment_after_judge) {
                append_str=append(append_str,Code_Generation_2_Javascript(sl, temp_nl->node.node_list->node));
            }
            append_str=append(append_str, "\n}\n");
            //SL_addString(sl, "}\n");
            return append_str;
           
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
            append_str=append(append_str, "){\n");
            
            
            if (has_v) {
                
                char *value_var_name=foreach_in_nl->ahead->node.name;
                append_str=append(append_str,append(value_var_name,"="));
                
                char *in_value=append("(", append(foreach_in_value, ")"));
                char *in_value_and_key=append(in_value, append("[", append(foreach_index,"]")));
                
                append_str=append(append_str, in_value_and_key);
                append_str=append(append_str, ";\n");
            }
            
            nl=foreach_in_nl->next;
            char *output_str="";
            
            while (nl!=NULL) {
                char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
                
                if ((int)strlen(temp_str)!=0) {
                    output_str=append(output_str,temp_str);
                    if (output_str[(int)strlen(output_str)-1]!='\n') {
                        output_str=append(output_str, "\n");
                    }
                }
            }
            append_str=append(append_str,output_str);            
            return append_str;
        }
        else{
            char *output_str="";
            while (nl!=NULL) {
                char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
                nl=nl->next;
                
                if ((int)strlen(temp_str)!=0) {
                    output_str=append(output_str,temp_str);
                    if (output_str[(int)strlen(output_str)-1]!='\n') {
                        if (output_str[(int)strlen(output_str)-1]!=';') {
                            output_str=append(output_str, ";\n");
                        }else{
                            output_str=append(output_str, "\n");
                        }
                    }
                }
            }
            return output_str;
        }
        
        return "";
    }
    
    // this place has problem
    else if (term(tree.name, "relation")){
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
        TREE judge_tree=tree.node_list->node;
        //<(num 4)(id x)
        
        TREE left_tree=judge_tree.node_list->node;
        TREE right_tree=judge_tree.node_list->next->node;
        
        char *left_str=Code_Generation_2_Javascript(sl, left_tree);
        char *right_str=Code_Generation_2_Javascript(sl, right_tree);
        char *append_str=left_str;
        
        char *judge_sign=judge_tree.name;
        if (term(judge_sign, "==")) {
            judge_sign="===";
        }
        else if (term(judge_sign, "!=")){
            judge_sign="!==";
        }
        
        append_str=append(append_str, judge_sign);
        append_str=append(append_str, right_str);
        
        return append_str;
    }
    
    // append
    else if (term(tree.name,"=")){
        bool is_local=FALSE;
        char *append_string;
        
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
        
        
        char *var_value=Code_Generation_2_Javascript(sl, var_value_tree);
        
        append_string=append(append_string, var_value);
        
        append_string=append(append_string,";");

        //SL_addString(sl, append_string);
        
                
        return append_string;
        
    }
    if (term(tree.name, "func_value")) {
        char *append_string="function(";
        
        char *param_str=Code_Generation_2_Javascript(sl, tree.node_list->next->node);
        
        append_string=append(append_string, param_str);
        append_string=append(append_string, "){\n");
        
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
        Node_List *nl=tree.node_list->next->next;
        while (nl->next!=NULL) {
            char *output_str=Code_Generation_2_Javascript(sl, nl->node);
            append_string=append(append_string, append("     ",output_str));
            nl=nl->next;
        }
        
        append_string=append(append_string," }");
        return append_string;
    }
    /*
     (table [1,2,3]
        ( table_expr
            ( key(num 0))
            (num 1)
        )
        ( table_expr
            ( key(num 1))
            (num 2))
        ( table_expr
            ( key(num 2))
            (num 3)
        )
     )
        Convert Walley Table to JS array
    */
    else if (term(tree.token_class, "table")){
        char *append_str="{";
        Node_List *nl=tree.node_list;
        while (nl!=NULL) {
            
            char *temp_str=Code_Generation_2_Javascript(sl, nl->node);
            append_str=append(append_str, temp_str);
            if (nl->next!=NULL) {
                append_str=append(append_str, ",");
            }
            
            nl=nl->next;
        }
        append_str=append(append_str, "}");
        return append_str;
    }
    else if (term(tree.name, "table_expr")){
        TREE key_tree=tree.node_list->node;
        TREE value_tree=tree.node_list->next->node;
        char *left=Code_Generation_2_Javascript(sl, key_tree.node_list->node);
        bool left_is_string=isString(left);
        if (left_is_string==FALSE && stringIsDigit(left)==FALSE) {
            printf("Error.. invalid key %s\n",left);
            exit(0);
        }
        if (left_is_string) {
            left=substr(left, 1, (int)strlen(left)-1);
        }
        
        char *right=Code_Generation_2_Javascript(sl, value_tree);
        
        return append(left, append(":", right));
    }
    
    else if(term(tree.name, "table_value")){
        Node_List *nl=tree.node_list;
        char *var_name=Code_Generation_2_Javascript(sl,nl->node);
        char *append_str=var_name;
        js_isTableValue=TRUE;

        nl=nl->next;
        while (nl!=NULL) {
            TREE key_tree=nl->node;
            char *key_str=Code_Generation_2_Javascript(sl, key_tree);
            /* change .length() to ["length"]()
            if (term(key_tree.name,"func")) {
                append_str=append(append_str,".");
            }
             printf("key_str %s\n",key_str);
            */
            
            append_str=append(append_str, key_str);

            
            nl=nl->next;
        }
        
        js_isTableValue=FALSE;
        return append_str;
        

    }
    else if (term(tree.name, "key")){
        if (term(tree.node_list->node.name,"slice")) {
            
            char *append_str=".slice(";
            
            Node_List *nl=tree.node_list->node.node_list;
            TREE left=nl->node;
            TREE right=nl->next->node;
            
            char *left_str=Code_Generation_2_Javascript(sl, left);
            append_str=append(append_str, left_str);
            
            // does not append
            if (term(right.name,"its_length")) {
                
            }
            else{
                append_str=append(append_str, ",");
                char *right_str=Code_Generation_2_Javascript(sl, right);
                append_str=append(append_str, right_str);
            }
            append_str=append(append_str, ")");
            
            return append_str;
        }
        else{
            TREE key_tree=tree.node_list->node;
            return append("[", append(Code_Generation_2_Javascript(sl, key_tree), "]"));
        }
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
        bool used_to_be_js_isTableValue=FALSE;
        char *append_str; //=tree.node_list->node.name;
        if (js_isTableValue==FALSE) {
            // i changed parser for func on 05/20/2013
            char *func_name_string=Code_Generation_2_Javascript(sl,tree.node_list->node.node_list->node);
            char *func_name= substr(func_name_string,1,(int)strlen(func_name_string)-1);
            
            append_str=func_name;
            
        }
        else{
            char *func_name=Code_Generation_2_Javascript(sl,tree.node_list->node.node_list->node);
            // add []
            append_str=append("[",append(func_name, "]"));
            
            // solve console.log(a()) -> console["log"](["a"]()) problem
            // change js_isTableValue to FALSE at first and then restore to TRUE
            used_to_be_js_isTableValue=TRUE;
            js_isTableValue=FALSE;
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
        
        
        if (used_to_be_js_isTableValue) {
            js_isTableValue=TRUE;
        }
        
        return append_str;
    }
    else if (term(tree.name, "value")){
        Node_List *nl=tree.node_list;
        return Code_Generation_2_Javascript(sl, nl->node);
    }
    // and( +(num 3)(num 4))(id a)
    else if (term(tree.name, "and")||term(tree.name, "or")){
        char *left_str=Code_Generation_2_Javascript(sl, tree.node_list->node);
        char *right_str=Code_Generation_2_Javascript(sl, tree.node_list->next->node);
        char *judge_sign="&&";
        if (term(tree.name, "or")) {
            judge_sign="||";
        }
        return append(left_str, append(judge_sign, right_str));
    }
    else if (term(tree.name,"params")){
        char *append_string="";
        Node_List *nl=tree.node_list;
        while (nl!=NULL) {
            
            if (term(nl->node.name, "=")) {
                printf("Does not support = in params now\n");
                exit(0);
            }
            
            char *need_to_be_appended=Code_Generation_2_Javascript(sl, nl->node);
            
            // none params
            if(term(need_to_be_appended, "null")){
                nl=nl->next;
                continue;
            }
            
            append_string=append(append_string, need_to_be_appended);

            if (nl->next!=NULL) {
                append_string=append(append_string, ",");
            }
            nl=nl->next;
        }
        return append_string;
    }
    else if (term(tree.name, "end")){
        return "}\n";
    }
    
    else if (term(tree.token_class,"id")){
        // continue
        if (term(tree.name, "continue")) {
            SL_addString(sl, "continue;");
            return "";
        }
        
        if (term(tree.name, "break")) {
            SL_addString(sl, "break;");
            return "";
        }
        
        
        // change 'none' to 'null'
        if (term(tree.name, "none")) {
            return "null";
        }
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
            //char *append_str=left_str;
            if (left_need_bracket) {
                left_str=append("(",append(left_str, ")"));
            }
                
            
            if(right_need_bracket){
                right_str=append("(", append(right_str, ")"));
            }
                        
            // change ^ to Math.pow()
            if (term(tree.name, "^")) {
                
                char *append_str=append("Math.pow(", append(append(left_str, append(",", right_str)), ")"));
                return append_str;
            }
            else{
                char *append_str=append(left_str, append(tree.name, right_str));
                return append_str;
            }
            
        }
        else{
            if (term(tree.name, "^")) {
              return  append("Math.pow(", append(append(left_str, append(",", right_str)), ")"));
            }
            else{
                char *append_str=left_str;
                append_str=append(append_str, tree.name);
                append_str=append(append_str, right_str);
                return append_str;
            }
        }
    }
    else if (term(tree.name, "expr")){
        return Code_Generation_2_Javascript(sl, tree.node_list->node);
    }
    else if (term(tree.name, "return")){
        char *append_str="return ";
        Node_List *nl=tree.node_list;
        append_str=append(append_str, Code_Generation_2_Javascript(sl, nl->node));
        append_str=append(append_str, ";\n");
        // SL_addString(sl, append_str);
        return append_str;
        
    }
    else{
        printf("Code Generation Error..\n");
        exit(0);
    }
}



























