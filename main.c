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
    
  
    //Walley_Init();
    //Walley_Run();
    
    /*
    char *input_str="math.add=def(a,b) then return a+b end";
    Token_List *tl=Walley_Lexical_Analyzie(input_str);
    TREE tree=parser(tl);
    Str_List *sl;
    SL_initSL(&sl);
    
    Code_Generation_2_Javascript(&sl, tree);
    
    SL_print(sl);
    
    exit(0);
    */
    
    
    //Str_List *output_sl=Compile_to_JS("/Users/shd101wyy/Documents/workspace/xcode/Walley0.1/Walley0.1/test.wy");
    
    /*
    // test sentence_seperation
    //"x,y=def (a,b) then return a+b end,12 z=12"
    //"x,y = def () then return 3+4 end,13 z=13"
    char *input_str="x,y=def (a,b) then return a+b end,12 z=12";
    Token_List *tl=Walley_Lexical_Analyzie(input_str);
    printf("===================\n");
    TL_print(tl);
    printf("===================\n");
    parser(tl);
    //sentences_seperation(tl);
    exit(0);
    */
    
    // test Code_Generation Function
    /*
    Walley_Init();
    Test("x=[1,2]");
    
    
    
    
    printf("\n\n@@@@@@@@@@\n");
    FL_print(FUNCTION_LIST);
    printf("============\n\n\n");
    
    OL_print(OPERATION_LIST);
    exit(0);
     */
    
     /*
     VM_init();
     
     char *to_analyze_str="if 3>4 and 4>6:";
     struct TL *tl=Walley_Lexical_Analyzie(to_analyze_str);
     TL_print(tl);
     TREE output_tree=parser(tl);
     Token_List *output_tl=TREE_convertAST(output_tree);
     printf("\nAFTER CONVERTING==========\n");
     TL_print(output_tl);
     
     //Operation_List *ol=CG(output_tl);
     //printf("\nOPERATION LIST============\n");
     //OL_print(ol);
    
    exit(0);
    
    */

    
    if (argc==2) {
        char *file_name=argv[1];
        VM_Run_File(file_name);
    }

    else if (argc==3) {
        if (strcmp(argv[1],"lex")==0) {
            char *to_analyze_str=argv[2];
            struct TL *tl=Walley_Lexical_Analyzie(to_analyze_str);
            TL_print(tl);
        }
        else if (strcmp(argv[1],"parse")==0) {
            char *to_analyze_str=argv[2];
            struct TL *tl=Walley_Lexical_Analyzie(to_analyze_str);
            TL_print(tl);
            parser(tl);
        }
        else if (strcmp(argv[1],"vm")==0) {
            char *file_name=argv[2];
            VM_Run_File(file_name);
        }
        
        // compile to min.js
        else if (strcmp(argv[1], "js_min")==0){
            printf("Begin to compile to javascript file\n");
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
        // compile to js
        else if (strcmp(argv[1], "js")==0){
            printf("Begin to compile to javascript file\n");
            Str_List *output_sl=Compile_to_JS(argv[2]);
            
            int length=(int)strlen(argv[2]);
            char *compile_to_file=argv[2];
            compile_to_file[length-1]='s';
            compile_to_file[length-2]='j';
            
            printf("compile_to_file name %s\n",compile_to_file);
            
            FILE *fp=fopen(compile_to_file, "w");
            while (output_sl!=NULL) {
                
                fputs(output_sl->string_content, fp);
                fputs("\n",fp);
                output_sl=output_sl->next;
            }
            
            fclose(fp);
            
        }

        /*
        else if (strcmp(argv[1],"cg")==0) {
            
            VM_init();
            
            char *to_analyze_str=argv[2];
            struct TL *tl=Walley_Lexical_Analyzie(to_analyze_str);
            TL_print(tl);
            TREE output_tree=parser(tl);
            Token_List *output_tl=TREE_convertAST(output_tree);
            printf("\nAFTER CONVERTING==========\n");
            TL_print(output_tl);
            
            Operation_List *ol=CG(output_tl);
            printf("\nOPERATION LIST============\n");
            OL_print(ol);
        }
         */

        
    }
    else
        printf("Command Error\n");
    // insert code here...
    return 0;
}

