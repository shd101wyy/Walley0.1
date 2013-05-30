//
//  walley.h
//  Walley0.1
//
//  Created by shd101wyy on 13-4-6.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//
#include "walley_cg_js.h"

// run script in cmd
void Walley_Run(){
    
    // save incomplete statements
    Str_List *saved_str_list;
    SL_initSL(&saved_str_list);
    
    while (1) {
        
        printf("\n>>> ");
        char *input_str=(char*)malloc(sizeof(char)*1000);
        gets(input_str);
        if (strcmp(input_str, "exit()") == 0)
            break;
        
        Token_List *tl;
        tl=Walley_Lexical_Analyzie(input_str);
        
        TREE tree;
        
        
        tree=parser(tl);
        

        
        if (INCOMPLETE_STATEMENT) {
            char *temp_string=input_str;
            while (INCOMPLETE_STATEMENT) {
                printf("\n>>> ");
                char *input_str=(char*)malloc(sizeof(char)*1000);
                gets(input_str);
                
                INCOMPLETE_STATEMENT=FALSE;
                
                temp_string=append(temp_string, input_str);
                temp_string=append(temp_string, " ");
                Token_List *temp_tl=Walley_Lexical_Analyzie(temp_string);

                tree=parser(temp_tl);
                
            }
        }

        
        
        Str_List *output_sl;
        SL_initSL(&output_sl);
        
        
        char *output_str=Code_Generation_2_Javascript(&output_sl, tree);
        
        
        if (term(output_str, "")==FALSE) {
            if (output_str[(int)strlen(output_str)-1]!=';' && term(substr(output_str, (int)strlen(output_str)-2, (int)strlen(output_str)), ";\n")==FALSE) {
                output_str=append(output_str, ";\n");
            }
            SL_addString(&output_sl, output_str);
        }
        printf("\n");
        SL_print(output_sl);
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
    
    // this string is from prototype.js in walley folder
    char *preload_js_str="none=null;String.prototype.find=function(e,t){if(typeof t==\"undefined\"){t=0}return this.indexOf(e,t)};String.prototype.tolower=function(){return this.toLowerCase()};String.prototype.toupper=function(){return this.toUpperCase()};String.prototype.reverse=function(){return this.split("").reverse().join("")};Math[\"cot\"]=function(e){return 1/Math.tan(e)};Math[\"sec\"]=function(e){return 1/Math.cos(e)};Math[\"csc\"]=function(e){return 1/Math.sin(e)};Object.prototype.slice=function(e,t){var n={};var r=0;for(var i=e;i<t;i++){n[r]=this[i];r++}return n};Object.prototype.append=function(e){var t=\"-1\";for(var n in this){if(!isNaN(n)){if(n>t){t=n}}}if(t!=\"-1\"){t=parseInt(t)+1}else{t=\"0\"}this[t]=e}\n";
    SL_addString(&output_sl, preload_js_str);
    
    
    
    
    while (sl_in_file!=NULL) {
        char *input_str=sl_in_file->string_content;
        
        if ((int)strlen(trim(sl_in_file->string_content))==0) {
            sl_in_file=sl_in_file->next;
            continue;
        }
        
        Token_List *tl=Walley_Lexical_Analyzie(sl_in_file->string_content);
       
        TREE tree;

        tree=parser(tl);
        

        printf("\n\n-----> |%s| %d\n",sl_in_file->string_content,INCOMPLETE_STATEMENT);
        
        
        if (INCOMPLETE_STATEMENT) {
            char *temp_string=sl_in_file->string_content;
            while (INCOMPLETE_STATEMENT) {
                sl_in_file=sl_in_file->next;
                
                
                if (sl_in_file==NULL) {
                    printf("Error.. Incomplete statements %s\n",temp_string);
                    exit(0);
                }
                
                printf("\nINCOMPLETE---> %s\n",sl_in_file->string_content);
                
                INCOMPLETE_STATEMENT=FALSE;
                
                temp_string=append(temp_string, sl_in_file->string_content);
                temp_string=append(temp_string, " \n ");
                
                input_str=temp_string;
                
                                
                Token_List *temp_tl=Walley_Lexical_Analyzie(temp_string);
                printf("\n=====\n");
                TL_print(temp_tl);
                tree=parser(temp_tl);                
            }
        }
        
        
        
        char *output_str=Code_Generation_2_Javascript(&output_sl, tree);
        

        
        if (term(output_str, "")==FALSE) {
            if (output_str[(int)strlen(output_str)-1]!=';' && term(substr(output_str, (int)strlen(output_str)-2, (int)strlen(output_str)), ";\n")==FALSE) {
                output_str=append(output_str, ";\n");
            }
            SL_addString(&output_sl, output_str);
        }
        

        
        sl_in_file=sl_in_file->next;
    }
    
    return output_sl;
}

