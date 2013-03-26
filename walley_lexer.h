//
//  walley_lexical.h
//  Walley
//
//  Created by shd101wyy on 13-2-12.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_data.h"
/*
    m_operator-> add_sign
             | minus_sign
             | mult_sign
             | div_sign
             | mode_sign
             | pow_sign
 
    add_sign   -> '+'
    minus_sign -> '-'
    mult_sign  -> '*'
    div_sign   -> '/'
    mode_sign  -> '%'
    pow_sign   -> '**'
                | '^'
 
    punctuation -> ','
                | ';'
                | ':'
 
    dot -> '.'
 
 
    judge_sign -> '>'
                | '<'
                | '=='
                | '>='
                | '<='
                | '!='
 
    true_flase -> 'true'
                | 'false'
 
    relation ->  'and'
                |'or'
                |'not'
 
    l_annotation -> '#~'
    annotation   -> '#'
    r_annotation -> '~#'
 
    keyword  -> if_stat
     |switch_stat
     |for_stat
     |while_stat
     |def_stat
     |class_stat
 
     if_stat-> 'if'
     | 'elif'
     | 'else'
 
     switch_stat -> 'switch'
     | 'case'
     
     while_stat -> 'while'
     
     for_stat -> 'for'
     
     def_stat -> 'def'
     
     class_stat -> 'class'

 
    assignment_operator -> '='
 
 
 //   left_p     -> '('
 //   right_p    -> ')'
  //   left_fep   -> '{'   //function expression parenthesis
 //   right_fep  -> '}'
 
 
 // '[' then find ']' to
    make 'list_table'
 
     (     -> '('
     )    -> ')'
     [    -> '['
     ]   -> ']'
     {   -> '{'   //function expression parenthesis
     }  -> '}'

 
 
 
    double_quote -> "
    // no single quote available
 
    string       -> double_quote content double_quote

 
    num      -> int
              | double
 
    int      -> [0-9]+
    double   -> [0-9]+ '.' [0-9]+
 
    id       -> [a-zA-Z_][a-zA-Z0-9_]*

    white_space -> (' '|'\n'|'\t')+
 
    * can not be analyzed
 
 =============================================================================================================
 */











/*
bool is_id(char *input_str){
    int i=0;
    int length=(int)strlen(input_str);
    
    bool has_alpha=FALSE;
    
    // check whether has alpha
    for (; i<length; i++) {
        if (isalpha(input_str[0])) {
            has_alpha=TRUE;
            break;
        }
    }
    if (has_alpha==FALSE) {
        return FALSE;
    }
    
    // 2a is not allowed
    if (isdigit(input_str[0])) {
        return FALSE;
    }
    return TRUE;
}
*/
/*
char *Walley_Analyze_Token_Class(char *input_str){
    //  1  m_operator
    if (strcmp(input_str, "+")==0
        ||strcmp(input_str, "-")==0
        ||strcmp(input_str, "*")==0
        ||strcmp(input_str, "/")==0
        ||strcmp(input_str, "%")==0
        ||strcmp(input_str, "^")==0
        ||strcmp(input_str, "**")==0
        ) {
        return "m_operator";
    }
    
    //  2  punctuation
    if (strcmp(input_str, ",")==0
        ||strcmp(input_str, ";")==0
        ||strcmp(input_str, ":")==0
        ) {
        return "punctuation";
    }
    if (strcmp(input_str, ".")==0) {
        return "dot";
    }
    
    // 3 judge_sign
    if (strcmp(input_str, ">")==0
        ||strcmp(input_str, "<")==0
        ||strcmp(input_str, "==")==0
        ||strcmp(input_str, ">=")==0
        ||strcmp(input_str, "<=")==0
        ||strcmp(input_str, "!=")==0

        ) {
        return "judge_sign";
    }
    
    // 4 relation
    if (strcmp(input_str, "and")==0
        ||strcmp(input_str, "or")==0
        ||strcmp(input_str, "not")==0) {
        return "relation";
    }
    
    // 5 left_annotation
    if (strcmp(input_str, "#~")==0) {
        return "l_annotation";
    }
    

    // 6 right_annotation
    if (strcmp(input_str, "~#")==0) {
        return "r_annotation";
    }

    // 7 keyword
    if(strcmp(input_str, "if")==0
       ||strcmp(input_str, "elif")==0
       ||strcmp(input_str, "else")==0
       ||strcmp(input_str, "switch")==0
       ||strcmp(input_str, "case")==0
       ||strcmp(input_str, "for")==0
       ||strcmp(input_str, "while")==0
       ||strcmp(input_str, "def")==0
       ||strcmp(input_str, "class")==0
       ){
        return "keyword";
    }

    // 8 assignment
    if(strcmp(input_str, "=")==0)
        return "assignment_operator";

    

    // 9 annotation
    if(strcmp(input_str, "#")==0){
        return "annotation";
    }

    // 10 ()[]{}
    if(strcmp(input_str, "(")==0
       ||strcmp(input_str, ")")==0
       ||strcmp(input_str, "[")==0
       ||strcmp(input_str, "]")==0
       ||strcmp(input_str, "{")==0
       ||strcmp(input_str, "}")==0
       ){
        return input_str;
    }

    // 11 string
    if(input_str[0]=='"' && input_str[(int)strlen(input_str)-1]=='"'){
        return "string";
    }

    // 12 digit
    if(stringIsDigit(input_str))
        return "num";

    // 13 white_space
    int i=0;
    bool is_white_space=TRUE;
    for (i=0; i<(int)strlen(input_str); i++) {
            if(input_str[i]!=' '
               &&input_str[i]!='\n'
               &&input_str[i]!='\t'){
                is_white_space=FALSE;
                break;
            }
    }
    if(is_white_space){
        return "white_space";
    }

    // 14 id
    bool isid=is_id(input_str);
    if (isid) {
        return "id";
    }
    
    // 15 error
    printf("Can not analyze %s\n",input_str);
    exit(0);
}
*/
/*
    input_str : x=12
                0123
    start     :0
    
    then return index 2 as end
 
 
 */

bool match(char *input_str, int index, char *match_string){
    int length_of_input_str=(int)strlen(input_str);
    int length_of_match_str=(int)strlen(match_string);
    if (index+length_of_match_str>length_of_input_str) {
        return FALSE;
    }
    int i=0;
    bool match=TRUE;
    for (; i<length_of_match_str; i++) {
        if (input_str[index+i]!=match_string[i]) {
            match=FALSE;
            break;
        }
    }
    if (match==TRUE) {
        return TRUE;
    }
    else{
        return FALSE;
    }
}

// [0,1]
// 01234 return 4
int LIST_indexOfFinalBracket(char *input_str, int index_of_first_bracket){
    int count=0;
    int in_string=FALSE;
    int length_of_input_str=(int)strlen(input_str);
    int i=index_of_first_bracket;
    for (; i<length_of_input_str; i++) {
        if (in_string==FALSE && input_str[i]=='"' && input_str[i-1]!='\\') {
            in_string=TRUE;
            continue;
        }
        if (in_string==TRUE && input_str[i]=='"' && input_str[i-1]!='\\') {
            in_string=FALSE;
            continue;
        }
        
        if (in_string==FALSE) {
            if (input_str[i]=='[') {
                count++;
                continue;
            }
            if (input_str[i]==']') {
                count--;
                if (count==0) {
                    return i;
                }
                else{
                    continue;
                }
            }
        }

    }
    
    return -1;
}

char* Walley_Analyze_Token_Class(char *input_str, int i, int *end){
    int length=(int)strlen(input_str);
    //  1  m_operator
    if (match(input_str, i, "**")) {
        *end=i+2;
        return "m_operator";
    }
    if (match(input_str, i, "+")
        ||match(input_str, i, "-")
        ||match(input_str, i, "*")
        ||match(input_str, i, "/")
        ||match(input_str, i, "^")
        ||match(input_str, i, "%")
        ) {
        *end=i+1;
        return "m_operator";
    }
    
    
    
    
    //  2  punctuation
    if (match(input_str,i,",")
        ||match(input_str,i,";")
        ||match(input_str,i,":")
        ) {
        *end=i+1;
        return "punctuation";
    }
    
    
    // 3 judge_sign
    // 1) i<length-1
    if (
        match(input_str, i, "==")
        ||match(input_str, i, ">=")
        ||match(input_str, i, "<=")
        ||match(input_str, i, "!=")
        ) {
        *end=i+2;
        return "judge_sign";
    }
    if (input_str[i]=='>'
        ||input_str[i]=='<') {
        *end=i+1;
        return "judge_sign";
    }
    
    if (match(input_str, i, "true")) {
        *end=i+4;
        return "true_of_false";
    }
    if (match(input_str, i, "false")) {
        *end=i+5;
        return "true_of_false";
    }
    
    
    // 4 relation
    // 1) and | not
    if (match(input_str, i, "and")
        ||match(input_str, i, "not")
        ){
        *end=i+3;
        return "relation";
    }
    if (match(input_str, i, "or")) {
        *end=i+2;
        return "relation";
    }
    
    // 5 left_annotation
    if (i<=length-2&&(input_str[i]=='#'&&input_str[i+1]=='~')) {
        *end=i+2;
        return "l_annotation";
    }
    
    // 6 right_annotation
    if (i<=length-2&&(input_str[i]=='~'&&input_str[i+1]=='#')) {
        *end=i+2;
        return "r_annotation";
    }
    
    // 7 keyword
    // 1) if
    if (i<=length-2&&(input_str[i]=='i'&&input_str[i+1]=='f')) {
        *end=i+2;
        return "keyword";
    }
    // 2)for def
    if (match(input_str, i, "for")
        ||match(input_str, i,"def")) {
        *end=i+3;
        return "keyword";
    }
    // 3) elif else case
    if (match(input_str, i, "elif")
        ||match(input_str, i, "else")
        ||match(input_str, i, "case")) {
        *end=i+4;
        return "keyword";
    }
    
    // 4) while class
    if (match(input_str, i, "while")
        ||match(input_str, i, "class")) {
        *end=i+5;
        return "keyword";
    }
    
    // 5) switch
    if (match(input_str, i, "switch")) {
        *end=i+6;
        return "keyword";
    }
    
    // 8 assignment
    if(input_str[i]=='='){
        *end=i+1;
        return "assignment_operator";
    }

    
    // 9 annotation
    if(input_str[i]=='#'){
        *end=i+1;
        return "annotation";
    }

    // 10 ()[]{}
    if(input_str[i]=='('
       ||input_str[i]==')'
       ||input_str[i]=='{'
       ||input_str[i]=='}'
       ){
        *end=i+1;
        char *output=(char*)malloc(sizeof(char)*2);
        output[0]=input_str[i];
        output[1]=0;
        return output;
    }
    
    if (input_str[i]=='[') {
        int index_of_final=LIST_indexOfFinalBracket(input_str, i);
        if (index_of_final==-1) {
            Walley_Print_Error(input_str, "Can not find final ]", i);
        }
        *end=index_of_final+1;
        return "list_table";
    }
    
    // 11 string
    if(input_str[i]=='"'){
        int index_of_right_dq=indexOfFinalDoubleQuote(input_str, i);
        if (index_of_right_dq==-1) {
            printf("incomplete str\n");
            exit(0);
        }
        else{
            *end=index_of_right_dq+1;
            return "string";
        }
    }
    
    // 12 digit
    if (isdigit(input_str[i])) {
        int a=i+1;
        int find_dot=FALSE;
        for (; a<length; a++) {
            if (input_str[a]=='.' && find_dot==FALSE) {
                find_dot=TRUE;
                continue;
            }
            if (input_str[a]=='.' && find_dot==TRUE) {
                Walley_Print_Error(input_str, "invalide number", a);
            }
            if (!isdigit(input_str[a])) {
                break;
            }
        }
        
        if (a!=length&&isalpha(input_str[a])) {
            Walley_Print_Error(input_str, "Invalid Syntave", a);
        }
        
        *end=a;
        return "num";
    }
    
    // 13 white_space
    if (input_str[i]==' '
        ||input_str[i]=='\n'
        ||input_str[i]=='\t') {
        int a=i+1;
        for (; a<length; a++) {
            if (input_str[a]!=' '
                &&input_str[a]!='\n'
                &&input_str[a]!='\t') {
                break;
            }
        }
        *end=a;
        return "white_space";
    }
    
    // 14 id
    if (isalpha(input_str[i])||input_str[i]=='_') {
        int a=i+1;
        bool has_alpha=FALSE;
        if (isalpha(input_str[i])) {
            has_alpha=TRUE;
        }
        for (; a<length; a++) {
            if (isalpha(input_str[a])) {
                has_alpha=TRUE;
            }
            if (!isalpha(input_str[a])&&!isdigit(input_str[a])&&input_str[a]!='_') {
                break;
            }
        }
        
        if (has_alpha==TRUE) {
            *end=a;
            return "id";
        }

    }
  
    // 15 dot
    if (input_str[i]=='.') {
        int a=i+1;
        *end=a;
        return "dot";
    }
    
    // Error
    Walley_Print_Error(input_str, "Can not analyze this input", i);
    exit(0);
}


struct TL * Walley_Lexical_Analyzie(char *input_str){
    printf("Begin to Analyze %s\n",input_str);
    
    int i=0;
    int length=(int)strlen(input_str);
    Token_List *tl;
    TL_init(&tl);
    
    int end=0;
    
    for (; i<length; i++) {
        char *token_class=Walley_Analyze_Token_Class(input_str, i, &end);
        
        // delete white_space
        if (strcmp(token_class, "white_space")==0) {
            i=end-1;
            continue;
        }
        
        struct TOKEN temp_token;        
        temp_token.TOKEN_START=i;
        temp_token.TOKEN_END=end;
        temp_token.TOKEN_CLASS=token_class;
        
        char *token_string=(char*)malloc(sizeof(char)*(end-i+1));
        strcpy(token_string, "");
        int a=0;
        for (; a<end-i; a++) {
            token_string[a]=input_str[i+a];
        }
        token_string[a]=0;
        
        temp_token.TOKEN_STRING=token_string;
        
        TL_addToken(&tl, temp_token);
        i=end-1;
    }
    
    
    
    return tl;
}
































 