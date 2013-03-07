//
//  walley_lexical.h
//  Walley
//
//  Created by shd101wyy on 13-2-12.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_string.h"
bool isSign(char sign);
bool isJudgeSign(char *input_str, int index);

struct TOKEN{
    char *TOKEN_CLASS;
    char *TOKEN_STRING;
    int TOKEN_START;
    int TOKEN_END; // |"Hello"|  index of final "
};

// Token list
void TL_PrintTOKEN(struct TOKEN *token){
    int row=1;
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TOKEN_PrintTOKEN..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    while (row<length) {
        printf("%s:|%s|:%d:%d\n",token[row].TOKEN_CLASS,token[row].TOKEN_STRING,token[row].TOKEN_START,token[row].TOKEN_END);
        row++;
    }
}

void TL_initTokenList(struct TOKEN **token){
    *token=(struct TOKEN*)malloc(sizeof(struct TOKEN)*1);
    (*token)->TOKEN_CLASS="__size_of_array__";
    (*token)->TOKEN_STRING="1";
    (*token)->TOKEN_START=-1;
    (*token)->TOKEN_END=-1;
}

void TL_addProperty(struct TOKEN **token,char *token_class, char *token_string, int token_start, int token_end){
    
    int length=0;
    if (strcmp((*token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TL_addProperty..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*token)->TOKEN_STRING);
    }
    
    (*token)->TOKEN_STRING=intToCString(1+atoi((*token)->TOKEN_STRING));
    
    *token=(struct TOKEN*)realloc(*token, sizeof(struct TOKEN)*(length+1));
    (*token+length)->TOKEN_CLASS=token_class;
    (*token+length)->TOKEN_STRING=token_string;
    (*token+length)->TOKEN_START=token_start;
    (*token+length)->TOKEN_END=token_end;

}


const char* W_KEYWORDS[]={"if","elif","else","for","while","switch","case","def","class"};   //12-3=9     ,"syms","global","<@"}; //12
const char W_WHITESPACES[]={' ','\n','\t'};//3
const char* W_OPERATOR[]={"+","-","**","*","^","/","\\","%"};//8
const char* W_JUDGESIGN[]={"<",">","<=",">=","==","!="};//6
const char* W_RELATION[]={"and","or"};//2
const char* W_TRUE_OR_FALSE[]={"TRUE","FALSE"};//2
//const char* W_NUMBER;      1234  12.4
//const char* W_ID;          Hello123
//const char* W_STRING;      'Hello' "Hello"
//const char* W_DICTIONARY;  {"A":12} // now it is for Expression, not dictionary anymore
//const char* W_LIST_TABLE;   [1,2,3]  [["a"]=12,[0]=2]
//const char* W_ASSIGNMENT_OPERATOR;  = sign
//const char* W_PUNCTUATION;        : , ;
//const char* W_UNFINISHED_VAR  '123  ||  "123 || [123,1
//const char  W_DOT  .  // it is for .show(), if input_str is 1.6, then the . is not dot
//const char* W_LONG_ANNOTATION_LEFT  #~
//const char* W_LONG_ANNOTATION_RIGHT ~#
//const char* W_SHORT_ANNOTATION      #



// 1.6
// 012 ---> FALSE
bool isW_Dot(char *input_str, int index_of_dot){
    if (input_str[index_of_dot]!='.') {
        return FALSE;
    }
    if (index_of_dot==(int)strlen(input_str)-1) {
        return TRUE;
    }
    if (isdigit(input_str[index_of_dot+1])) {
        return FALSE;
    }
    else{
        return TRUE;
    }
}

// check if it is # #~ or ~#
bool isW_Annotation(char *input_str, int index_of_dot){
    if (input_str[index_of_dot]!='#'&&input_str[index_of_dot]!='~') {
        return FALSE;
    }
    if (input_str[index_of_dot]=='#') {
        return TRUE;
    }
    if (input_str[index_of_dot]=='#') {
        if (index_of_dot<(int)strlen(input_str)-1) {
            if (input_str[index_of_dot+1]=='~') {
                return TRUE;
            }
        }
    }
    if (input_str[index_of_dot]=='~') {
        if (index_of_dot<(int)strlen(input_str)-1) {
            if (input_str[index_of_dot+1]=='#') {
                return TRUE;
            }
        }
    }
    
    return FALSE;
}

bool isW_Assignment_Operator(char *input_str, int index_of_equa){
    if (input_str[index_of_equa]!='=') {
        return FALSE;
    }
    int length=(int)strlen(input_str);

    if (index_of_equa+1==length) {
        return TRUE;
    }
    else{
        if (input_str[index_of_equa+1]!='=') {
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
}

char * TOKEN_analyzeTokenClass(char *token_string){
    if (strcmp(token_string, "#")==0) {
        return "W_SHORT_ANNOTATION";
    }
    if (strcmp(token_string, "#~")==0) {
        return "W_LONG_ANNOTATION_LEFT";
    }
    if (strcmp(token_string, "~#")==0) {
        return "W_LONG_ANNOTATION_RIGHT";
    }
    if (strcmp(token_string, ".")==0) {
        return "W_DOT";
    }
    if (strcmp(token_string, ":")==0||strcmp(token_string, ",")==0||strcmp(token_string, ";")==0) {
        return "W_PUNCTUATION";
    }
    if (token_string[0]=='"'||token_string[0]=='\'') {
        return "W_STRING";
    }
    
    if (token_string[0]=='[') {
        return "W_LIST_TABLE";
    }
    
    if (token_string[0]=='{') {
        return "W_DICTIONARY";
    }
    
    if (strcmp(token_string, "=")==0) {
        return "W_ASSIGNMENT_OPERATOR";
    }
    
    int i=0;
    int length=12-3; //W_KEYWORDS
    for (i=0; i<length; i++) {
        if (strcmp(W_KEYWORDS[i], token_string)==0) {
            return "W_KEYWORDS";
        }
    }
    
    length=3;
    int j=0;
    bool is_white_space=TRUE;
    for (j=0; j<(int)strlen(token_string); j++) {
        bool satisfied=FALSE;
        for (i=0; i<length; i++) {
            if (W_WHITESPACES[i]==token_string[j]) {
                satisfied=TRUE;
            }
        }
        if (satisfied==FALSE) {
            is_white_space=FALSE;
            break;
        }
    }
    if (is_white_space) {
        return "W_WHITESPACES";
    }

    length=8;
    for (i=0; i<length; i++) {
        if (strcmp(W_OPERATOR[i], token_string)==0) {
            return "W_OPERATOR";
        }
    }
    
    length=6;
    for (i=0; i<length; i++) {
        if (strcmp(W_JUDGESIGN[i], token_string)==0) {
            return "W_JUDGESIGN";
        }
    }
    length=2;
    for (i=0; i<length; i++) {
        if (strcmp(W_RELATION[i], token_string)==0) {
            return "W_RELATION";
        }
    }
    
    length=2;
    for (i=0; i<length; i++) {
        if (strcmp(W_TRUE_OR_FALSE[i], token_string)==0) {
            return "W_TRUE_OR_FALSE";
        }
    }
    
    
    if (stringIsDigit(token_string)) {
        return "W_NUMBER";
    }
    else{
        return "W_ID";
    }
}


//  [1,2,3,[3]]
//  012345678910
//  return 10
int indexOfFinal(char *input_str, int first_index){
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
    else if(first_char=='\''){
        for (; i<length; i++) {
            if (input_str[i]=='\''&&input_str[i-1]!='\\') {
                return i;
            }
        }
    }
    else if(first_char=='['){
        int left=1;
        int right=0;
        for (; i<length; i++) {
            if (input_str[i]=='['&&charIsInString(input_str, i)==FALSE) {
                left++;
            }
            if (input_str[i]==']'&&charIsInString(input_str, i)==FALSE) {
                right++;
            }
            if (left==right) {
                return i;
            }
        }
    
    }
    // (
    else if(first_char=='('){
        int left=1;
        int right=0;
        for (; i<length; i++) {
            if (input_str[i]=='('&&charIsInString(input_str, i)==FALSE) {
                left++;
            }
            if (input_str[i]==')'&&charIsInString(input_str, i)==FALSE) {
                right++;
            }
            if (left==right) {
                return i;
            }
        }
        
    }

    // {
    else{
        int left=1;
        int right=0;
        for (; i<length; i++) {
            if (input_str[i]=='{'&&charIsInString(input_str, i)==FALSE) {
                left++;
            }
            if (input_str[i]=='}'&&charIsInString(input_str, i)==FALSE) {
                right++;
            }
            if (left==right) {
                return i;
            }
        }

    }
    return -1;
    //printf("Error! Can not find the final index of |%s|\n",input_str);
    //exit(0);
}


int TL_length(struct TOKEN *token){
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TL_length..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    
    return length;
}

struct TOKEN* Walley_Lexica_Analysis(char *input_str){
    struct TOKEN *token=NULL;
    TL_initTokenList(&token);
    int length=(int)strlen(input_str);
    int i=0;
    int start=0;
    int end=0;
    char type='i'; // 'i' for id, 'b' for blank 's' for judge sign or sign(operator),'t' for "" '' [] {} type, 'c' for :
                   // 'd' for dot
                   // 'a' for annotation
                   // 'e' for assignment operator =
                
    char t=' ';
    i=1;
    if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
        type='b';
    }
    if (isalpha(input_str[0])||isdigit(input_str[0])) {
        type='i';
    }
    if (input_str[0]=='"') {
        type='t';
        t='s'; //string
    }
    if (input_str[0]=='\'') {
        type='t';
        t='s'; //string
    }
    if (input_str[0]=='{') {
        type='t';
        t='d'; //dict
    }
    if (input_str[0]=='[') {
        type='t';
        t='l'; //list or table
    }
    if (input_str[0]==':') {
        type='c';
    }
    if (isW_Annotation(input_str, 0)) {
        type='a';
    }
    if (isW_Assignment_Operator(input_str, 0)) {
        type='e';
    }
    for(;i<length;i++){
        //printf("%c\n",input_str[i]);
        if (type=='a') {
            //# or ~#
            if (input_str[i-1]=='#') {
                //#~
                if (input_str[i]=='~') {
                    end=i+1;
                    char *token_string=substr(input_str, i-1, end);
                    char *token_class=TOKEN_analyzeTokenClass(token_string);
                    TL_addProperty(&token, token_class, token_string,start,end-1);
                    start=end;
                    i=start;
                }
                
                //#
                else{
                    end=i;
                    char *token_string=substr(input_str, i-1, end);
                    char *token_class=TOKEN_analyzeTokenClass(token_string);
                    TL_addProperty(&token, token_class, token_string,start,end-1);
                    start=end;
                    i=start;
                }
            }
            // ~#
            else{
                end=i+1;
                char *token_string=substr(input_str, i-1, end);
                char *token_class=TOKEN_analyzeTokenClass(token_string);
                TL_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                i=start;
            }
            
            if (isJudgeSign(input_str,i)||isSign(input_str[i])) {
                type='s';
            }
            else if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                type='b';
            }
            else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                type='c';
            else if(input_str[i]=='"'||input_str[i]=='\''||input_str[i]=='P'||input_str[i]=='[')
                type='t';
            else if(isW_Dot(input_str, i)){
                type='d';
            }
            else if(isW_Annotation(input_str, i)){
                type='a';
            }
            else if(isW_Assignment_Operator(input_str, i)){
                type='e';
            }
            else{
                type='i';
            }

            
        }
        else if (type=='d') {
            char *token_string=".";
            char *token_class="W_DOT";
            TL_addProperty(&token, token_class, token_string,i-1,i);
            start=i;
            if (isJudgeSign(input_str,i)||isSign(input_str[i])) {
                type='s';
            }
            else if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                type='b';
            }
            else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                type='c';
            else if(input_str[i]=='"'||input_str[i]=='\''||input_str[i]=='P'||input_str[i]=='[')
                type='t';
            else if(isW_Dot(input_str, i)){
                type='d';
            }
            else if(isW_Annotation(input_str, i)){
                type='a';
            }
            else if(isW_Assignment_Operator(input_str, i)){
                type='e';
            }
            else{
                type='i';
            }

        }
        else if (type=='e') {
            char *token_string="=";
            char *token_class="W_ASSIGNMENT_OPERATOR";
            TL_addProperty(&token, token_class, token_string,i-1,i);
            start=i;
            if (isJudgeSign(input_str,i)||isSign(input_str[i])) {
                type='s';
            }
            else if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                type='b';
            }
            else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                type='c';
            else if(input_str[i]=='"'||input_str[i]=='\''||input_str[i]=='P'||input_str[i]=='[')
                type='t';
            else if(isW_Dot(input_str, i)){
                type='d';
            }
            else if(isW_Annotation(input_str, i)){
                type='a';
            }
            else{
                type='i';
            }
            
        }

        else if(type=='t'){
            start=i-1;
            int final_index=indexOfFinal(input_str, i-1);
            if (final_index==-1) {
                char *token_string=substr(input_str, i-1, (int)strlen(input_str));
                TL_addProperty(&token, "W_UNFINISHED_VAR", token_string,i-1,(int)strlen(input_str));
                return token;
            }
            char *token_string=substr(input_str, i-1, final_index+1);
            char *token_class=TOKEN_analyzeTokenClass(token_string);
            TL_addProperty(&token, token_class, token_string,i-1,final_index);
            i=final_index+1;
            start=i;
            
            if (isJudgeSign(input_str,i)||isSign(input_str[i])) {
                type='s';
            }
            else if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                type='b';
            }
            else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                type='c';
            else if(input_str[i]=='"'||input_str[i]=='\''||input_str[i]=='P'||input_str[i]=='[')
                type='t';
            else if(isW_Dot(input_str, i)){
                type='d';
            }
            else if(isW_Annotation(input_str, i)){
                type='a';
            }
            else if(isW_Assignment_Operator(input_str, i)){
                type='e';
            }
            else{
                type='i';
            }
        }
        else if (type=='i'){
            //if (isalpha(input_str[i])||isdigit(input_str[i])||input_str[i]=='_') {
            if (charIsInParenthesis(input_str, i)==TRUE||(input_str[i]!=' '&&input_str[i]!='\n'&&input_str[i]!='\t'&&isJudgeSign(input_str,i)==FALSE&&isSign(input_str[i])==FALSE&&
                input_str[i]!='"'&&input_str[i]!='\''&&input_str[i]!='{'&&input_str[i]!='['
                &&input_str[i]!=':'&&input_str[i]!=','&&input_str[i]!=';'&&isW_Dot(input_str, i)==FALSE&&isW_Annotation(input_str, i)==FALSE&&input_str[i]!='=')) {
                continue;
            }
            else{
                end=i;
                char *token_string=substr(input_str, start, end);
                char *token_class=TOKEN_analyzeTokenClass(token_string);
                TL_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                
                
                if (isJudgeSign(input_str,i)||isSign(input_str[i])) {
                    type='s';
                }
                else if (input_str[i]=='"') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='\'') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='{') {
                    type='t';
                    t='d'; //dict
                }
                else if (input_str[i]=='[') {
                    type='t';
                    t='l'; //list or table
                }
                else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                    type='c';
                else if(isW_Dot(input_str, i)){
                    type='d';
                }
                else if(isW_Annotation(input_str, i)){
                    type='a';
                }
                else if(isW_Assignment_Operator(input_str, i)){
                    type='e';
                }
                else{
                    type='b';
                }
            }
        }
        
        else if(type=='b'){
            if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                continue;
            }
            else{
                end=i;
                char *token_string=substr(input_str, start, end);
                char *token_class=TOKEN_analyzeTokenClass(token_string);
                TL_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                if (isJudgeSign(input_str,i)||isSign(input_str[i])) {
                    type='s';
                }
                else if (input_str[i]=='"') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='\'') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='{') {
                    type='t';
                    t='d'; //dict
                }
                else if (input_str[i]=='[') {
                    type='t';
                    t='l'; //list or table
                }
                else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                    type='c';
                else if(isW_Dot(input_str, i)){
                    type='d';
                }
                else if(isW_Annotation(input_str, i)){
                    type='a';
                }
                else if(isW_Assignment_Operator(input_str, i)){
                    type='e';
                }
                else{
                    type='i';
                }
            }
        }
        
        else if(type=='s'){
            if (isSign(input_str[i])==TRUE||isJudgeSign(input_str,i)==TRUE||input_str[i]=='=') {
                continue;
            }
            else{
                end=i;
                char *token_string=substr(input_str, start, end);
                char *token_class=TOKEN_analyzeTokenClass(token_string);
                TL_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                    type='b';
                }
                else if (input_str[i]=='"') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='\'') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='{') {
                    type='t';
                    t='d'; //dict
                }
                else if (input_str[i]=='[') {
                    type='t';
                    t='l'; //list or table
                }
                else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                    type='c';
                else if(isW_Dot(input_str, i)){
                    type='d';
                }
                else if(isW_Annotation(input_str, i)){
                    type='a';
                }
                else if(isW_Assignment_Operator(input_str, i)){
                    type='e';
                }
                else{
                    type='i';
                }
            }
        }
        
        else if(type=='c'){
            /*
            if (input_str[i-1]==';') {
                printf("%s\n",input_str);
                char *temp_str="";
                temp_str=Str_appendSpaceAhead(temp_str, i-1);
                printf("%s^\n",temp_str);
                printf("Error. Walley does not need ; in sentence\n");
                exit(0);
            }
             */
            TL_addProperty(&token, "W_PUNCTUATION", charToString(input_str[i-1]),i-1,i-1);
            start=i;
            if (isJudgeSign(input_str,i)||isSign(input_str[i])) {
                type='s';
            }
            else if (input_str[i]=='"') {
                type='t';
                t='s'; //string
            }
            else if (input_str[i]=='\'') {
                type='t';
                t='s'; //string
            }
            else if (input_str[i]=='{') {
                type='t';
                t='d'; //dict
            }
            else if (input_str[i]=='[') {
                type='t';
                t='l'; //list or table
            }

            else if (input_str[i]==' '||input_str[i]=='\t'||input_str[i]=='\n')
                type='b';
            else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                type='c';
            else if(isW_Dot(input_str, i)){
                type='d';
            }
            else if(isW_Annotation(input_str, i)){
                type='a';
            }
            else if(isW_Assignment_Operator(input_str, i)){
                type='e';
            }
            else
                type='i';
            
        }
        
        
    }
    
    
    
        // final add token
        end=length;
    if (start<end) {
        char *token_string=substr(input_str, start, end);
        char *token_class=TOKEN_analyzeTokenClass(token_string);
        TL_addProperty(&token, token_class, token_string,start,end-1);
    }

    
        return token;
}

int TL_numOfTOKEN_CLASS(struct TOKEN *token,char *token_class){
    int row=0;
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TL_numOfTOKEN_CLASS..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    int num=0;
    while (row<length) {
        if (strcmp(token_class, token[row].TOKEN_CLASS)==0) {
            num++;
        }
        row++;
    }
    return num;
}

// index_of_token_class starts from 0.
struct TOKEN TL_returnTokenAccordingToIndexAndTokenClass(struct TOKEN *token,char *token_class, int index_of_token_class){
    int row=0;
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TL_numOfTOKEN_CLASS..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    int num=-1;
    while (row<length) {
        if (strcmp(token_class, token[row].TOKEN_CLASS)==0) {
            num++;
        }
        if (num==index_of_token_class) {
            return token[row];
        }
        row++;
    }
    
    printf("Mistake occurred whiling calling function TL_returnTokenAccordingToIndexAndTokenClass\nNo token found according to class %s and index %d",token_class,index_of_token_class);
    exit(0);

}


int TL_indexOfFirstNoneWhiteSpaceToken(struct TOKEN *token){
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TL_numOfTOKEN_CLASS..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    int row=1;
    while (row<length) {
        if (strcmp(token[row].TOKEN_CLASS, "W_WHITESPACES")!=0) {
            return row;
        }
        row++;
    }
    printf("Error\nCan not find required none-whitespaces token\n");
    exit(0);
}





// Token Errors
void TOKEN_checkError(struct TOKEN *token,char *input_str){
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TOKEN_PrintTOKEN..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }

    int num_of_keyword=TL_numOfTOKEN_CLASS(token, "W_KEYWORDS");
    int num_of_W_ASSIGNMENT_OPERATOR=TL_numOfTOKEN_CLASS(token, "W_ASSIGNMENT_OPERATOR");
    
    // Error 1.. More Keywords
    // eg "if if x==1:"
    if (num_of_keyword>1) {
        struct TOKEN more_token=TL_returnTokenAccordingToIndexAndTokenClass(token, "W_KEYWORDS", 1);
        int start=more_token.TOKEN_START;
        printf("%s\n",input_str);
        char *temp_str="";
        temp_str=Str_appendSpaceAhead(temp_str, start);
        printf("%s^\n",temp_str);
        printf("Error. More Keywords |%s| occurred\n",more_token.TOKEN_STRING);
        exit(0);
    }
    
    // Error 2.. Miss :
    // eg "if x==1"
    if (num_of_keyword==1 && strcmp(token[TL_indexOfFirstNoneWhiteSpaceToken(token)].TOKEN_STRING,"W_KEYWORDS")==0) {
        struct TOKEN final_token=token[length-1];
        if (strcmp(final_token.TOKEN_STRING, ":")!=0) {
            int end=final_token.TOKEN_END+1;
            printf("%s\n",input_str);
            char *temp_str="";
            temp_str=Str_appendSpaceAhead(temp_str, end);
            printf("%s^\n",temp_str);
            printf("Error. Miss |:| at the end of sentence\n");

            TL_PrintTOKEN(token);
            exit(0);
        }
    }
    
    // Error 3.. x =
    // eg "x=" miss assigned content
    if (num_of_W_ASSIGNMENT_OPERATOR==1 && strcmp(token[length-1].TOKEN_STRING,"=")==0) {
        int end=token[length-1].TOKEN_END;
        printf("%s\n",input_str);
        char *temp_str="";
        temp_str=Str_appendSpaceAhead(temp_str, end);
        printf("%s^\n",temp_str);
        printf("Error. Miss assigned content after =\n");
        exit(0);
    }
    
    
    // Error 4.. if x=12:
    // = should be ==
    if (num_of_keyword==1 && num_of_W_ASSIGNMENT_OPERATOR>=1) {
        int start=TL_returnTokenAccordingToIndexAndTokenClass(token, "W_ASSIGNMENT_OPERATOR", 0).TOKEN_START;
        printf("%s\n",input_str);
        char *temp_str="";
        temp_str=Str_appendSpaceAhead(temp_str, start);
        printf("%s^\n",temp_str);
        printf("Error. Should not use =\nTry use == instead of = when comparing\n");
        exit(0);
    }
   
    // Error 5.. x=12=34
    if (num_of_W_ASSIGNMENT_OPERATOR>1) {
        int start=TL_returnTokenAccordingToIndexAndTokenClass(token, "W_ASSIGNMENT_OPERATOR", 1).TOKEN_START;
        printf("%s\n",input_str);
        char *temp_str="";
        temp_str=Str_appendSpaceAhead(temp_str, start);
        printf("%s^\n",temp_str);
        printf("Error. More = occurred\n");
        exit(0);
    }
    
    // Error 6.. x=123:
    
    if (num_of_W_ASSIGNMENT_OPERATOR==1) {
        struct TOKEN final_token=token[length-1];
        char *token_class=final_token.TOKEN_CLASS;
        if (strcmp(token_class, "W_STRING")!=0&&
            strcmp(token_class,"W_NUMBER")!=0&&
            strcmp(token_class, "W_DICTIONARY")!=0&&
            strcmp(token_class, "W_LIST_TABLE")!=0&&
            strcmp(token_class, "W_ID")!=0&&
            strcmp(token_class, "W_UNFINISHED_VAR")!=0) {
            int start=final_token.TOKEN_START;
            printf("%s\n",input_str);
            char *temp_str="";
            temp_str=Str_appendSpaceAhead(temp_str, start);
            printf("%s^\n",temp_str);
            printf("Error. invalid syntax\n");
            exit(0);
        }
    }
    
}


int TL_numOfNoneWhitespaces(struct TOKEN *token){
    int length=TL_length(token);
    int row=1;
    int num=0;
    while (row<length) {
        if (strcmp(token[row].TOKEN_CLASS, "W_WHITESPACES")!=0) {
            num++;
        }
        row++;
    }
    return num;
}

struct TOKEN *TL_returnTokenListWithoutWhitespaces(struct TOKEN *token){
    struct TOKEN *return_token;
    TL_initTokenList(&return_token);
    int length=TL_length(token);
    int row=1;
    while (row<length) {
        if (strcmp("W_WHITESPACES", token[row].TOKEN_CLASS)!=0) {
            TL_addProperty(&return_token, token[row].TOKEN_CLASS, token[row].TOKEN_STRING, token[row].TOKEN_START, token[row].TOKEN_END);
        }
        row++;
    }
    return return_token;
}

struct TOKEN *subtoken(struct TOKEN *token, int from_index, int to_index){
    if (from_index<=0) {
        printf("Error.. Token from_index <= 0\n");
        exit(2);
    }
    
    struct TOKEN *output_token;
    TL_initTokenList(&output_token);
    int i=from_index;
    for (; i<to_index; i++) {
        TL_addProperty(&output_token, token[i].TOKEN_CLASS, token[i].TOKEN_STRING, token[i].TOKEN_START, token[i].TOKEN_END);
    }
    return output_token;
}
struct TOKEN TOKEN_lastToken(struct TOKEN *token, int index){
    if (index==0) {
        struct TOKEN token_temp;
        token_temp.TOKEN_CLASS="None";
        token_temp.TOKEN_STRING="None";
        token_temp.TOKEN_START=0;
        token_temp.TOKEN_END=0;
        return token_temp;
    }
    else
        return token[index-1];
}
struct TOKEN TOKEN_nextToken(struct TOKEN *token, int index){
    int length=TL_length(token);
    if (index+1==length) {
        struct TOKEN token_temp;
        token_temp.TOKEN_CLASS="None";
        token_temp.TOKEN_STRING="None";
        token_temp.TOKEN_START=0;
        token_temp.TOKEN_END=0;
        return token_temp;
    }
    else
        return token[index+1];
}

void TL_addToken(struct TOKEN **token, struct TOKEN add_token){
    TL_addProperty(token, add_token.TOKEN_CLASS, add_token.TOKEN_STRING, add_token.TOKEN_START, add_token.TOKEN_END);
}
void TL_addTokenList(struct TOKEN **token, struct TOKEN *add_token_list){
    int length_of_add_token_list=TL_length(add_token_list);
    int i=1;
    for (; i<length_of_add_token_list; i++) {
        TL_addToken(token,add_token_list[i]);
    }
}

// num is the n th token that has required TOKEN_CLASS
// num starts from 0.
int TL_indexOfTokenAccordingTokenClassAndNum(struct TOKEN *token,char *token_class, int num){
    int length=TL_length(token);
    int i=0;
    int count=-1;
    for (i=1; i<length; i++) {
        if (strcmp(token[i].TOKEN_CLASS, token_class)==0) {
            count++;
            if (count==num) {
                return i;
            }
        }
    }
return -1;
}

char *TL_toString(struct TOKEN *token){
    int length=TL_length(token);
    int i=1;
    char *output="";
    for (; i<length; i++) {
        output=append(output, token[i].TOKEN_STRING);
    }
    return output;
}

struct TOKEN *TL_cleanTokenList(struct TOKEN **token_list){
    char *input_str=TL_toString(*token_list);
    return Walley_Lexica_Analysis(input_str);
}

//const char* W_PUNCTUATION;        : , ;
struct TOKEN *TL_returnTokenListWithoutPunctuation(struct TOKEN *token_list){
    struct TOKEN *output_token_list;
    TL_initTokenList(&output_token_list);
    int length=TL_length(token_list);
    int i=1;
    for (; i<length; i++) {
        if (strcmp(token_list[i].TOKEN_CLASS, "W_PUNCTUATION")!=0) {
            TL_addToken(&output_token_list, token_list[i]);
        }
    }
    return output_token_list;
}


char** TL_returnStringListWithoutPunctuation(struct TOKEN *token_list){
    char **output_str_list;
    Str_initStringList(&output_str_list);
    int length=TL_length(token_list);
    int i=1;
    char *append_str="";
    for (; i<length; i++) {
        if (strcmp(token_list[i].TOKEN_CLASS, "W_PUNCTUATION")!=0) {
            append_str=append(append_str, token_list[i].TOKEN_STRING);
        }
        else{
            Str_addString(&output_str_list, append_str);
            append_str="";
            
        }
    }
    Str_addString(&output_str_list, append_str);

    return output_str_list;
}


//####################################################################################
// TOKEN ARRAY is the Array that consists TOKEN LIST
struct TOKEN_ARRAY{
    int length;
    struct TOKEN **token_list;
};

void TA_init(struct TOKEN_ARRAY *token_array){
    (*token_array).length=1;
    (*token_array).token_list=(struct TOKEN **)malloc(sizeof(struct TOKEN *)*1);
    TL_initTokenList(&((*token_array).token_list[0]));
}

int TA_length(struct TOKEN_ARRAY token_array){
    return token_array.length;
}

void TA_addToken(struct TOKEN_ARRAY *token_array, struct TOKEN token){
    int length=TA_length(*token_array);
    TL_addToken(&((*token_array).token_list[length-1]), token);
}

void TA_addTokenList(struct TOKEN_ARRAY *token_array, struct TOKEN *token_list){
    (*token_array).length=(*token_array).length+1;
    (*token_array).token_list=(struct TOKEN **)realloc((*token_array).token_list, sizeof(struct TOKEN *)*(*token_array).length);
    TL_initTokenList(&(*token_array).token_list[(*token_array).length-1]);
    
    int length_of_token_list=TL_length(token_list);
    int i=0;
    for (; i<length_of_token_list; i++) {
        TA_addToken(token_array, token_list[i]);
    }
}

void TA_PrintTokenArray(struct TOKEN_ARRAY token_array){
    int length=TA_length(token_array);
    int i=0;
    for (; i<length; i++) {
        printf("%d =======\n",i);
        TL_PrintTOKEN(token_array.token_list[i]);
    }
}

void TA_initNewTokenList(struct TOKEN_ARRAY *token_array){
    (*token_array).length=(*token_array).length+1;
    (*token_array).token_list=(struct TOKEN **)realloc((*token_array).token_list, sizeof(struct TOKEN *)*(*token_array).length);
    TL_initTokenList(&(*token_array).token_list[(*token_array).length-1]);

}

//###################################################################################

//const char* W_PUNCTUATION;        : , ;
//     1,i+1,a[i]
//    token list 1 :1
//               2 :i+1
//               3 :a[i]
struct TOKEN_ARRAY TL_returnTokenArrayWithoutPunctuation(struct TOKEN *token_list){
    
    struct TOKEN_ARRAY output_token_array;
    TA_init(&output_token_array);
    
    int length=TL_length(token_list);
    int i=1;
    
    
    for (; i<length; i++) {
        if (strcmp(token_list[i].TOKEN_CLASS, "W_PUNCTUATION")!=0) {
            TA_addToken(&output_token_array, token_list[i]);
        }
        else{
            TA_initNewTokenList(&output_token_array);
        }
    }
    
    return output_token_array;
}


void Walley_Print_Error(char *input_str,char *error_message,int error_start_index){
    printf("Error.. %s\n",error_message);
    printf("%s\n",input_str);
    printf("%s^\n",Str_appendSpaceAhead("", error_start_index));
    exit(0);
}


