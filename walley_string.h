/* 
 * File:   walley_string.h
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 12:34 PM
 */

#include "walley_pre_functions.h"

char* replace_not_in_string(char* input_str, char* replace_str, char* with_str);
bool charIsInString(char *input_str, int char_index);
char *charToString(char input_char){
    char *output=(char*)malloc(sizeof(char)*2);
    output[0]=input_char;
    output[1]=0;
    return output;
}

char* substr(char* input_str, int from_index, int to_index) {
    if (from_index < 0){// || to_index > (int) strlen(input_str)) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        printf("\nMistake occurred while calling function substr\nPlease Check\n");
        printf("the input_str is %s from_index %d to_index %d\n\n",input_str,from_index,to_index);
        //return "\nMistake occurred while calling function substr\nPlease Check\n";
        exit(0);
    }
    else if (from_index>to_index){
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("\nMistake occurred while calling function substr\nPlease Check\n");
        printf("the input_str is %s from_index %d to_index %d\n\n",input_str,from_index,to_index);
        exit(1);
    }
    else if (from_index==to_index){
        //printf("RETURN NONE");
        return "";
    }
    else if (to_index-from_index==1){
        return charToString(input_str[from_index]);
    }
    else {
        //printf("\n\nFunction substr:\nThe input_str is %s\nthe from_index is %d\nthe to_index is %d\n", input_str, from_index, to_index);
        //if(to_index>(int)strlen(input_str))
        //    to_index=(int)strlen(input_str);
        int length = to_index - from_index;
        int i;
        char *output =(char*)malloc((length+1) * sizeof (char));
        strcpy(output, "");
        for (i = 0; i < length; i++) {
            output[i] = input_str[from_index + i];
        }
        output[length]=0;
        return output;

    }
}


char *append(char *input_str, char *append_str){
    //printf("$$ |%s| $$ |%s|\n",input_str,append_str);
    int length_of_input_str=(int)strlen(input_str);
    int length_of_append_str=(int)strlen(append_str);
    char *temp=(char*)malloc(sizeof(char)*(length_of_input_str+length_of_append_str+1));
    int i=0;
    for(i=0;i<length_of_input_str;i++){
        temp[i]=input_str[i];
    }
    for(i=0;i<length_of_append_str;i++){
        temp[i+length_of_input_str]=append_str[i];
    }
    
    // strlen problem 1
    //temp[(int)strlen(temp)]=0;
    temp[(length_of_input_str+length_of_append_str)]=0;
    
    /*
     // I delete the code below on Dec 25
    temp=substr(temp,0,length_of_input_str+length_of_append_str);
     */
    return temp;
}

int find(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0]) {
            //printf("Find The same\n");
            //char *temp = substr(from_str, i, i + (int) strlen(find_str));
            //printf("############%d\n",i);
            for (j = 0; j < (int) strlen(find_str); j++) {
                //printf("Find_Str[j] %c From_Str[i+j] %c\n",find_str[j],from_str[i+j]);
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    //printf("%d",index);
    return index;
}

// "Hello" find "l"--->3, find from behind
int find_from_behind(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    
    for (i = (int) strlen(from_str)-1; i >=0; i--) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0]) {
            //printf("Find The same\n");
            //char *temp = substr(from_str, i, i + (int) strlen(find_str));
            //printf("############%d\n",i);
            for (j = 0; j < (int) strlen(find_str); j++) {
                if (i+j==(int)strlen(from_str)) {
                    find_index=FALSE;
                    break;
                }
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    //printf("%d",index);
    return index;
}


int find_from_behind_from_index(char *from_str, char *find_str, int from_index) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    
    for (i = from_index; i >=0; i--) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0]) {
            //printf("Find The same\n");
            //char *temp = substr(from_str, i, i + (int) strlen(find_str));
            //printf("############%d\n",i);
            for (j = 0; j < (int) strlen(find_str); j++) {
                if (i+j==(int)strlen(from_str)) {
                    find_index=FALSE;
                    break;
                }
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    //printf("%d",index);
    return index;
}

// "Hello" find "l"--->3, find from behind
int find_from_behind_not_in_string(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    
    for (i = (int) strlen(from_str)-1; i >=0; i--) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInString(from_str, i)==FALSE) {
            //printf("Find The same\n");
            //char *temp = substr(from_str, i, i + (int) strlen(find_str));
            //printf("############%d\n",i);
            for (j = 0; j < (int) strlen(find_str); j++) {
                if (i+j==(int)strlen(from_str)) {
                    find_index=FALSE;
                    break;
                }
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    //printf("%d",index);
    return index;
}

int find_from_index_to_index(char *from_str, char *find_str, int from_index, int to_index) {
    if (from_index < 0 || to_index > (int) strlen(from_str)) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred which calling function find_from_index_to_index\n");
        printf("Try to find |%s| in |%s| from |%d| to |%d|\n",find_str,from_str,from_index,to_index);
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < to_index; i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0]) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}

int find_from_index(char *from_str, char *find_str, int from_index) {
    if (from_index < 0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred which calling function find_from_index");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < (int) strlen(from_str); i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0]) {
                //printf("%c==%c\n",from_str[i],find_str[0]);
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        //printf("%c!=%c\n",find_str[j],from_str[i+j]);
                        find_index = FALSE;
                        break;
                    }
                    //printf("|%c| == |%c| ",find_str[j],from_str[i+j]);
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    //printf("FIND INDEX\n");
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}

int find_to_index(char *from_str, char *find_str, int to_index) {
    if (to_index > (int) strlen(from_str)) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred which calling function find_to_index");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = 0; i < to_index; i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0]) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}

/*
char* replace(char* input_str, char* replace_str, char* with_str) {
    int i;
    char *input_str_copy=input_str;
    char output[1000] = "";
    for (i = 0; i < (int) strlen(input_str); i++) {
        if (input_str[i] == replace_str[0]) {
            printf("input_str is %s\ni is %d\ni+(int)strlen(replace_str) is %d\n", input_str, i, i + (int) strlen(replace_str));
            char *temp = substr(input_str_copy, i, i + (int) strlen(replace_str));
            printf("The length of input_str is %d", (int) strlen(input_str));
            printf("Find equal\n");
            printf("Temp is %s\nreplace_str is %s\n", temp, replace_str);
            printf("The length of temp is %d\n", (int) strlen(temp));
            if (strcmp(temp, replace_str) == 0) {
                printf("Find replace_str\n");
                strcat(output, replace_str);
                i = i + (int) strlen(replace_str) - 1;
            } else {
                output[(int) strlen(output)] = input_str[i];
            }
        } else {
            output[(int) strlen(output)] = input_str[i];
        }
    }
    char *output_str = output;
    return output_str;
}*/
char* replace(char* input_str, char* replace_str, char* with_str) {
    //printf("#### replace ####\n");
    int i;
    int j;

    //char *input_str_copy = input_str;
    char output[100000] = "";
    int length_of_input_str=(int)strlen(input_str);
    for (i = 0; i < length_of_input_str; i++) {
        if (input_str[i] == replace_str[0]) {
            bool is_equal = TRUE;
            for (j = 0; j < (int) strlen(replace_str); j++) {
                if (replace_str[j] != input_str[i + j]) {
                    is_equal = FALSE;
                    //printf("\nis_equal=FALSE\n");
                }
            }
            if (is_equal == TRUE) {
                //printf("Find replace_str\n");
                strcat(output, with_str);
                i = i + (int) strlen(replace_str) - 1;
            } else {
                output[(int) strlen(output)] = input_str[i];
            }
        } else {
            output[(int) strlen(output)] = input_str[i];
        }
    }
    //char *output_str = output;
    //printf("Output is %s\n",output);
    int length=(int)strlen(output);
    char *output_str=(char*)malloc(sizeof(char)*(length+1));
    //printf("%% %d %%\n",(int)strlen(output));
    int a=0;
    for(a=0;a<length;a++){
        output_str[a]=output[a];
    }
    output_str[length]=0;
    //output_str=substr(output_str,0,length);
    return output_str;
}
char* replace_from_index_to_index(char *input_str, char* replace_str, char* with_str, int from_index, int to_index){
    if (from_index>=to_index) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred while calling function replace_from_index_to_index\ninput_str %s\nreplace_str %s\nwith_str %s\nfrom_index %d to_index %d\n",input_str,replace_str,with_str,from_index,to_index);
        exit(0);
    }
    char *ahead;
    char *back;
    char *middle;
    if(from_index!=0)
        ahead=substr(input_str,0,from_index);
    else
        ahead="";
    if(to_index!=(int)strlen(input_str))
        back=substr(input_str,to_index,(int)strlen(input_str));
    else
        back="";
    middle=substr(input_str,from_index,to_index);
    //printf("middle %s\n, replace_str %s\n with_str %s\n",input_str,replace_str,with_str);
    middle=replace(middle,replace_str,with_str);
    
    char *output=append(ahead, middle);
    output=append(output, back);
    return output;
        
}

char* replace_from_index_to_index_not_in_string(char *input_str, char* replace_str, char* with_str, int from_index, int to_index){
    if (from_index>=to_index) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred while calling function replace_from_index_to_index_not_in_string\ninput_str %s\nreplace_str %s\nwith_str %s\nfrom_index %d to_index %d\n",input_str,replace_str,with_str,from_index,to_index);
        exit(0);
    }
    char *ahead;
    char *back;
    char *middle;
    if(from_index!=0)
        ahead=substr(input_str,0,from_index);
    else
        ahead="";
    if(to_index!=(int)strlen(input_str))
        back=substr(input_str,to_index,(int)strlen(input_str));
    else
        back="";
    middle=substr(input_str,from_index,to_index);
    //printf("middle %s\n, replace_str %s\n with_str %s\n",input_str,replace_str,with_str);
    middle=replace_not_in_string(middle,replace_str,with_str);
    
    char *output=append(ahead, middle);
    output=append(output, back);
    return output;
    
}
int count_str(char *input_str, char *count_str){
    int count=0;
    int i=0;
    int from=0;
    int length_of_input_str=(int)strlen(input_str);
    for(;i<length_of_input_str;i++){
        if(find_from_index(input_str,count_str,from)==-1)
            break;
        else{
            from=find_from_index(input_str,count_str,from)+1;
            count+=1;
        }
    }
    return count;
}



/*
 eg: charIsInString("'Hello'",2)----->TRUE
 * Very Important Function
 bool charIsInString(char *input_str, int char_index){
    char *temp=substr(input_str,0,char_index);
    //char *temp=substr(input_str,0,char_index+1);
    //char char_to_check=input_str[char_index];
    bool in_string=FALSE;
    if(find(temp,"\"")!=-1){
        if(count_str(temp,"\"")%2!=0){
            in_string=TRUE;
        } 
    }        
    if(find(temp,"'")!=-1){
       if (count_str(temp,"'")%2!=0){
            in_string=TRUE;
        }
    }
    //printf("Char is in string --->input_str : %s\n",input_str);
    return in_string;
}
 * The below is the newest version
 */
 bool charIsInString(char *input_str, int char_index){
    //char *temp=substr(input_str,0,char_index);
    //char *temp=substr(input_str,0,char_index+1);
    //char char_to_check=input_str[char_index];
     if(char_index>=(int)strlen(input_str)){
         printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred whiling calling function charIsInString\nOut of index, input_str %s with index %d\n",input_str,char_index);
         exit(0);
     }
    bool in_string=FALSE;
    bool find_double_quote=FALSE;
    bool find_single_quote=FALSE;
    int i=0;
    for(i=0;i<(int)strlen(input_str);i++){
        //printf("-->%c\n",input_str[i]);
        if(i==char_index){
            //printf("There %d\n",in_string);
                break;
        }
        if(find_double_quote==TRUE && input_str[i]=='"'){
            //printf("here\n");
            if (input_str[i-1]=='\\') {
                in_string=TRUE;
                continue;
            }
            
            find_double_quote=FALSE;
            in_string=FALSE;
            continue;
        }
        if(input_str[i]=='\''&&find_double_quote==FALSE&&find_single_quote==TRUE){
            if (input_str[i-1]=='\\') {
                in_string=TRUE;
                continue;
            }
            
            find_single_quote=FALSE;
            in_string=FALSE;
            continue;
        }
        
        if(input_str[i]=='"'&&find_double_quote==FALSE){
            find_double_quote=TRUE;
            in_string=TRUE;
            continue;
        }
        if(input_str[i]=='\''&&find_double_quote==FALSE&&find_single_quote==FALSE){
            find_single_quote=TRUE;
            in_string=TRUE;
            continue;
        } 
    }
    //printf("Char is in string --->input_str : %s\n",input_str);
     if(input_str[char_index]=='"'){
         if (char_index>=1 && input_str[char_index-1]!='\\') {
             in_string=FALSE;
         }
     }
     if(find_double_quote==FALSE && find_single_quote==TRUE){
         if ( char_index>=1 && input_str[char_index]=='\'') {
             in_string=FALSE;
         }
    }
    return in_string;
}
// change "heLlo" to "HELLO"

char *stringToUpperCase(char *input_str) {
    //printf("---->%s\n", input_str);
    int i = 0;
    int length = (int) strlen(input_str);
    //printf("length %d\n", length);
    char temp[10000] = "";
    for (i = 0; i < length; i++) {
        //printf("%c\n", input_str[i]);
        if (isalpha(input_str[i])  && charIsInString(input_str,i)==FALSE) {
            //if(input_str[i]>='a'&&input_str[i]<='z'){
            //printf("here %c\n", toupper(input_str[i]));
            temp[i] = toupper(input_str[i]);
        } else {
            temp[i] = input_str[i];
        }
    }
    int length_of_temp=(int)strlen(temp);
    char *output=(char*)malloc(sizeof(char)*(length_of_temp+1));
    for(i=0;i<length_of_temp;i++){
        output[i]=temp[i];
    }
    output[length_of_temp]=0;
    return output;
}
char *stringToLowerCase(char *input_str) {
    //printf("---->%s\n", input_str);
    int i = 0;
    int length = (int) strlen(input_str);
    //printf("length %d\n", length);
    char temp[10000] = "";
    for (i = 0; i < length; i++) {
        //printf("%c\n", input_str[i]);
        if (isalpha(input_str[i])  && charIsInString(input_str,i)==FALSE) {
            //if(input_str[i]>='a'&&input_str[i]<='z'){
            //printf("here %c\n", toupper(input_str[i]));
            temp[i] = tolower(input_str[i]);
        } else {
            temp[i] = input_str[i];
        }
    }
    char *output=(char*)malloc(sizeof(char)*((int)strlen(temp)+1));
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(temp)]=0;
    //printf("String to lower case----->%s\n", temp);
    return output;
}
/*
 
 * eg find_not_in_string("'hello',hello",he)--->9
 */

int find_not_in_string(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE) {
            //printf("Find The same\n");
            //printf("%c\n",from_str[i]);
            //char *temp = substr(from_str, i, i + (int) strlen(find_str));
            //printf("############%d\n",i);
            for (j = 0; j < (int) strlen(find_str); j++) {
                //printf("Find_Str[j] %c From_Str[i+j] %c\n",find_str[j],from_str[i+j]);
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    return index;
}



/*
 * eg replace_not_in_string("'Hello',Hello","Hello","a")---->"'Hello',a"
 */
char* replace_not_in_string(char* input_str, char* replace_str, char* with_str) {
    //printf("#### replace not in string ####\n");
    //printf("#### |%s|\n, replace|%s|\n, with|%s|\n, ####\n",input_str,replace_str,with_str);
    int i;
    int j;

    char output[10000]="";
    int length_of_input_str=(int)strlen(input_str);
    int length_of_with_str=(int)strlen(with_str);
    
    for (i = 0; i < length_of_input_str; i++) {
        //printf("WITH STR ----->|%s|, %d\n",with_str,(int)strlen(with_str));
        //printf("---->%c %c %d\n",input_str[i],replace_str[0],charIsInString(input_str,i));
        if (input_str[i] == replace_str[0] && charIsInString(input_str,i)==FALSE) {
            bool is_equal = TRUE;
            //printf("00000 Equal, %c\n",replace_str[0]);
            for (j = 0; j < (int) strlen(replace_str); j++) {
                if (replace_str[j] != input_str[i + j]) {
                    is_equal = FALSE;
                    //printf("\nis_equal=FALSE\n");
                }
            }
            if (is_equal == TRUE) {
                //printf("Find replace_str\n");
                //printf("input str %s\n",input_str);
                //if((int)strlen(with_str)!=0)
                with_str=substr(with_str,0,length_of_with_str);
                //printf("OUTPUT---->|%s|\n",output);
                //printf("with str-->|%s|\n",with_str);
                if(length_of_with_str!=0)
                    strcat(output, with_str);
                //printf("OUTPUT---->|%s|\n",output);
                //printf("input str %s\n",input_str);
                //printf("i is %d\n",i);
                i = i + (int) strlen(replace_str) - 1;
                
                //printf("i is %d\n",i);
            } else {
                output[(int) strlen(output)] = input_str[i];
            }
        } else {
            output[(int) strlen(output)] = input_str[i];
        }
        //printf("--->%c\n",input_str[i]);
    }
    //char *output_str = output;
    //printf("Output is %s\n",output);
    int length=(int)strlen(output);
    char *output_str=(char*)malloc(sizeof(char)*(length+1));
    //printf("%% %d %%\n",(int)strlen(output));
    int a=0;
    for(a=0;a<length;a++){
        output_str[a]=output[a];
    }
    output_str[length]=0;
    //output_str=substr(output_str,0,length);
    return output_str;
}

/*
 * eg replace_not_in_string_for_times("'Hello',Hello Hello","Hello","a",1)---->"'Hello',a,Hello"
 */
char* replace_not_in_string_for_times(char* input_str, char* replace_str, char* with_str, int time) {
    //printf("#### replace not in string ####\n");
    //printf("#### |%s|\n, replace|%s|\n, with|%s|\n, ####\n",input_str,replace_str,with_str);
    int i;
    int j;
    
    int count=0;

    char output[10000]="";
    int length_of_input_str=(int)strlen(input_str);
    int length_of_with_str=(int)strlen(with_str);
    
    for (i = 0; i < length_of_input_str; i++) {
        //printf("WITH STR ----->|%s|, %d\n",with_str,(int)strlen(with_str));
        //printf("---->%c %c %d\n",input_str[i],replace_str[0],charIsInString(input_str,i));
        if (input_str[i] == replace_str[0] && charIsInString(input_str,i)==FALSE && count<time) {
            bool is_equal = TRUE;
            //printf("00000 Equal, %c\n",replace_str[0]);
            for (j = 0; j < (int) strlen(replace_str); j++) {
                if (replace_str[j] != input_str[i + j]) {
                    is_equal = FALSE;
                    //printf("\nis_equal=FALSE\n");
                }
            }
            if (is_equal == TRUE) {
                count++;
                //printf("Find replace_str\n");
                //printf("input str %s\n",input_str);
                //if((int)strlen(with_str)!=0)
                with_str=substr(with_str,0,length_of_with_str);
                //printf("OUTPUT---->|%s|\n",output);
                //printf("with str-->|%s|\n",with_str);
                if(length_of_with_str!=0)
                    strcat(output, with_str);
                //printf("OUTPUT---->|%s|\n",output);
                //printf("input str %s\n",input_str);
                //printf("i is %d\n",i);
                i = i + (int) strlen(replace_str) - 1;
                
                //printf("i is %d\n",i);
            } else {
                output[(int) strlen(output)] = input_str[i];
            }
        } else {
            output[(int) strlen(output)] = input_str[i];
        }
        //printf("--->%c\n",input_str[i]);
    }
    //char *output_str = output;
    //printf("Output is %s\n",output);
    int length=(int)strlen(output);
    char *output_str=(char*)malloc(sizeof(char)*(length+1));
    //printf("%% %d %%\n",(int)strlen(output));
    int a=0;
    for(a=0;a<length;a++){
        output_str[a]=output[a];
    }
    output_str[length]=0;
    //output_str=substr(output_str,0,length);
    return output_str;
}

int find_from_index_not_in_string(char *from_str, char *find_str, int from_index) {
    if (from_index < 0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred which calling function find_from_index_not_in_string");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < (int) strlen(from_str); i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}

int count_str_not_in_string(char *input_str, char *count_str){
    int count=0;
    int i=0;
    int from=0;
    int length_of_input=(int)strlen(input_str);
    for(;i<length_of_input;i++){
        if(find_from_index_not_in_string(input_str,count_str,from)==-1)
            break;
        else{
            from=find_from_index_not_in_string(input_str,count_str,from)+1;
            count+=1;
        }
    }
    return count;
}

char *experiment(char *input_str){
    input_str=substr(input_str,0,2);
    printf("input_str %s\n",input_str);
    return "Hello";
}

char* removeBackSpace(char* input_message) {
    int length_of_input_message=(int)strlen(input_message);
    if (length_of_input_message!= 0) {
        int i = (int) strlen(input_message) - 1;
        char *output = input_message;
        if (output[i] == ' ') {
            for (; i >= 0; i--) {
                if (input_message[i] != ' ') {
                    output = substr(input_message, 0, i + 1);
                    break;
                }
            }
        }
        return output;
    } else {
        return "";
    }

}

char* removeAheadSpace(char* input_message) {
    //printf("Input Message is %s\n",input_message);
    if ((int) strlen(input_message) != 0) {
        int i = 0;
        char *output = input_message;
        if (input_message[0] == ' ') {
            for (; i < (int) strlen(input_message); i++) {
                if (input_message[i] != ' ') {
                    output = substr(input_message, i, (int) strlen(input_message));
                    break;
                }
            }
        }
        return output;
    } else {
        return "";
    }
}

/*
 * removeAheadSpaceForNum("  Hi",1)---->" Hi")
 */
char *removeAheadSpaceForNum(char* input_message, int remove_n_spaces) {
    if ((int) strlen(input_message) != 0) {
        int i = 0;
        int count = 0;
        char *output = input_message;
        for (; i < (int) strlen(input_message); i++) {
            if (input_message[i] == ' ') {
                count++;
            }
            if (count == remove_n_spaces) {
                output = substr(input_message, i + 1, (int) strlen(input_message));
                break;
            }
        }
        return output;
    } else {
        return "";
    }
}

char *trim(char *input_str){
    return removeAheadSpace(removeBackSpace(input_str));
}

bool stringIsDigit(char *input_str){
    input_str=trim(input_str);
    if(input_str[0]=='-')
        input_str=substr(input_str,1,(int)strlen(input_str));
    bool isDigit=TRUE;
    int i=0;
    if(input_str[0]=='.')
        i=1;
    int initial=i;
    
    for(;i<(int)strlen(input_str);i++){
        if(input_str[i]=='.'&&i!=initial&&i!=(int)strlen(input_str)-1){
            continue;
        }
        if(isdigit(input_str[i])==FALSE){
            isDigit=FALSE;
            break;
        }
    }
    
    int numberOfDot=count_str(input_str,".");
    if(numberOfDot>1)
        isDigit=FALSE;
    
    return isDigit;
}

bool stringIsFraction(char *input_str){
    int index_of_gang=find(input_str,"/");
    int string_is_digit=stringIsDigit(input_str);
    
    if (index_of_gang==-1) {
        return FALSE;
    }
    if (index_of_gang==-1 && string_is_digit==FALSE) {
        return FALSE;
    }
    if (index_of_gang!=-1) {
        char *numerator=substr(input_str, 0, index_of_gang);
        char *denominator=substr(input_str, index_of_gang+1, (int)strlen(input_str));
        
        if (stringIsDigit(numerator)==TRUE && stringIsDigit(denominator)==TRUE) {
            return TRUE;
        }
        else{
            return FALSE;
        }
        
    }
    return FALSE;
}

bool stringIsAlpha(char *input_str){
    input_str=trim(input_str);
    int i=0;
    int length=(int)strlen(input_str);
    bool is_alpha=TRUE;
    for (i=0; i<length; i++) {
        if (isalpha(input_str[i])==FALSE) {
            is_alpha=FALSE;
            break;
        }
    }
    return is_alpha;
}


// like a_b 
bool stringIsAlphaAndSlash(char *input_str){
    input_str=trim(input_str);
    int i=0;
    int length=(int)strlen(input_str);
    bool is_alpha=TRUE;
    for (i=0; i<length; i++) {
        if (isalpha(input_str[i])==FALSE && input_str[i]!='_') {
            is_alpha=FALSE;
            break;
        }
    }
    return is_alpha;
}


bool charIsInList(char *input_str,int index){
    char *check_str;
    if (input_str[index]=='[') {
        check_str=substr(input_str, 0, index);
    }
    else if (input_str[index]==']')
        check_str=substr(input_str, 0, index+1);
    else
        check_str=substr(input_str, 0, index+1);

    if(count_str_not_in_string(check_str, "[") != count_str_not_in_string(check_str, "]")){
        //printf("%c %d is in []\n",input_str[index],index);
        //printf("[ %d, ] %d\n",count_str_not_in_string(check_str, "["),count_str_not_in_string(check_str, "]"));
        return TRUE;
    }
    else{
        return FALSE;
    }
}


bool charIsInDictionary(char *input_str,int index){
    char *check_str;
    if (input_str[index]=='{') {
        check_str=substr(input_str, 0, index);
    }
    else if (input_str[index]=='}')
        check_str=substr(input_str, 0, index+1);
    else
        check_str=substr(input_str, 0, index+1);
    if(count_str_not_in_string(check_str, "{") != count_str_not_in_string(check_str, "}")){
        //printf("%c %d is in dictionary\n",input_str[index],index);
        //printf("RETURN TRUE\n");
        return TRUE;
    }
    else{
        //printf("RETURN FALSE\n");
        return FALSE;
    }
}

bool charIsInParenthesis(char *input_str, int index){
    char *check_str=substr(input_str, 0, index+1);
    if(count_str_not_in_string(check_str, "(") != count_str_not_in_string(check_str, ")")){
        //printf("%c %d is in dictionary\n",input_str[index],index);
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int find_not_in_str_list_dict(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE && charIsInDictionary(from_str, i)==FALSE && charIsInList(from_str, i)==FALSE) {
            //printf("Find The same\n");
            //printf("%c\n",from_str[i]);
            //char *temp = substr(from_str, i, i + (int) strlen(find_str));
            //printf("############%d\n",i);
            for (j = 0; j < (int) strlen(find_str); j++) {
                //printf("Find_Str[j] %c From_Str[i+j] %c\n",find_str[j],from_str[i+j]);
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    return index;
}
int find_from_index_not_in_str_list_dict(char *from_str, char *find_str, int from_index) {
    if (from_index < 0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred which calling function find_from_index_not_in_str_list_dict");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < (int) strlen(from_str); i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE && charIsInDictionary(from_str, i)==FALSE && charIsInList(from_str, i)==FALSE) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}
int find_from_index_not_in_str_list(char *from_str, char *find_str, int from_index) {
    if (from_index < 0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred which calling function find_from_index_not_in_str_list_dict");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < (int) strlen(from_str); i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE && charIsInList(from_str, i)==FALSE) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}

int find_from_behind_not_in_str_list_dict_parenthesis(char *from_str, char *find_str){
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    
    for (i = (int) strlen(from_str)-1; i >=0; i--) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInString(from_str, i)==FALSE && charIsInDictionary(from_str, i)==FALSE &&
            charIsInList(from_str, i)==FALSE && charIsInParenthesis(from_str, i)==FALSE) {
            //printf("Find The same\n");
            //char *temp = substr(from_str, i, i + (int) strlen(find_str));
            //printf("############%d\n",i);
            for (j = 0; j < (int) strlen(find_str); j++) {
                if (i+j==(int)strlen(from_str)) {
                    find_index=FALSE;
                    break;
                }
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    //printf("%d",index);
    return index;

}
int count_str_not_in_str_list_dict(char *input_str, char *count_str){
    int count=0;
    int i=0;
    int from=0;
    for(;i<(int)strlen(input_str);i++){
        if(find_from_index_not_in_str_list_dict(input_str,count_str,from)==-1)
            break;
        else{
            from=find_from_index_not_in_str_list_dict(input_str,count_str,from)+1;
            count+=1;
        }
    }
    return count;
}

int find_not_in_str_list_dict_parenthesis(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE && charIsInDictionary(from_str, i)==FALSE && charIsInList(from_str, i)==FALSE && charIsInParenthesis(from_str, i)==FALSE) {
            //printf("Find The same\n");
            //printf("%c\n",from_str[i]);
            //char *temp = substr(from_str, i, i + (int) strlen(find_str));
            //printf("############%d\n",i);
            for (j = 0; j < (int) strlen(find_str); j++) {
                //printf("Find_Str[j] %c From_Str[i+j] %c\n",find_str[j],from_str[i+j]);
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    return index;
}
int find_from_index_not_in_str_list_dict_parenthesis(char *from_str, char *find_str, int from_index) {
    if (from_index < 0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred which calling function find_from_index_not_in_str_list_dict");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < (int) strlen(from_str); i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE && charIsInDictionary(from_str, i)==FALSE && charIsInList(from_str, i)==FALSE && charIsInParenthesis(from_str, i)==FALSE) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}
int count_str_not_in_str_list_dict_parenthesis(char *input_str, char *count_str){
    int count=0;
    int i=0;
    int from=0;
    for(;i<(int)strlen(input_str);i++){
        if(find_from_index_not_in_str_list_dict_parenthesis(input_str,count_str,from)==-1)
            break;
        else{
            from=find_from_index_not_in_str_list_dict_parenthesis(input_str,count_str,from)+1;
            count+=1;
        }
    }
    return count;
}

char *intToCString(double num1){
    int num1_int=(int)num1;
    char temp[10000]="";
    sprintf(temp, "%d",num1_int);
    return append("", temp);
    
}

bool checkWhetherComplete(char *input_str){
    bool complete=TRUE;
    if(input_str[0]==input_str[(int)strlen(input_str)-1]||
       (input_str[0]=='['&&input_str[(int)strlen(input_str)-1]==']')||
       (input_str[0]=='{'&&input_str[(int)strlen(input_str)-1]=='}'))
        complete=TRUE;
    else
        complete=FALSE;
    return complete;
}


char *numToCString(double num){
    char temp[10000]="";
    sprintf(temp, "%f",num);
    return append("", temp);
}

char *stringReverse(char *input_str){
    int count=0;
    int length=(int)strlen(input_str);
    char *output=(char*)malloc((sizeof(char)*(length+1)));
    int i;
    for (i=length-1; i>=0; i--) {
        output[count]=input_str[i];
        count++;
    }
    output[length]=0;
    return output;
}

//             11
//   012345678901
//   sin(3*(4+5))        indexOfMostOutterBracket(sin(3*(4+5)),3)---->11
int indexOfMostOutterBracket(char *input_str, int index_of_left_bracket){
    int num_of_right_bracket=0;
    int i=index_of_left_bracket;
    int length=(int)strlen(input_str);
    int num_of_left_bracket=0;
    int index=-1;
    for (; i<length; i++) {
        if (input_str[i]=='(') {
            num_of_left_bracket++;
        }
        else if (input_str[i]==')') {
            num_of_right_bracket++;
        }
        if (num_of_left_bracket==num_of_right_bracket) {
            index=i;
            break;
        }
    }
    return index;
}

bool isSign(char sign){
    bool is_sign=FALSE;
    if(sign=='+'||
       sign=='-'||
       sign=='*'||
       sign=='/'||
       sign=='\\'||
       sign=='%'||
       sign=='^')
        is_sign=TRUE;
    return is_sign;
}
/*
 
 ==
 >=
 <=
 >
 <
 !=
 
 */
bool isJudgeSign(char *input_str, int index){
    int length=(int)strlen(input_str);
    if (index+1==length) {
        if (input_str[index]=='>'||input_str[index]=='<') {
            return TRUE;
        }
        else
            return FALSE;
    }
    else{
        if (input_str[index]=='='&&input_str[index+1]=='=') {
            return TRUE;
        }
        else if (input_str[index]=='>'&&input_str[index+1]=='=') {
            return TRUE;
        }
        else if (input_str[index]=='<'&&input_str[index+1]=='=') {
            return TRUE;
        }
        else if(input_str[index]=='>')
            return TRUE;
        else if(input_str[index]=='<')
            return TRUE;
        else if(input_str[index]=='!'&&input_str[index+1]=='=')
            return TRUE;
        else
            return FALSE;
    }
    return FALSE;
}

int indexOfMostOutterRectBracket(char *input_str, int index_of_left_bracket){
    int num_of_right_bracket=0;
    int i=index_of_left_bracket;
    int length=(int)strlen(input_str);
    int num_of_left_bracket=0;
    int index=-1;
    for (; i<length; i++) {
        if (input_str[i]=='[') {
            num_of_left_bracket++;
        }
        else if (input_str[i]==']') {
            num_of_right_bracket++;
        }
        if (num_of_left_bracket==num_of_right_bracket) {
            index=i;
            break;
        }
    }
    return index;
}

int indexOfMostOutterDictBracket(char *input_str, int index_of_left_bracket){
    int num_of_right_bracket=0;
    int i=index_of_left_bracket;
    int length=(int)strlen(input_str);
    int num_of_left_bracket=0;
    int index=-1;
    for (; i<length; i++) {
        if (input_str[i]=='{') {
            num_of_left_bracket++;
        }
        else if (input_str[i]=='}') {
            num_of_right_bracket++;
        }
        if (num_of_left_bracket==num_of_right_bracket) {
            index=i;
            break;
        }
    }
    return index;
}


bool findAlphaInString(char *input_str){
    int i=0;
    while (i<(int)strlen(input_str)) {
        if (isalpha(input_str[i])) {
            return TRUE;
        }
        
        i++;
    }
    return FALSE;
}

bool stringHasAlpha(char *input_str){
    bool has_alpha=FALSE;
    int i=0;
    for(;i<(int)strlen(input_str);i++){
        if(isalpha(input_str[i])){
            has_alpha=TRUE;
            break;
        }
    }
    return has_alpha;
}
char *Str_appendSpaceAhead(char *input_str, int num_of_space){
    int i=0;
    for (; i<num_of_space; i++) {
        input_str=append(input_str, " ");
    }
    return input_str;
    
}


/*
 * Init String List
 */

void Str_initStringList(char ***output){
    *output=(char**)malloc(sizeof(char*)*1);
    *output[0]="1";
}

void Str_PrintStr(char **input_str){
    printf("length is %s\n",input_str[0]);
    int length=atoi(input_str[0]);
    int i=1;
    while (i<length) {
        printf("%d-> %s\n",i,input_str[i]);
        i++;
    }
}
 
/*
 * This function is for function[] and tempfile[]....
 * replace __walley_function__.wy
 */

void Str_addString(char ***input_str_list,char *add_str){
    if (add_str==NULL) {
        printf("STR IS NULL\n");
        return;
    }
    int length=atoi((*input_str_list)[0]);
    length=length+1;
    (*input_str_list)[0]=intToCString(length);
    (*input_str_list)=(char**)realloc(*input_str_list, sizeof(char*)*(length));
    (*input_str_list)[length-1]=add_str;
}

int Str_length(char **input_str_list){
    return atoi(input_str_list[0]);

}


// init dynamic string
void d_string(char **input_str, char *copy_str){
    *input_str=(char*)malloc(sizeof(char)*((int)strlen(copy_str))+sizeof(char));
    
    strcpy(*input_str, copy_str);
}

// dynamic string concat
int d_strcat(char **buffer,char *addition)
{
    (*buffer) = (char*)realloc((*buffer),sizeof(char)*((int)strlen((*buffer)) + (int)strlen(addition) )+ sizeof(char));
    if (!(*buffer))
        return 0;
    strcat(*buffer, addition);
    return 1 ;
}
 

/*
 This function will remove \n behind input_str;
 */


char *removeNFromBack(char *input_str){
    while (input_str[(int)strlen(input_str)-1]=='\n') {
        if ((int)strlen(input_str)-1==0) {
            return "";
        }
        input_str=substr(input_str, 0,(int)strlen(input_str)-1);
    }
    return input_str;
}


bool stringIsEmpty(char *input_str){
    if (input_str==NULL) {
        return TRUE;
    }
    input_str=trim(input_str);
    input_str=removeNFromBack(input_str);
    int i=0;
    bool isEmpty=TRUE;
    for(; i<(int)strlen(input_str);i++){
        if(input_str[i]!=' ')
            isEmpty=FALSE;
    }
    if (strcmp("\n", input_str)==0) {
        isEmpty=TRUE;
    }
    //// printf("Input Str |%s|,length %d,isEmpty %d\n",input_str,(int)strlen(input_str),isEmpty);
    return isEmpty;
}


// a\nb\n
// 0:a
// 1:b
char **Str_stringToStringList(char *input_str){
    char **output_str_list;
    Str_initStringList(&output_str_list);
    int begin=0;
    int end=find_not_in_str_list_dict_parenthesis(input_str, "\\n");
    while (end!=-1) {
        char *str=substr(input_str, begin, end);
        if (stringIsEmpty(str)==FALSE) {
            Str_addString(&output_str_list, str);
        }
        begin=end+1;
        end=find_from_index_not_in_str_list_dict_parenthesis(input_str, "\\n",begin);
    }
    char *str=substr(input_str, begin, (int)strlen(input_str));
    if (stringIsEmpty(str)==FALSE) {
        Str_addString(&output_str_list, str);
    }
    return output_str_list;
}


// according to \\n and \n
char **changeStringToStringList(char *input_str){
    char **output_list;
    Str_initStringList(&output_list);
    int i=0;
    int length=(int)strlen(input_str);
    int start=0;
    for (; i<length-1; i++) {
        if (input_str[i]=='\n') {
            char *temp_string=substr(input_str, start, i);
            start=i+1;
            if (stringIsEmpty(temp_string)==FALSE) {
                Str_addString(&output_list, temp_string);
            }
        }
        if (input_str[i]=='\\'&&input_str[i+1]=='n') {
            char *temp_string=substr(input_str, start, i);
            start=i+2;
            if (stringIsEmpty(temp_string)==FALSE) {
                Str_addString(&output_list, temp_string);
            }
        }
    }
    
    char *final_string=substr(input_str, start, (int)strlen(input_str));
    if (stringIsEmpty(final_string)==FALSE) {
        Str_addString(&output_list, final_string);
    }
    return output_list;
}


/*
================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================================ LINKED LIST =============================================================================================================
 
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
















