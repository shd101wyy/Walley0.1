/* 
 * File:   walley_string.h
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 12:34 PM
 */

#include "walley_pre_functions.h"
bool stringIsDigit(char *input_str){
    bool isDigit=TRUE;
    int i=0;
    if(input_str[0]=='.')
        i=1;
    if(input_str[0]=='-')
        i=1;
    
    int initial=i;
    int num_of_dot=0;
    
    for(;i<(int)strlen(input_str);i++){
        if (input_str[i]=='.') {
            num_of_dot++;
        }
        if(input_str[i]=='.'&&i!=initial&&i!=(int)strlen(input_str)-1){
            continue;
        }
        if(isdigit(input_str[i])==FALSE){
            isDigit=FALSE;
            break;
        }
    }
    if (num_of_dot>=2) {
        return FALSE;
    }
    return isDigit;
}

//  [1,2,3,[3]]
//  012345678910
//  return 10
int indexOfFinalDoubleQuote(char *input_str, int first_index){
    char first_char=input_str[first_index];
    int i=first_index+1;
    int length=(int)strlen(input_str);
    if (first_char=='"') {
        for (; i<length; i++) {
            if (input_str[i]=='"'&&input_str[i-1]!='\\') {
                return i;
            }
        }
    }
   
    // did not find
    return -1;
}


void Walley_Print_Error(char *input_str,char *error_message,int error_start_index){
    printf("Error.. %s\n",error_message);
    printf("%s\n",input_str);
    char *empty=(char*)malloc(sizeof(char)*(error_start_index+2));
    strcpy(empty, "");
    int i=0;
    for (; i<error_start_index; i++) {
        empty[i]=' ';
    }
   
    strcat(empty, "^");
    empty[error_start_index+1]=0;
    
    
    printf("%s\n",empty);
    exit(0);
}





/*
====================================================================================================================================================================================================================================================================================== LINKED LIST =============================================================================================================
 
 */
//================= STRING LIST ============================================================================

struct SL{
    char *string_content;
    struct SL *next;
};


void SL_initSLWithString(struct SL **string_list, char *init_string){
    (*string_list)=(struct SL*)malloc(sizeof(struct SL)*1);
    (*string_list)->string_content=init_string;
    (*string_list)->next=NULL;
}
void SL_initSL(struct SL **string_list){
    (*string_list)=(struct SL*)malloc(sizeof(struct SL)*1);
    (*string_list)->next=NULL;
    (*string_list)->string_content=NULL;
}

int SL_length(struct SL *string_list){
    if (string_list==NULL || string_list->string_content==NULL) {
        return 0;
    }
    int length=0;
    struct SL *next_sl=string_list->next;
    while (next_sl!=NULL) {
        length++;
        next_sl=next_sl->next;
    }
    length++;
    return length;
}

void SL_addString(struct SL **string_list, char *add_string){
    if ((*string_list)->string_content==NULL) {
        (*string_list)->string_content=add_string;
        (*string_list)->next=NULL;
        return;
    }
    
    struct SL *add_string_list=(struct SL*)malloc(sizeof(struct SL)*1);
    add_string_list->string_content=add_string;
    add_string_list->next=NULL;
    
    int length=SL_length(*string_list);
    int i=0;
    
    struct SL **current_sl=&(*string_list);
    
    for (i=1; i<length; i++) {
        current_sl=&((*current_sl)->next);
    }
    
    (*current_sl)->next=add_string_list;
}


void SL_print(struct SL *string_list){
    int length=SL_length(string_list);
    int i=0;
    for (; i<length; i++) {
        printf("%d-- %s\n",i,string_list->string_content);
        string_list=string_list->next;
    }
}

char *SL_stringAtIndex(struct SL *string_list, int index){
    int i=0;
    while (string_list->next!=NULL) {
        if (index==i) {
            return string_list->string_content;
        }
        i++;
        string_list=string_list->next;
    }
    if (index==i) {
        return string_list->string_content;
    }
    else{
        printf("SL index %d out of boundary",index);
        exit(0);
    }
}

char *SL_pop(struct SL **string_list){
    int length=SL_length(*string_list);
    int i=0;
    struct SL **sl=&(*string_list);
    struct SL **current_sl;
    char *return_string="";
    if (length==1) {
        (*sl)->next=NULL;
        return_string=(*sl)->string_content;
        (*sl)->string_content=NULL;
        free(*sl);
        SL_initSL(sl);
        return return_string;
    }
    for (i=1; i<length; i++) {
        current_sl=&(*sl);
        sl=&((*sl)->next);
    }
    (*sl)->next=NULL;
    return_string=(*sl)->string_content;
    (*sl)->string_content=NULL;
    (*current_sl)->next=NULL;
    free(*sl);
    return return_string;
}

void SL_removeStringAtIndex(struct SL **string_list, int index){
    if (index==0) {
        (*string_list)=(*string_list)->next;
        return;
    }
    int length=SL_length(*string_list);
    if (index>=length) {
        printf("index out of boundary\n");
        exit(0);
    }
    
    struct SL **current_sl=&(*string_list);
    
    if (length==1) {
        (*current_sl)->next=NULL;
        (*current_sl)->string_content=NULL;
        free(current_sl);
    }
    
    
    int i=0;
    for (; i<length-1; i++) {
        if (i==0) {
        }
        else{
            current_sl=&((*current_sl)->next);
        }
        if (i+1==index) {
            struct SL **next_that_need_to_delete=&((*current_sl)->next);
            (*current_sl)->next=(*current_sl)->next->next;
            
            (*next_that_need_to_delete)->next=NULL;
            (*next_that_need_to_delete)->string_content=NULL;
            free(next_that_need_to_delete);
            return;
        }
    }
}

// convert String List to single string
char *SL_toString(Str_List *sl){
    int malloc_length=0;
    Str_List *temp_sl=sl;
    while (sl->next!=NULL) {
        malloc_length+=(int)strlen(sl->string_content);
        sl=sl->next;
    }
    malloc_length+=(int)strlen(sl->string_content);
    sl=temp_sl;
    
    char *output_str=(char*)malloc(sizeof(char)*(malloc_length+1));
    
    
    int count=0;
    while (sl->next!=NULL) {
        int i=0;
        int length=(int)strlen(sl->string_content);
        for (; i<length; i++) {
            output_str[count]=(sl->string_content)[i];
            count++;
        }
        sl=sl->next;
    }
    int i=0;
    int length=(int)strlen(sl->string_content);
    for (; i<length; i++) {
        output_str[count]=(sl->string_content)[i];
        count++;
    }
    
    output_str[count]=0;
    return output_str;

}


//================================================
struct Char_List{
    char current_char;
    struct Char_List *next;
};

typedef struct Char_List Char_List;
void CL_init(Char_List **cl){
    (*cl)=(Char_List *)malloc(sizeof(Char_List)*1);
    (*cl)->next=NULL;
}

void CL_initWithChar(Char_List **cl, char init_char){
    (*cl)=(Char_List *)malloc(sizeof(Char_List)*1);
    (*cl)->current_char=init_char;
    (*cl)->next=NULL;
}
void CL_addChar(Char_List **cl, char add_char){
    if ((*cl)->current_char==0) {
        (*cl)->current_char=add_char;
        (*cl)->next=NULL;
        return;
    }
    Char_List **current_cl=&(*cl);
    while ((*current_cl)->next!=NULL) {
        current_cl=&((*current_cl)->next);
    }
    Char_List *temp_cl;
    CL_initWithChar(&temp_cl, add_char);
    (*current_cl)->next=temp_cl;
}

int CL_length(Char_List *cl){
    int length=0;
    while (cl->next!=NULL) {
        length++;
        cl=(cl->next);
    }
    length++;
    return length;
}

void CL_print(Char_List *cl){
    while (cl->next!=NULL) {
        printf("%c",cl->current_char);
        cl=(cl->next);
    }
    printf("%c",cl->current_char);
}

char *CL_toString(Char_List *cl){
    int length=CL_length(cl);
    char *output=(char*)malloc(sizeof(char)*(length+1));
    strcpy(output, "");
    int i=0;
    while (cl->next!=NULL) {
        output[i]=cl->current_char;
        i++;
        cl=cl->next;
    }
    output[i]=cl->current_char;
    i++;
    output[i]=0;
    return output;
}

//===============
/*
 \n (newline)
 \t (tab)
 \v (vertical tab)
 \f (new page)
 \b (backspace)
 \r (carriage return)
 */

// input_str is the content inside "\n", where \n is \\n, so change \\n to \\n
char *CL_formatWalleyString(char *input_str){
    int length=(int)strlen(input_str);
    if (length<=1) {
        return input_str;
    }
    Char_List *cl;
    int i=0;
    
    // init cl
    if (i<length-1&&input_str[i]=='\\'
        &&(input_str[i+1]=='n'
           ||input_str[i+1]=='t'
           ||input_str[i+1]=='v'
           ||input_str[i+1]=='f'
           ||input_str[i+1]=='b'
           ||input_str[i+1]=='r'
           )
        ) {
        switch (input_str[i+1]) {
            case 'n':
                CL_initWithChar(&cl, '\n');
                break;
            case 't':
                CL_initWithChar(&cl, '\t');
                break;
            case 'v':
                CL_initWithChar(&cl, '\v');
                break;
            case 'f':
                CL_initWithChar(&cl, '\f');
                break;
            case 'b':
                CL_initWithChar(&cl, '\b');
                break;
            case 'r':
                CL_initWithChar(&cl, '\r');
                break;
            default:
                printf("Error..\\ mistake\n");
                exit(0);
                break;
        }
        i=2;
    }
    else{
        CL_initWithChar(&cl, input_str[0]);
        i=1;
    }

    
    
    for (; i<length; i++) {
        
        if (i<length-1&&input_str[i]=='\\'
            &&(input_str[i+1]=='n'
               ||input_str[i+1]=='t'
               ||input_str[i+1]=='v'
               ||input_str[i+1]=='f'
               ||input_str[i+1]=='b'
               ||input_str[i+1]=='r'
               )
            ) {
            switch (input_str[i+1]) {
                case 'n':
                    CL_addChar(&cl, '\n');
                    break;
                case 't':
                    CL_addChar(&cl, '\t');
                    break;
                case 'v':
                    CL_addChar(&cl, '\v');
                    break;
                case 'f':
                    CL_addChar(&cl, '\f');
                    break;
                case 'b':
                    CL_addChar(&cl, '\b');
                    break;
                case 'r':
                    CL_addChar(&cl, '\r');
                    break;
                default:
                    printf("Error..\\ mistake\n");
                    exit(0);
                    break;
            }
            i=i+1;
            continue;
        }
        if (input_str[i]=='"') {
            int index_of_final=indexOfFinalDoubleQuote(input_str, i);
            i=index_of_final;
            int j=0;
            for (; j<index_of_final+1; j++) {
                CL_addChar(&cl, input_str[j]);
            }
            continue;
        }

        CL_addChar(&cl, input_str[i]);

    }

return CL_toString(cl);
    
}


char *intToCString(double num1){
    int num1_int=(int)num1;
    char *temp=(char*)malloc(sizeof(char)*1000);
    sprintf(temp, "%d",num1_int);
    return temp;
    
}

char *numToCString(double num){
    char *temp=(char*)malloc(sizeof(char)*1000);
    sprintf(temp, "%f",num);
    return temp;
}


// hello -> "hello"
// "hello" -> "hello"
char *toString(char *input_str){
    if (input_str[0]=='"') {
        return input_str;
    }
    else{
        int malloc_length=(int)strlen(input_str)+2;
        char *output=(char*)malloc(sizeof(char)*(malloc_length+1));
        strcpy(output, "\"");
        strcat(output, input_str);
        strcat(output, "\"");
        output[malloc_length]=0;
        return output;
    }
}


char* substr(char* input_str, int from_index, int to_index) {
        int length = to_index - from_index;
        int i;
        char *output =(char*)malloc((length+1) * sizeof (char));
        strcpy(output, "");
        for (i = 0; i < length; i++) {
            output[i] = input_str[from_index + i];
        }
        output[i]=0;
        return output;
        
}





