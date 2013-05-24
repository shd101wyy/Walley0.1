
#include "walley_var.h"


struct Stack{
    char *value;
};

/*
 SET 0 #1
 PRINT 0
 LT 0 #10
 JMP 4
 ADD 0 0 #1
 PRINT 0
 JMP -4
 PRINT "FINISH LOOP!!!"
 HALT
 
 
 i=0
 while i<10:
     i=i+1
 print "Finish Loop"
 */



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
    SETG,      // 06 SET dest src       ; SET 0 #100; set const 100 in register address 0; SET 0 1, set value in register 1 to register 0
    SETL,  // 07 SETNONE dest       ; SET none to dest
    //LOADG,    // 06 LOADG dest from   ; load global value
    //LOADL,    // 07 LOADL dest from   ; load local value
    PRINT,    // 08 PRINT arg0         ;
    HALT,     // 09 HALT               ;
    SETCONS,    //10 SETCONS dest value;  SETCONS 0 100, set const value 100 to register 0
    AND,        //11 AND dest src1 src2;  AND 0 0 1.  and the value in 0 and value in 1, then put true or false in 0
    OR,         //12 OR dest src1 src2 ;  OR 0 0 1.   or the value in 0 and value in 1, then put true or false in 0
    //SETG,     // 10 SETG dest value    ; set global value
    //SETL,     // 11 SETL dest value    ; set local value
    //MOVE,     // 12 MOVE dest from     ; move value
    JMP,      // 13 JMP steps          ; jump steps.. eg jump -2   --> jump back 2 steps
    $,        // 14 annotation 
    EQ,       // 15 EQ arg0 arg1  ; if arg0==arg1 continue next next sentence, else run next sentence; == EQUAL
              // 15 EQ dest arg0 arg1  ; if arg0==arg1 save true in dest, else save false in dest

    LT,       // 16 LT dest arg0 arg1  ; if arg0<arg1  ...                   , else ...           ; < less than
    LE,       // 17 LE dest arg0 arg1  ; if arg0<=arg2 ...                   , else ...           ; <= less than or equal
    LABEL,    // 18 LABEL 0       ; save place to jump to
    JMPA,     // 19 JMPA 0        ; jump AHEAD to LABEL 0
    JMPB,     // 20 JMPB 0        ; jump BACK to LABEL 0
    NOT,      // 21 NOT dest      ; NOT 0, change value in 0 to opposite-> true to false, false to true
    CALL,        //22 
    NEWTABLE,  // 24
    TADD,        //25
    ENDTABLE,      //26
    TEST,        //27
    LOADTOG,     // 28
    BEGINLOCAL,   // 29
    FREELOCAL,     //30
    SET,        //31
    RETURN,     // 32
    ENDPARAMS,  // 33
    BEGINFUNC,  // 34 BEGIN a new FUNCTION
    ENDFUNC,     // 35 END A new FUNCTION
    TABLEGET,     // 36
    TABLESTART,      // 37
    TABLEENTER,        // 38
    QUITTABLE,
    GETT,
    SETT,
    SETP,
    ENTERTABLE,
    CREATETABLE,
    ENDCALL
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
        case SETG:
            return "SETG";
            break;
        case SETL:
            return "SETL";
            break;
        case SETCONS:
            return "SETCONS";
            break;
        case PRINT:
            return "PRINT";
            break;
        case HALT:
            return "HALT";
            break;
        case AND:
            return "AND";
            break;
        case OR:
            return "OR";
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
        case LABEL:
            return "LABEL";
            break;
        case JMPA:
            return "JMPA";
            break;
        case JMPB:
            return "JMPB";
            break;
        case NOT:
            return "NOT";
            break;
        case NEWTABLE:
            return "NEWTABLE";
            break;
        case TADD:
            return "TADD";
            break;
        case ENDTABLE:
            return "ENDTABLE";
            break;
        case TEST:
            return "TEST";
            break;
        case LOADTOG:
            return "LOADTOG";
            break;
        case BEGINLOCAL:
            return "BEGINLOCAL";
            break;
        case FREELOCAL:
            return "FREELOCAL";
            break;
        case SET:
            return "SET";
            break;
        case RETURN:
            return "RETURN";
            break;
        case ENDPARAMS:
            return "ENDPARAMS";
            break;
        case CALL:
            return "CALL";
            break;
        case BEGINFUNC:
            return "BEGINFUNC";
            break;
        case ENDFUNC:
            return "ENDFUNC";
            break;
        case TABLEGET:
            return "TABLEGET";
            break;
        case TABLESTART:
            return "TABLESTART";
            break;
        case TABLEENTER:
            return "TABLEENTER";
            break;
        case QUITTABLE:
            return "QUITTABLE";
            break;
        case GETT:
            return "GETT";
            break;
        case SETP:
            return "SETP";
            break;
        case ENTERTABLE:
            return "ENTERTABLE";
            break;
        case SETT:
            return "SETT";
            break;
        case CREATETABLE:
            return "CREATETABLE";
            break;
        case ENDCALL:
            return "ENDCALL";
            break;
        default:
            printf("Error..Unavailable opcode\n");
            exit(0);
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
    else if (strcmp(input_str,"SETG")==0) {
        return SETG;
    }
    else if (strcmp(input_str,"SETL")==0) {
        return SETL;
    }
    else if (strcmp(input_str,"SETCONS")==0) {
        return SETCONS;
    }
    
    else if (strcmp(input_str,"PRINT")==0) {
        return PRINT;
    }
    else if (strcmp(input_str,"HALT")==0) {
        return HALT;
    }
    else if (strcmp(input_str,"AND")==0) {
        return AND;
    }
    else if (strcmp(input_str,"OR")==0) {
        return OR;
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
    else if (strcmp(input_str, "LABEL")==0){
        return LABEL;
    }
    else if (strcmp(input_str, "JMPA")==0){
        return JMPA;
    }
    else if (strcmp(input_str, "JMPB")==0){
        return JMPB;
    }
    else if (strcmp(input_str, "NOT")==0){
        return NOT;
    }
    else if(term(input_str, "NEWTABLE"))
        return NEWTABLE;
    else if(term(input_str, "TADD"))
        return TADD;
    else if (term(input_str, "ENDTABLE"))
        return ENDTABLE;
    else if (term(input_str, "TEST"))
        return TEST;
    else if (term(input_str, "LOADTOG"))
        return LOADTOG;
    
    else if (term(input_str, "BEGINLOCAL"))
        return BEGINLOCAL;
    else if (term(input_str, "FREELOCAL"))
        return FREELOCAL;
    else if (term(input_str, "SET"))
        return SET;
    else if (term(input_str, "RETURN"))
        return RETURN;
    else if (term(input_str, "ENDPARAMS"))
        return ENDPARAMS;
    else if (term(input_str, "CALL"))
        return CALL;
    else if (term(input_str, "BEGINFUNC"))
        return BEGINFUNC;
    else if (term(input_str, "ENDFUNC"))
        return ENDFUNC;
    else if(term(input_str, "TABLEGET"))
        return TABLEGET;
    else if(term(input_str, "TABLESTART"))
        return TABLESTART;
    else if (term(input_str, "TABLEENTER"))
        return TABLEENTER;
    else if (term(input_str, "QUITTABLE"))
        return QUITTABLE;
    else if (term(input_str, "GETT"))
        return GETT;
    else if(term(input_str, "SETP"))
        return SETP;
    else if(term(input_str, "ENTERTABLE"))
        return ENTERTABLE;
    else if(term(input_str, "SETT"))
        return SETT;
    else if (term(input_str, "CREATETABLE"))
        return CREATETABLE;
    else if (term(input_str, "ENDCALL"))
        return ENDCALL;
    else{
        printf("Error.. wrong opcode %s\n",input_str);
        exit(0);
    }
}

struct OPERATION{
    enum OPCODE opcode;
    char *arg0;
    char *arg1;
    char *arg2;
    char *value;        // SETG 0 0 1 ;x        x is value
};

void OPERATION_print(OPERATION operation){
    printf("%s %s %s %s\n",OPCODE_getFromOpcode(operation.opcode),operation.arg0,operation.arg1,operation.arg2);
}

typedef struct REGISTER{
    char *value;
}REGISTER;


#define MAX_STACK 256  // stop using this now 
#define MAX_REGISTERS 256
#define MAX_LOCAL_VALUE 60


int PC=0;
//int GLOBAL_OFFSET=0; i move this value to walley_pre_functions
int LOCAL_COUNT=255;





//Stack stack[MAX_STACK];
REGISTER register_w[MAX_REGISTERS];

void REGISTER_Print(){
    int i=0;
    printf("REGISTER\n");
    printf("========\n");
    for (; i<MAX_REGISTERS; i++) {
        if (register_w[i].value==NULL) {
            continue;
        }
        printf("[%d] --> %s\n",i,register_w[i].value);
    }
    printf("\n\n");
}

/*
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
*/

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

/*
// r1 return 1
int register_index(char *input_str){
    
    // LOADG 0 #100
    // load const 100 to register 0
    if (input_str[0]!='r') {
        //printf("Error..it is not register\n");
        //exit(0);
        return atoi(input_str);
    }
    int length=(int)strlen(input_str);
    char *return_value=(char*)malloc(sizeof(char)*length);
    int i=0;
    for (; i<length-1; i++) {
        return_value[i]=input_str[i+1];
    }
    return_value[i]=0;
    int return_int=atoi(return_value);
    if (return_int>=MAX_REGISTERS) {
        printf("Error..unavailable register %d\n",return_int);
        exit(0);
    }
    return return_int;
}
*/

// #100 return 100
// 1 return value in 1
char *load_value(char *input_str){
    if (input_str[0]=='#') {
        return const_value(input_str);
    }
    /*
    else if (input_str[0]=='r'){
        return register_w[register_index(input_str)].value;
    }
    else
        return stack[atoi(input_str)].value;
     */
    return register_w[atoi(input_str)].value;
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
    int current_index;
};

void OL_init(struct OL **ol){
    (*ol)=(struct OL*)malloc(sizeof(struct OL)*1);
    (*ol)->operation.opcode=$;
    (*ol)->next=NULL;
    (*ol)->ahead=NULL;
    (*ol)->current_index=0;
}
void OL_print(struct OL *ol){
    while (ol!=NULL) {
        printf("%d:|%s| |%s| |%s| |%s|",ol->current_index,OPCODE_getFromOpcode(ol->operation.opcode),ol->operation.arg0,ol->operation.arg1,ol->operation.arg2);
        
        if (ol->operation.value==NULL) {
            printf("\n");
        }
        else{
            printf("      ; %s\n",ol->operation.value);
        }
        
        ol=ol->next;
    }
       
}

OPERATION OL_pop(Operation_List **ol){
    int length=OL_length(*ol);
    int i=0;
    Operation_List **temp_ol=&(*ol);
    Operation_List **current_sl;
    OPERATION return_operation;
    if (length==1) {
        (*ol)->next=NULL;
        return_operation=(*temp_ol)->operation;
        free(*temp_ol);
        OL_init(temp_ol);
        return return_operation;
    }
    for (i=1; i<length; i++) {
        current_sl=&(*temp_ol);
        temp_ol=&((*temp_ol)->next);
    }
    (*temp_ol)->next=NULL;
    return_operation=(*temp_ol)->operation;
    (*temp_ol)=NULL;
    (*current_sl)->next=NULL;
    free(*temp_ol);
    return return_operation;
}

OPERATION OL_lastOperation(Operation_List *ol){
    while (ol->next!=NULL) {
        ol=ol->next;
    }
    return ol->operation;
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
    temp_ol->current_index=(*current_ol)->current_index+1;
    temp_ol->ahead=(*current_ol);
    (*current_ol)->next=temp_ol;
    //(*current_ol)->next->ahead=(*current_ol);
}

// true true and --> true
char* judge(char *value1, char *value2, char *and_or){
    //
    char *return_judge;
    if (term(and_or, "and")) {
        if (term("false", value1)||term("false",value2)) {
            return_judge="false";
        }
            return_judge="true";
    }
    else if (term(and_or, "or")){
        if (term("true", value2)||term("true", value2)) {
            return_judge="true";
        }
        return_judge="false";
    }
    else{
        printf("Error..and_or\n");
        exit(0);
    }
    return return_judge;
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
    //char *arg0=NULL;
    char *arg1=NULL;
    char *arg2=NULL;
    int r_index1=-1;
    //int r_index2=-1;
    //int s_index=-1;
    char *print_str=NULL;
    char *print_str2=NULL;
    char *can_pass="";
    
    switch (operation.opcode) {
            /*
        case LOADG:
            // LOAD r1 #100
            r_index1=register_index(operation.arg0);
            arg1=load_value(operation.arg1);
            register_w[r_index1].value=arg1;
            break;
            */
            /*
        case MOVE:
            // MOVE r1 r2
            r_index1=register_index(operation.arg0);
            r_index2=register_index(operation.arg1);
            register_w[r_index1].value=register_w[r_index2].value;
            break;
             */
        case SETG:
            // SET 0 1
            // SET 0 #100
            register_w[atoi(operation.arg0)].value=load_value(operation.arg1);
            break;
        //case SETNONE:
            // SETNONE 0
        //    register_w[atoi(operation.arg0)].value="none";
        //    break;
        case SETCONS:
            // SETCONS 0 100
            register_w[atoi(operation.arg0)].value=operation.arg1;
            break;
            /*
        case SETG:
            // SETG 0 r1
            s_index=atoi(operation.arg0);
            arg1=load_value(operation.arg1);
            stack[s_index].value=arg1;
            break;
            */
            
            // ADD SUB MULT DIV MOD POW only support num now
        case ADD:
            // ADD 0 0 1
            //printf("%s %s\n",operation.arg2,operation.arg1);
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            //printf("%s %s\n",arg2,arg1);

            r_index1=atoi(operation.arg0);
            register_w[r_index1].value=add(arg1, arg2);
            break;
            
            
        case SUB:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=atoi(operation.arg0);
            register_w[r_index1].value=sub(arg1, arg2);
            break;
            
            
        case MUL:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=atoi(operation.arg0);
            register_w[r_index1].value=mul(arg1, arg2);
            break;
            
            
        case DIV:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=atoi(operation.arg0);
            register_w[r_index1].value=divide(arg1, arg2);
            break;
            
            
        case MOD:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=atoi(operation.arg0);
            register_w[r_index1].value=mod(arg1, arg2);
            break;
            
            
        case POW:
            // SUB r0 r0 r1   r0=r0-r1
            arg2=load_value(operation.arg2);
            arg1=load_value(operation.arg1);
            r_index1=atoi(operation.arg0);
            register_w[r_index1].value=power(arg1, arg2);
            break;
        
        // AND 0 0 1
        case AND:
            can_pass=judge(load_value(operation.arg1),load_value(operation.arg2),"and");
            register_w[atoi(operation.arg0)].value=can_pass;
            break;
        //NOT 0
        case NOT:
            can_pass=register_w[atoi(operation.arg0)].value;
            if (term(can_pass, "true")) {
                can_pass="false";
            }
            else{
                can_pass="true";
            }
            register_w[atoi(operation.arg0)].value=can_pass;
            break;
        
        // OR 0 0 1
        // 1 true
        // 0 false
        // then 0-> true
        case OR:
            can_pass=judge(load_value(operation.arg1),load_value(operation.arg2),"or");
            register_w[atoi(operation.arg0)].value=can_pass;
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
                print_str2=CL_formatWalleyString(print_str2);
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
            
        case LABEL:
            break;

            
        default:
            break;
    }
}

bool pass(char *value1, char *value2, enum OPCODE opcode){
    //bool pass=FALSE;
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
        // jump ahead
        else if (ol->operation.opcode==JMPA){
            char *label_index=ol->operation.arg0;
            while (ol->operation.opcode!=LABEL || strcmp(label_index, ol->operation.arg0)!=0) {
                ol=ol->ahead;
                if (ol==NULL) {
                    printf("Error..JUMP Ahead Too Much\nDid not find Lable");
                    exit(0);
                }
            }
            VM_Run_Command(ol);
            return;
        }
        // jump back
        else if (ol->operation.opcode==JMPB){
            char *label_index=ol->operation.arg0;
            while (ol->operation.opcode!=LABEL || strcmp(label_index, ol->operation.arg0)!=0) {
                ol=ol->next;
                if (ol==NULL) {
                    printf("Error..JUMP Behind Too Much\nDid not find Lable");
                    exit(0);
                }
            }
            VM_Run_Command(ol);
            return;
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
    else if (ol->operation.opcode==JMPA){
        char *label_index=ol->operation.arg0;
        while (ol->operation.opcode!=LABEL || strcmp(label_index, ol->operation.arg0)!=0) {
            ol=ol->ahead;
            if (ol==NULL) {
                printf("Error..JUMP Ahead Too Much\nDid not find Lable");
                exit(0);
            }
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
        char *arg0;
        char *arg1;
        char *arg2;        
        Char_List *cl0;
        Char_List *cl1;
        Char_List *cl2;
        

        CL_initWithChar(&cl0, 0);
        CL_initWithChar(&cl1, 0);
        CL_initWithChar(&cl2, 0);

        // remove \b behind
        int a=1;
        while (arr[length-a]=='\n') {
            arr[length-a]=' ';
            a++;
        }
        
        
        int i=0;
        while (arr[i]!=' '&&i<length) {
            enum_name[i]=arr[i];
            i++;
        }
        
        i=i+1;
        int count=0;
        while (arr[i]!=' '&&i<length) {
            if (arr[i]=='"') {
                int index_of_final=indexOfFinalDoubleQuote(arr, i);
                for (; i<index_of_final+1; i++) {
                    CL_addChar(&cl0, arr[i]);
                    count++;
                }
                
            }
            else{
                CL_addChar(&cl0, arr[i]);
                count++;
                i++;
            }
        }
        
        i=i+1;
        count=0;
        while (arr[i]!=' '&&i<length) {
            if (arr[i]=='"') {
                int index_of_final=indexOfFinalDoubleQuote(arr, i);
                for (; i<index_of_final+1; i++) {
                    CL_addChar(&cl1, arr[i]);
                    count++;
                }
                
            }
            else{
                CL_addChar(&cl1, arr[i]);
                count++;
                i++;
            }
        }
    
    
        i=i+1;
        count=0;
        while (arr[i]!=' '&&i<length) {
            if (arr[i]=='"') {
                int index_of_final=indexOfFinalDoubleQuote(arr, i);
                for (; i<index_of_final+1; i++) {
                    CL_addChar(&cl2, arr[i]);
                    count++;
                }
                
            }
            else{
            CL_addChar(&cl2, arr[i]);
            count++;
            i++;
            }
        }
    
        arg0=CL_toString(cl0);
        arg1=CL_toString(cl1);
        arg2=CL_toString(cl2);
        
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
    
    printf("\n=======REGISTER====\n");
    REGISTER_Print();
    
}

void VM_init(){
    VL_init(&GLOBAL_VAR_LIST);
}






















