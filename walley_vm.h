
#include "walley_parser.h"
struct Stack{
    char *value;
};

/*
 SETG 0 #1
 PRINT 0
 LT 0 #10
 JMP 6
 LOADG r0 0
 ADD r0 r0 #1
 SETG 0 r0
 PRINT 0
 JMP -6
 PRINT "FINISH LOOP!!!"
 HALT
 
 
 i=0
 while i<10:
     i=i+1
 print "Finish Loop"
 */

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
    JMP,      // 13 JMP steps          ; jump steps.. eg jump -2   --> jump back 2 steps
    $,        // 14 annotation 
    EQ,       // 15 EQ arg0 arg1  ; if arg0==arg1 continue next next sentence, else run next sentence; == EQUAL
    /*
     eg:
     EQ #12 #12
     JMP -2        // this sentence will not be run because 12==12
     PRINT "EQUAL" // directly run this sentence after EQ
     */
    LT,       // 16 LT arg0 arg1  ; if arg0<arg1  ...                   , else ...           ; < less than
    LE,       // 17 LE arg0 arg1  ; if arg0<=arg2 ...                   , else ...           ; <= less than or equal
    
};
char *OPCODE_getFromOpcode(enum OPCODE opcode){
    switch (opcode) {
        case ADD:
            return "ADD";
            break;
        case SUB:
            return "SUB";
            break;
        case MUL:
            return "MUL";
            break;
        case DIV:
            return "DIV";
            break;
        case MOD:
            return "MOD";
            break;
        case POW:
            return "POW";
            break;
        case LOADG:
            return "LOADG";
            break;
        case LOADL:
            return "LOADL";
            break;
        case PRINT:
            return "PRINT";
            break;
        case HALT:
            return "HALT";
            break;
        case SETG:
            return "SETG";
            break;
        case SETL:
            return "SETL";
            break;
        case MOVE:
            return "MOVE";
            break;
        case JMP:
            return "JMP";
            break;
        case $:
            return "$";
            break;
        case EQ:
            return "EQ";
            break;
        case LT:
            return "LT";
            break;
        case LE:
            return "LE";
            break;
        default:
            break;
    }
}

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
    else if (strcmp(input_str, "$")==0){
        return $;
    }
    else if (strcmp(input_str, "EQ")==0){
        return EQ;
    }
    else if (strcmp(input_str, "LT")==0){
        return LT;
    }
    else if (strcmp(input_str, "LE")==0){
        return LE;
    }
    else{
        printf("Error.. wrong opcode %s\n",input_str);
        exit(0);
    }
}

typedef struct OPERATION{
    enum OPCODE opcode;
    char *arg0;
    char *arg1;
    char *arg2;
}OPERATION;

void OPERATION_print(OPERATION operation){
    printf("%s %s %s %s\n",OPCODE_getFromOpcode(operation.opcode),operation.arg0,operation.arg1,operation.arg2);
}

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


struct OL{
    OPERATION operation;
    struct OL *next;
    struct OL *ahead;
};

void OL_init(struct OL **ol){
    (*ol)=(struct OL*)malloc(sizeof(struct OL)*1);
    (*ol)->operation.opcode=$;
    (*ol)->next=NULL;
    (*ol)->ahead=NULL;
}
void OL_print(struct OL *ol){
    while (ol->next!=NULL) {
        printf("|%s| |%s| |%s| |%s|\n",OPCODE_getFromOpcode(ol->operation.opcode),ol->operation.arg0,ol->operation.arg1,ol->operation.arg2);
        ol=ol->next;
    }
    printf("|%s| |%s| |%s| |%s|\n",OPCODE_getFromOpcode(ol->operation.opcode),ol->operation.arg0,ol->operation.arg1,ol->operation.arg2);
    
}

void OL_append(struct OL **ol, OPERATION operation){
    
    struct OL *temp_ol;
    temp_ol=(struct OL*)malloc(sizeof(struct OL)*1);
    temp_ol->operation=operation;
    temp_ol->next=NULL;
    temp_ol->ahead=NULL;
    
    struct OL **current_ol=&(*ol);
    while ((*current_ol)->next!=NULL) {
        current_ol=&((*current_ol)->next);
    }
    temp_ol->ahead=(*current_ol);
    (*current_ol)->next=temp_ol;
    //(*current_ol)->next->ahead=(*current_ol);
    
}

int OL_length(struct OL *ol){
    int length=0;
    while (ol->next!=NULL) {
        length++;
        ol=ol->next;
    }
    length++;
    return length;
}



void VM_RUN_ONE_COMMAND(OPERATION operation){
    //printf("=====\n");
    //OPERATION_print(operation);
    char *arg0=NULL;
    char *arg1=NULL;
    char *arg2=NULL;
    int r_index1=-1;
    int r_index2=-1;
    int s_index=-1;
    char *print_str=NULL;
    char *print_str2=NULL;
    
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
            //printf("%s %s\n",operation.arg2,operation.arg1);
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            //printf("%s %s\n",arg2,arg1);

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
        case PRINT:
            print_str=operation.arg0;
            if (print_str[0]=='"') {
                int length=(int)strlen(print_str);
                print_str2=(char*)malloc(sizeof(char)*(length-1));
                strcpy(print_str2, "");
                int i=0;
                for (; i<length-2; i++) {
                    print_str2[i]=print_str[i+1];
                }
                print_str2[i]=0;
            }
            else{
                print_str2=load_value(print_str);
            }
            printf("%s",print_str2);
            break;
        case HALT:
            exit(0);
            break;
        case $:
            break;

            
        default:
            break;
    }
}

bool pass(char *value1, char *value2, enum OPCODE opcode){
    bool pass=FALSE;
    if (stringIsDigit(value1)&&stringIsDigit(value2)) {
        double v1=atof(value1);
        double v2=atof(value2);
        if (opcode==EQ) {
            if (v1==v2) {
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
        else if (opcode==LT){
            if (v1<v2) {
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
        //LE
        else{
            if (v1<=v2) {
                return TRUE;
            }
            else
                return FALSE;
        }
    }
    else{
        if (opcode==EQ) {
            if (strcmp(value1, value2)==0) {
                return TRUE;
            }
            else
                return FALSE;
        }
        else if(opcode==LT){
            if (strcmp(value1, value2)<0) {
                return TRUE;
            }
            else
                return FALSE;
        }
        //LE
        else{
            if (strcmp(value1, value2)<=0) {
                return TRUE;
            }
            else
                return FALSE;
        }
    }
    
}

void VM_Run_Command(struct OL *ol){
    while (ol->next!=NULL) {
        if (ol->operation.opcode==JMP) {
            int jump_step=atoi(ol->operation.arg0);
            if (jump_step==0) {
                printf("Error.. Can not JUMP 0\n");
                exit(0);
            }
            else if (jump_step<0){
                jump_step=-jump_step;
                int i=0;
                for (; i<jump_step; i++) {
                    ol=ol->ahead;                    
                    if (ol==NULL) {
                        printf("Error.. Jump back too much\n");
                        exit(0);
                    }
                }
            }
            // jump_step >0
            else{
                int i=0;
                for (; i<jump_step; i++) {
                    ol=ol->next;
                    if (ol==NULL) {
                        printf("Error.. Jump ahead too much\n");
                        exit(0);
                    }
                }
            }
            VM_Run_Command(ol);
            return;
            //ol=ol->next;
        }
        else if (ol->operation.opcode==EQ) {
            // EQ #12 #12
            char *value1=load_value(ol->operation.arg0);
            char *value2=load_value(ol->operation.arg1);
            bool can_pass=pass(value1, value2, ol->operation.opcode);
            // run next next sentence
            if (can_pass) {
                ol=ol->next->next;
                VM_Run_Command(ol);
                return;
            }
            // run next sentence
            else{
                ol=ol->next;
                VM_Run_Command(ol);
                return;
            }
        }
        else if (ol->operation.opcode==LT) {
            // EQ #12 #12
            char *value1=load_value(ol->operation.arg0);
            char *value2=load_value(ol->operation.arg1);
            bool can_pass=pass(value1, value2, ol->operation.opcode);
            // run next next sentence
            if (can_pass) {
                ol=ol->next->next;
                VM_Run_Command(ol);
                return;

            }
            // run next sentence
            else{
                ol=ol->next;
                VM_Run_Command(ol);
                return;

            }
        }
        else if (ol->operation.opcode==LE) {
            // EQ #12 #12
            char *value1=load_value(ol->operation.arg0);
            char *value2=load_value(ol->operation.arg1);
            bool can_pass=pass(value1, value2, ol->operation.opcode);
            // run next next sentence
            if (can_pass) {
                ol=ol->next->next;
                VM_Run_Command(ol);
                return;

            }
            // run next sentence
            else{
                ol=ol->next;
                VM_Run_Command(ol);
                return;
            }
        }
        else{
            VM_RUN_ONE_COMMAND(ol->operation);
            ol=ol->next;
        }
    }
    if (ol->operation.opcode==JMP) {
        int jump_step=atoi(ol->operation.arg0);
        if (jump_step==0) {
            printf("Error.. Can not JUMP 0\n");
            exit(0);
        }
        else if (jump_step<0){
            jump_step=-jump_step;
            int i=0;
            for (; i<jump_step; i++) {
                ol=ol->ahead;
                if (ol==NULL) {
                    printf("Error.. Jump too much\n");
                    exit(0);
                }
            }
        }
        // jump_step >0
        else{
            printf("Error.. NO operation ahead\n");
            exit(0);
        }
        VM_Run_Command(ol);
        return;
    }
    
    
    else{
        VM_RUN_ONE_COMMAND(ol->operation);
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
    
    int lines=0;
    
    
    struct OL *ol;
    OL_init(&ol);
    
    while ((fgets(arr, 10000, fp)) != NULL) {
        length=(int)strlen(arr);
        char enum_name[10]="";
        char *arg0=(char*)malloc(sizeof(char)*100);
        char *arg1=(char*)malloc(sizeof(char)*100);
        char *arg2=(char*)malloc(sizeof(char)*100);
        
        if (arr[length-1]=='\n') {
            arr[length-1]=' ';
        }
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
        if ((int)strlen(arg0)==0) {
            arg0=NULL;
        }
        if ((int)strlen(arg1)==0) {
            arg1=NULL;
        }
        if ((int)strlen(arg2)==0) {
            arg2=NULL;
        }
        
        enum OPCODE opcode=OPCODE_getFromString(enum_name);
        OPERATION operation=(struct OPERATION){opcode,arg0,arg1,arg2};
        OL_append(&ol, operation);
        lines++;
    }
    
    printf("lines %d\n",lines);
    OL_print(ol);
    VM_Run_Command(ol);

}






















