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
    
    bool begin=FALSE;
    while (1) {
        
        printf("\n>>> ");
        char *input_str=(char*)malloc(sizeof(char)*1000);
        gets(input_str);
        if (strcmp(input_str, "exit()") == 0)
            break;
        
        Token_List *tl;
        tl=Walley_Lexical_Analyzie(input_str);
        
        
        // now complete
        if (begin==TRUE && COUNT_THEN_END==0) {
            begin=FALSE;
            
            char *saved_string=SL_toString(saved_str_list);
                      
            // reinitialize saved_str_list
            SL_initSL(&saved_str_list);
            
            // append saved_string + input_str
            int malloc_length=(int)strlen(saved_string)+(int)strlen(input_str);
            char *input_str2=(char*)malloc(sizeof(char)*(1+malloc_length));
            strcpy(input_str2, saved_string);
            strcat(input_str2, input_str);
            input_str2[malloc_length]=0;
            
            
            // reset INCOMPLETE_STATEMENT
            INCOMPLETE_STATEMENT=FALSE;
            
            // regenerate tl
            tl=Walley_Lexical_Analyzie(input_str2);
            
        }
        
        // incomplete statements
        if (COUNT_THEN_END!=0 || INCOMPLETE_STATEMENT) {
            begin=TRUE;
            
            // append space after input_str
            int malloc_length=(int)strlen(input_str);
            char *input_str2=(char*)malloc(sizeof(char)*(2+malloc_length));
            strcpy(input_str2, input_str);
            strcat(input_str2," ");
            input_str2[1+malloc_length]=0;
            
            SL_addString(&saved_str_list, input_str2);
            continue;
        }
        
        // empty tl
        if (tl->current_token.TOKEN_STRING==NULL) {
            continue;
        }
                
        TREE syntax_tree=parser(tl);
        
        
        // incomplete statements
        if (COUNT_THEN_END!=0 || INCOMPLETE_STATEMENT) {
            //printf("COUNT_THEN_END-->%d incomplete \n",COUNT_THEN_END);
            begin=TRUE;
            
            // append space after input_str
            int malloc_length=(int)strlen(input_str);
            char *input_str2=(char*)malloc(sizeof(char)*(2+malloc_length));
            strcpy(input_str2, input_str);
            strcat(input_str2," ");
            input_str2[1+malloc_length]=0;
            
            SL_addString(&saved_str_list, input_str2);
            continue;
        }
        
              
        
        Str_List *output_sl;
        SL_initSL(&output_sl);
        
        
        char *output_str=Code_Generation_2_Javascript(&output_sl, syntax_tree);
        
        if (term(output_str, "")==FALSE) {
            if (output_str[(int)strlen(output_str)-1]!=';') {
                output_str=append(output_str, ";");                
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
    char *preload_js_str="String.prototype.find=function(e,t){if(typeof t==\"undefined\"){t=0}return this.indexOf(e,t)};String.prototype.tolower=function(){return this.toLowerCase()};String.prototype.toupper=function(){return this.toUpperCase()};String.prototype.reverse=function(){return this.split("").reverse().join("")};Math[\"cot\"]=function(e){return 1/Math.tan(e)};Math[\"sec\"]=function(e){return 1/Math.cos(e)};Math[\"csc\"]=function(e){return 1/Math.sin(e)};Array.prototype.append=function(e){this.push(e)};Array.prototype.insert=function(e,t){if(typeof t==\"undefined\"){return this.push(e)}this.splice(e,0,t)};Array.prototype.remove=function(e){this.splice(e,1)}";
    SL_addString(&output_sl, preload_js_str);
    
    
    
    
    while (sl_in_file!=NULL) {
        
        if ((int)strlen(trim(sl_in_file->string_content))==0) {
            sl_in_file=sl_in_file->next;
            continue;
        }
        
        Token_List *tl=Walley_Lexical_Analyzie(sl_in_file->string_content);
        TREE tree=parser(tl);
        
        
        if (INCOMPLETE_STATEMENT) {
            char *temp_string="";
            while (INCOMPLETE_STATEMENT) {
                
                COUNT_THEN_END=0;
                temp_string=append(temp_string, sl_in_file->string_content);
                temp_string=append(temp_string, " ");
                Token_List *temp_tl=Walley_Lexical_Analyzie(temp_string);
                
                if (COUNT_THEN_END==0) {
                    INCOMPLETE_STATEMENT=FALSE;
                    tree=parser(temp_tl);
                    
                    if (INCOMPLETE_STATEMENT==FALSE) {
                        break;
                    }
                    
                }
                
                
                sl_in_file=sl_in_file->next;
                
            }
        }
        
        
        char *output_str=Code_Generation_2_Javascript(&output_sl, tree);
        
        if (term(output_str, "")==FALSE) {
            output_str=append(output_str, ";");
            SL_addString(&output_sl, output_str);
        }
        
        sl_in_file=sl_in_file->next;
    }
    
    return output_sl;
}

