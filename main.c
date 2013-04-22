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
    
    
    // test sentence_seperation
    //"x,y=def (a,b) then return a+b end,12 z=12"
    //"x,y = def () then return 3+4 end,13 z=13"
    char *input_str="x= def () then return 3+4 end";
    Token_List *tl=Walley_Lexical_Analyzie(input_str);
    printf("===================\n");
    TL_print(tl);
    printf("===================\n");
    parser(tl);
    //sentences_seperation(tl);
    exit(0);
    
    
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

