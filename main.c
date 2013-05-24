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
    
   
    if (argc==1) {
        
        /*
        printf("Walley Language version 0.0.1.567\n");
        Str_List *sl=file_getStringList("./introduction");
        while (sl!=NULL) {
            printf("%s\n",sl->string_content);
            sl=sl->next;
        }
        printf("\n\");
        */
        Walley_Run();
    
              
    }
    else if (argc==3){
        if (term(argv[1], "compile")) {
            printf("Begin to compile Walley Language file to JS file\n");
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

