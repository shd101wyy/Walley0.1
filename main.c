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
   
    if (argc==2) {
        char *file_name=argv[1];
        VM_Run_File(file_name);
    }

    if (argc==3) {
        if (strcmp(argv[1],"lex")==0) {
            char *to_analyze_str=argv[2];
            struct TL *tl=Walley_Lexical_Analyzie(to_analyze_str);
            TL_print(tl);
        }
        
    }
    // insert code here...
    return 0;
}

