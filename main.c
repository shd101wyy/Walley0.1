//
//  main.c
//  Walley0.1
//
//  Created by shd101wyy on 13-3-7.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_code_generation.h"

int main(int argc, char **argv)
{
    // test Code_Generation Function
    char *to_analyze_str="x=[1,[2,3],4]";
    struct TL *tl=Walley_Lexical_Analyzie(to_analyze_str);
    TL_print(tl);
    TREE output_tree=parser(tl);
    Var_List *local_var_list;
    VL_init(&local_var_list);
    VL_init(&GLOBAL_VAR_LIST);
    Operation_List *ol;
    OL_init(&ol);
    Code_Generation(output_tree, &ol, &local_var_list);
    OL_print(ol);
    exit(0);
    
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

        
    }
    else
        printf("Command Error\n");
    // insert code here...
    return 0;
}

