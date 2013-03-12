
#include "walley_parser.h"
struct Stack{
    char *value;
};


// eg var_name :a  address :0
//    then found value of a at address 0
struct Var_Table{
    char *var_name;
    int address;
};


// #3  means const value
// 3   means address 3
// r1  means register 1

enum OPCODE{
    ADD,      // 00 ADD arg0 arg1 arg2 ; +
    SUB,      // 01 SUB arg0 arg1 arg2 ; -
    MUL,      // 02 MUL arg0 arg1 arg2 ; *
    DIV,      // 03 DIV arg0 arg1 arg2 ; /
    MOD,      // 04 MOD arg0 arg1 arg2 ; %
    POW,      // 05 POW arg0 arg1 arg2 ; ^
    LOADG,    // 06 LOADG dest from   ; load global value
    LOADL,    // 07 LOADL dest from   ; load local value
    PRINT,    // 08 PRINT arg0         ;
    HALT,     // 09 HALT               ;
    SETG,     // 10 SETG dest value    ; set global value
    SETL,     // 11 SETL dest value    ; set local value
    MOVE,     // 12 MOVE dest from     ; move value
    JMP       // 13 JMP steps          ; jump steps.. eg jump -2   --> jump back 2 steps
};

enum OPCODE OPCODE_getFromString(char *input_str){
    if (strcmp(input_str,"ADD")==0) {
        return ADD;
    }
    else if (strcmp(input_str,"SUB")==0) {
        return SUB;
    }
    else if (strcmp(input_str,"MUL")==0) {
        return MUL;
    }
    else if (strcmp(input_str,"DIV")==0) {
        return DIV;
    }
    else if (strcmp(input_str,"MOD")==0) {
        return MOD;
    }
    else if (strcmp(input_str,"POW")==0) {
        return POW;
    }
    else if (strcmp(input_str,"LOADG")==0) {
        return LOADG;
    }
    else if (strcmp(input_str,"LOADL")==0) {
        return LOADL;
    }
    else if (strcmp(input_str,"PRINT")==0) {
        return PRINT;
    }
    else if (strcmp(input_str,"HALT")==0) {
        return HALT;
    }
    else if (strcmp(input_str,"SETG")==0) {
        return SETG;
    }
    else if (strcmp(input_str,"SETL")==0) {
        return SETL;
    }
    else if (strcmp(input_str,"MOVE")==0) {
        return MOVE;
    }
    else if (strcmp(input_str,"JMP")==0) {
        return JMP;
    }
    else{
        printf("Error.. wrong opcode\n");
        exit(0);
    }
}

typedef struct OPERATION{
    enum OPCODE opcode;
    char *arg0;
    char *arg1;
    char *arg2;
}OPERATION;

typedef struct REGISTER{
    char *value;
}REGISTER;


#define MAX_STACK 256
#define MAX_LOCAL_VALUE 60
#define REGISTER_NUM 4
int PC=0;
int GLOBAL_COUNT=0;
int LOCAL_COUNT=255;
struct Stack stack[MAX_STACK];
REGISTER register_w[REGISTER_NUM];

void REGISTER_Print(){
    int i=0;
    printf("REGISTER\n");
    printf("========\n");
    for (; i<REGISTER_NUM; i++) {
        printf("[%d] --> %s\n",i,register_w[i].value);
    }
    printf("\n\n");
}

void STACK_Print(){
    int i=MAX_STACK-1;
    printf("STACK\n");
    printf("========\n");
    for (; i>=0; i--) {
        if (stack[i].value==NULL) {
            continue;
        }
        printf("[%d] --> %s\n",i,stack[i].value);
    }
    printf("\n\n");
    
}


// #100 return 100
char *const_value(char *input_str){
    int length=(int)strlen(input_str);
    char *return_value=(char*)malloc(sizeof(char)*length);
    int i=0;
    for (; i<length-1; i++) {
        return_value[i]=input_str[i+1];
    }
    return_value[i]=0;
    return return_value;
}

// r1 return 1
int register_index(char *input_str){
    if (input_str[0]!='r') {
        printf("Error..it is not register\n");
        exit(0);
    }
    int length=(int)strlen(input_str);
    char *return_value=(char*)malloc(sizeof(char)*length);
    int i=0;
    for (; i<length-1; i++) {
        return_value[i]=input_str[i+1];
    }
    return_value[i]=0;
    int return_int=atoi(return_value);
    if (return_int>=REGISTER_NUM) {
        printf("Error..unavailable register %d\n",return_int);
        exit(0);
    }
    return return_int;
}

// #100 return 100
// r1 return value in r1
char *load_value(char *input_str){
    if (input_str[0]=='#') {
        return const_value(input_str);
    }
    else if (input_str[0]=='r'){
        return register_w[register_index(input_str)].value;
    }
    else
        return stack[atoi(input_str)].value;
}

char *add(char *num1, char *num2){
    double output=atof(num1)+atof(num2);
    char *output_str = (char*)malloc(sizeof(char)*1000);
    sprintf(output_str,"%f",output);
    return output_str;
}
char *sub(char *num1, char *num2){
    double output=atof(num1)-atof(num2);
    char *output_str = (char*)malloc(sizeof(char)*1000);
    sprintf(output_str,"%f",output);
    return output_str;
}
char *mul(char *num1, char *num2){
    double output=atof(num1)*atof(num2);
    char *output_str = (char*)malloc(sizeof(char)*1000);
    sprintf(output_str,"%f",output);
    return output_str;
}
char *divide(char *num1, char *num2){
    double output=atof(num1)/atof(num2);
    char *output_str = (char*)malloc(sizeof(char)*1000);
    sprintf(output_str,"%f",output);
    return output_str;
}
char *mod(char *num1, char *num2){
    double output=(atoi(num1))%(atoi(num2));
    char *output_str = (char*)malloc(sizeof(char)*1000);
    sprintf(output_str,"%f",output);
    return output_str;
}
char *power(char *num1, char *num2){
    double output=pow(atof(num1),atoi(num2));
    char *output_str = (char*)malloc(sizeof(char)*1000);
    sprintf(output_str,"%f",output);
    return output_str;
}

void VM_RUN_ONE_COMMAND(OPERATION operation){
    char *arg0=NULL;
    char *arg1=NULL;
    char *arg2=NULL;
    int r_index1=-1;
    int r_index2=-1;
    int s_index=-1;
    
    switch (operation.opcode) {
        case LOADG:
            // LOAD r1 #100
            r_index1=register_index(operation.arg0);
            arg1=load_value(operation.arg1);
            register_w[r_index1].value=arg1;
            break;
            
        case MOVE:
            // MOVE r1 r2
            r_index1=register_index(operation.arg0);
            r_index2=register_index(operation.arg1);
            register_w[r_index1].value=register_w[r_index2].value;
            break;
            
            
        case SETG:
            // SETG 0 r1
            s_index=atoi(operation.arg0);
            arg1=load_value(operation.arg1);
            stack[s_index].value=arg1;
            break;
            
            
            // ADD SUB MULT DIV MOD POW only support num now
        case ADD:
            // ADD r0 r0 r1
            printf("%s %s\n",operation.arg2,operation.arg1);
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=register_index(operation.arg0);
            register_w[r_index1].value=add(arg1, arg2);
            break;
            
            
        case SUB:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=register_index(operation.arg0);
            register_w[r_index1].value=sub(arg1, arg2);
            break;
            
            
        case MUL:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=register_index(operation.arg0);
            register_w[r_index1].value=sub(arg1, arg2);
            break;
            
            
        case DIV:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=register_index(operation.arg0);
            register_w[r_index1].value=divide(arg1, arg2);
            break;
            
            
        case MOD:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=register_index(operation.arg0);
            register_w[r_index1].value=mod(arg1, arg2);
            break;
            
            
        case POW:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=register_index(operation.arg0);
            register_w[r_index1].value=power(arg1, arg2);
            break;
            
            
            
        default:
            break;
    }
}

void VM_Run_File(char *file_name){
    int length=(int)strlen(file_name);
    if (file_name[length-1]!='m'||file_name[length-2]!='v'||file_name[length-3]!='.') {
        printf("File Format Wrong...required  a.vm like file\n");
        exit(0);
    }
    FILE *fp;
    char arr[10000]="";
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    }
    
    while ((fgets(arr, 10000, fp)) != NULL) {
        length=(int)strlen(arr);
        char enum_name[10]="";
        char arg0[100]="";
        char arg1[100]="";
        char arg2[100]="";
        int i=0;
        while (arr[i]!=' '&&i<length) {
            enum_name[i]=arr[i];
            i++;
        }
        i=i+1;
        int count=0;
        while (arr[i]!=' '&&i<length) {
            arg0[count]=arr[i];
            count++;
            i++;
        }
        i=i+1;
        count=0;
        while (arr[i]!=' '&&i<length) {
            arg1[count]=arr[i];
            count++;
            i++;
        }
        i=i+1;
        count=0;
        while (arr[i]!=' '&&i<length) {
            arg2[count]=arr[i];
            count++;
            i++;
        }
        enum OPCODE opcode=OPCODE_getFromString(enum_name);
        OPERATION operation=(struct OPERATION){opcode,arg0,arg1,arg2};
        printf("|%s| |%s| |%s| |%s|\n",enum_name,arg0,arg1,arg2);
        VM_RUN_ONE_COMMAND(operation);
        
        
    }
}
/*
int main(int argc, char **argv){
    
    struct OPERATION prog[10];
    
    prog[0]=(struct OPERATION){SETG,"0","#1200"};
    prog[1]=(struct OPERATION){LOADG,"r1","0"};
    prog[2]=(struct OPERATION){MOVE,"r0","r1"};
    prog[3]=(struct OPERATION){ADD,"r0","r0","r1"};
    
    printf("%s %s %s\n",prog[0].arg0,prog[0].arg1,prog[0].arg2);
    printf("%s %s %s\n",prog[1].arg0,prog[1].arg1,prog[1].arg2);
    printf("%s %s %s\n",prog[2].arg0,prog[2].arg1,prog[2].arg2);
    printf("%s %s %s\n",prog[3].arg0,prog[3].arg1,prog[3].arg2);
    
    
    VM_RUN_ONE_COMMAND(prog[0]);
    VM_RUN_ONE_COMMAND(prog[1]);
    VM_RUN_ONE_COMMAND(prog[2]);
    VM_RUN_ONE_COMMAND(prog[3]);
    
    
    REGISTER_Print();
    STACK_Print();
    
    if (argc==2) {
        char *file_name=argv[1];
        VM_Run_File(file_name);
    }
    
    //VM_RUN_ONE_COMMAND(prog[3]);
    
    
    //prog[1]=(struct OPERATION){SETG,"0","r1"};
    
    
	return 0;
}



*/






















