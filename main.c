//
//  main.c
//  Walley0.1
//
//  Created by shd101wyy on 13-3-7.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley.h"
void Test(char *input_str){
    char *to_analyze_str=input_str;
    printf("input_str--------> %s\n",input_str);
    struct TL *tl=Walley_Lexical_Analyzie(to_analyze_str);
    TL_print(tl);
    TREE output_tree=parser(tl);
    
    if (NOW_FUNCTION) {
        Code_Generation(output_tree, &(FUNCTION_LIST->current_ol),&(FUNCTION_LIST->next_in_function) ,&LOCAL_OFFSET);
    }
    else{
        Code_Generation(output_tree, &OPERATION_LIST,&FUNCTION_LIST,&GLOBAL_OFFSET);
    }
    
    OPERATION op;
    op.opcode=$;
    op.arg0="===================";
    op.arg1=NULL;
    op.arg2=NULL;
    OL_append(&OPERATION_LIST, op);
    
}
int main(int argc, char **argv)
{
    
    // test Code_Generation Function
    
    Walley_Init();
    
    //Test("a=1");
    //Test("y=2");
    //Test("def add(num1,num2) then");
    //Test("x=3");
    //Test("y=4");
    //Test("end");
    Test("x=1");
    Test("while x<5 then");
    Test("end");
    
    
    
    printf("\n\n@@@@@@@@@@\n");
    FL_print(FUNCTION_LIST);
    printf("============\n\n\n");
    
    OL_print(OPERATION_LIST);
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

