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
struct SL;
struct SL{
    char *string_content;
    struct SL *next;
};
typedef struct SL Str_List;


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
    if (string_list==NULL) {
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
















