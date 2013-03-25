//
//  walley_data.h
//  CPractice
//
//  Created by shd101wyy on 12-10-17.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include "walley_string.h"


//=============================

struct TOKEN{
    char *TOKEN_CLASS;
    char *TOKEN_STRING;
    int TOKEN_START;
    int TOKEN_END; // |"Hello"|  index of final "
};

void TOKEN_print(struct TOKEN token){
    printf("%s:|%s|:%d:%d\n",token.TOKEN_CLASS,token.TOKEN_STRING,token.TOKEN_START,token.TOKEN_END);
}


struct TL{
    struct TOKEN current_token;
    struct TL *ahead;
    struct TL *next;
};



void TL_init(struct TL **tl){
    (*tl)=(struct TL *)malloc(sizeof(struct TL)*1);
    (*tl)->current_token.TOKEN_STRING=NULL;
    (*tl)->current_token.TOKEN_CLASS=NULL;
    (*tl)->current_token.TOKEN_START=-1;
    (*tl)->current_token.TOKEN_END=-1;
    (*tl)->next=NULL;
    (*tl)->ahead=NULL;
}

void TL_initWithToken(struct TL **tl, struct TOKEN token){
    (*tl)=(struct TL *)malloc(sizeof(struct TL)*1);
    (*tl)->current_token.TOKEN_STRING=token.TOKEN_STRING;
    (*tl)->current_token.TOKEN_CLASS=token.TOKEN_CLASS;
    (*tl)->current_token.TOKEN_START=token.TOKEN_START;
    (*tl)->current_token.TOKEN_END=token.TOKEN_END;
    (*tl)->next=NULL;
    (*tl)->ahead=NULL;
}

int TL_length(struct TL *tl){
    if (tl==NULL) {
        return 0;
    }
    int length=0;
    struct TL *next_tl=tl->next;
    while (next_tl!=NULL) {
        length++;
        next_tl=next_tl->next;
    }
    length++;
    return length;
}

void TL_addToken(struct TL **tl, Token add_token){
    if ((*tl)->current_token.TOKEN_STRING==NULL) {
        (*tl)->current_token=add_token;
        (*tl)->next=NULL;
        (*tl)->ahead=NULL;
        return;
    }
    
    Token_List *add_tl;//=(struct TL*)malloc(sizeof(struct TL)*1);
    //add_tl->current_token=add_token;
    //add_tl->next=NULL;
    //add_tl->ahead=NULL;
    TL_initWithToken(&add_tl, add_token);
    
    //int length=TL_length(*tl);
    //int i=0;
    
    Token_List **current_tl=&(*tl);
    
    while((*current_tl)->next!=NULL) {
        current_tl=&((*current_tl)->next);
    }
    
    (*current_tl)->next=add_tl;
    (*current_tl)->next->ahead=(*current_tl);
}

void TL_print(struct TL *tl){
    int length=TL_length(tl);
    int i=0;
    for (; i<length; i++) {
        printf("%s:|%s|:%d:%d\n",tl->current_token.TOKEN_CLASS,tl->current_token.TOKEN_STRING,tl->current_token.TOKEN_START,tl->current_token.TOKEN_END);
        tl=tl->next;
    }
}

struct TOKEN TL_tokenAtIndex(struct TL *tl, int index){
    int i=0;
    while (tl->next!=NULL) {
        if (index==i) {
            return tl->current_token;
        }
        i++;
        tl=tl->next;
    }
    if (index==i) {
        return tl->current_token;
    }
    else{
        printf("TL index %d out of boundary",index);
        exit(0);
    }
}

struct TL *TL_subtl(struct TL *tl,int begin, int end){
    if (end<=begin) {
        printf("TL end <= begin\n");
        exit(0);
    }
    
    struct TL *return_tl;
    TL_init(&return_tl);
    int length=TL_length(tl);
    if (end>length) {
        printf("TL end %d > length %d\n",end,length);
        exit(0);
    }
    int i=0;
    for (; i<length; i++) {
        if (i>=begin&&i<end) {
            //return_tl->current_token=tl->current_token;
            TL_addToken(&return_tl, tl->current_token);
            //return_tl->next=tl->next;
        }
        tl=tl->next;
    }
    return return_tl;
}


int TL_indexOfTokenThatHasTokenString(Token_List *tl, char *token_string){
    int output=-1;
    int i=0;
    while (tl->next!=NULL) {
        if (strcmp(tl->current_token.TOKEN_STRING, token_string)==0) {
            return i;
        }
        tl=tl->next;
        i++;
    }
    if (strcmp(tl->current_token.TOKEN_STRING, token_string)==0) {
        return i;
    }
    
    return output;
}

int TL_indexOfTokenThatHasTokenClass(Token_List *tl, char *token_class){
    int output=-1;
    int i=0;
    while (tl->next!=NULL) {
        if (strcmp(tl->current_token.TOKEN_CLASS, token_class)==0) {
            return i;
        }
        tl=tl->next;
        i++;
    }
    if (strcmp(tl->current_token.TOKEN_CLASS, token_class)==0) {
        return i;
    }
    
    return output;
}




char *TL_toString(Token_List *tl){
    Token_List *temp_tl=tl;
    int length=0;
    while (tl->next!=NULL) {
        length+=(int)strlen(tl->current_token.TOKEN_STRING);
        tl=tl->next;
    }
    length+=(int)strlen(tl->current_token.TOKEN_STRING);
    length++;
    char *output=(char*)malloc(sizeof(char)*length);
    int index=0;
    strcpy(output, "");
    tl=temp_tl;
    while (tl->next!=NULL) {
        char *copy_string=tl->current_token.TOKEN_STRING;
        int length_of_cs=(int)strlen(copy_string);
        int i=0;
        for (; i<length_of_cs; i++) {
            output[index]=copy_string[i];
            index++;
        }
        tl=tl->next;
    }
    
    char *copy_string=tl->current_token.TOKEN_STRING;
    int length_of_cs=(int)strlen(copy_string);
    int i=0;
    for (; i<length_of_cs; i++) {
        output[index]=copy_string[i];
        index++;
    }
    output[index]=0;
    return output;    
}
