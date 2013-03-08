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

typedef struct TOKEN Token;

struct TL{
    struct TOKEN current_token;
    struct TL *next;
};

typedef struct TL Token_List;


void TL_init(struct TL **tl){
    (*tl)=(struct TL *)malloc(sizeof(struct TL)*1);
    (*tl)->current_token.TOKEN_STRING=NULL;
    (*tl)->current_token.TOKEN_CLASS=NULL;
    (*tl)->current_token.TOKEN_START=-1;
    (*tl)->current_token.TOKEN_END=-1;
    (*tl)->next=NULL;
}

void TL_initWithToken(struct TL **tl, struct TOKEN token){
    (*tl)=(struct TL *)malloc(sizeof(struct TL)*1);
    (*tl)->current_token.TOKEN_STRING=token.TOKEN_STRING;
    (*tl)->current_token.TOKEN_CLASS=token.TOKEN_CLASS;
    (*tl)->current_token.TOKEN_START=token.TOKEN_START;
    (*tl)->current_token.TOKEN_END=token.TOKEN_END;
    (*tl)->next=NULL;
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
        return;
    }
    
    Token_List *add_tl=(struct TL*)malloc(sizeof(struct TL)*1);
    add_tl->current_token=add_token;
    add_tl->next=NULL;
    
    int length=TL_length(*tl);
    int i=0;
    
    Token_List **current_tl=&(*tl);
    
    for (i=1; i<length; i++) {
        current_tl=&((*current_tl)->next);
    }
    
    (*current_tl)->next=add_tl;
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
    if (end>=length) {
        printf("TL end >= length\n");
        exit(0);
    }
    int i=0;
    for (; i<length; i++) {
        if (i>=begin&&i<end) {
            return_tl->current_token=tl->current_token;
            return_tl->next=tl->next;
        }
        tl=tl->next;
    }
    return return_tl;
}


