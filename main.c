//
//  main.c
//  Walley0.1
//
//  Created by shd101wyy on 13-3-7.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley.h"

int main(int argc, char **argv)
{
    
    Compile_to_JS("/Users/shd101wyy/Documents/workspace/xcode/Walley0.1/Walley0.1/walley.wy");
    printf("\n\n!!!===== SUCCESS =====\n");
    exit(0);
    
    /*
    Token_List *tl=Walley_Lexical_Analyzie("local i=0 local x=2" );
    TL_print(tl);
    
    TREE tree;
    tree=parser(tl);
    
    Str_List *sl;
    SL_initSL(&sl);
    char *output=Code_Generation_2_Javascript(&sl, tree);
    printf("\n\n%s\n",output);
    SL_print(sl);
    
    exit(0);
    */
   
    if (argc==1) {
        
        /*
         */
        Walley_Run();
              
    }
    else if(argc==2){
        if (term(argv[1], "help")) {
            printf("Walley Language version 0.0.1.567\n");
            Str_List *sl=file_getStringList("./introduction");
            while (sl!=NULL) {
                printf("%s\n",sl->string_content);
                sl=sl->next;
            }
            printf("\n");

        }
        else{
            printf("Command Error\n");
            exit(0);
        }
    }
    else if (argc==3){
        if (term(argv[1], "compile")) {
            printf("Begin to compile Walley Language file to JS file\n");
            Str_List *output_sl=Compile_to_JS(argv[2]);
            
            int length=(int)strlen(argv[2]);
            char *compile_to_file=argv[2];
            compile_to_file[length-1]='s';
            compile_to_file[length-2]='j';
            
            printf("compile_to_file name %s\n",compile_to_file);
            
            FILE *fp=fopen(compile_to_file, "w");
            while (output_sl!=NULL) {
                
                fputs(output_sl->string_content, fp);
                output_sl=output_sl->next;
            }
            
            fclose(fp);
            
        }
        else if (term(argv[1], "compile_min")){
            printf("Begin to compile Walley Language file to JS file\n");
            Str_List *output_sl=Compile_to_JS(argv[2]);
            
            int length=(int)strlen(argv[2]);
            char *compile_to_file=argv[2];
            compile_to_file[length-1]='s';
            compile_to_file[length-2]='j';
            
            printf("compile_to_file name %s\n",compile_to_file);
            
            char *write_to_file=JS_min(output_sl);
            
            FILE *fp=fopen(compile_to_file, "w");
                
            fputs(write_to_file, fp);
            
            fclose(fp);
        }
        else{
            printf("Command Error\n");
            exit(0);
        }
    }
    else
        printf("Command Error\n");
    // insert code here...
    return 0;
}

