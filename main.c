//
//  main.c
//  Walley0.1
//
//  Created by shd101wyy on 13-3-7.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_vm.h"

int main(int argc, char **argv)
{
   
    
    
    char *to_analyze_str="3*(2+5)";
    struct TL *tl=Walley_Lexical_Analyzie(to_analyze_str);
    TL_print(tl);
    TREE output_tree=parser(tl);
    
    Token_List *output_tl=TREE_convertAST(output_tree);
    printf("AFTER CONVERTING==========\n");
    TL_print(output_tl);
    exit(0);
    
    
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

        
    }
    else
        printf("Command Error\n");
    // insert code here...
    return 0;
}

