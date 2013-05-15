//
//  walley_calculation.h
//  Walley0.1
//
//  Created by shd101wyy on 13-4-26.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_function_data_type.h"

// 3 , 4 ,+ -----> 7
char *Walley_Calculation(char *value1, char *value2, char *sign){
    printf("value1 %s,  value2 %s,   sign %s\n",value1,value2,sign);
    
    // number calculation
    if (value1[0]!='"'&&value2[0]!='"') {
        double output_num=Walley_Operator(atof(value1), atof(value2), sign[0]);
        
        // int
        if (output_num==(int)output_num) {
            return intToCString(output_num);
        }
        
        // double
        return cleanDotZeroAfterNumAndKeepOneZero(numToCString(output_num));
    }
    
    
    // string or number calculation
    else{
        bool value1IsString=FALSE;
        bool value2IsString=FALSE;
        if(value1[0]=='"'){
            value1=substr(value1, 1, (int)strlen(value1)-1);
            value1IsString=TRUE;
        }
        if (value2[0]=='"') {
            value2=substr(value2, 1, (int)strlen(value2)-1);
            value2IsString=TRUE;
        }
        if (sign[0]=='+') {
            int malloc_length=(int)strlen(value1)+(int)strlen(value2);
            char *output_str=(char*)malloc(sizeof(char)*(malloc_length+1+2));
            strcpy(output_str, "\"");
            strcat(output_str, value1);
            strcat(output_str, value2);
            strcat(output_str, "\"");
            output_str[malloc_length+2]=0;
            return output_str;
        }
        else if (sign[0]=='*'){
            if (value1IsString && value2IsString) {
                printf("Error.. Can not multiply two string %s and %s\n",value1,value2);
                exit(0);
            }
            else{
                int num=0;
                char *mult_str;
                if (value1IsString) {
                    mult_str=value1;
                    num=atoi(value2);
                }
                else{
                    mult_str=value2;
                    num=atoi(value1);
                }
                
                int malloc_size=num*(int)strlen(mult_str);
                char *output_str=(char*)malloc(sizeof(char)*(malloc_size+1+2));
                int i=0;
                strcpy(output_str, "\"");
                for (; i<num; i++) {
                    strcat(output_str, mult_str);
                }
                strcat(output_str, "\"");
                output_str[malloc_size+2]=0;
                return output_str;
            }
        }
        else{
            printf("Error.. Sign %s can not be used for string calculation for %s and %s\n",sign,value1,value2);
            exit(0);
        }
    }
}


double Walley_Operator(double num1,double num2,char sign){
    double output=0;
    if (sign == '*') {
        output = num1*num2;
    } else if (sign == '/') {
        output = num1 / num2;
    } else if (sign == '\\') {
        output = num2 / num1;
    } else if (sign == '%'){
        output=((int)num1)%((int)num2);
    } else if (sign == '^'){
        output=pow(num1,num2);
    } else if (sign == '+') {
        output = num1 + num2;
    } else if (sign == '-') {
        output = num1-num2;
    } else {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("Mistakes Occurred while calling function Walley_Operator");
        output=0;
    }
    return output;
}


// 12.0---->12.0
// 13.60--->13.6
char *cleanDotZeroAfterNumAndKeepOneZero(char *num){
    int index_of_dot=-1;
    int i=0;
    for (; i<(int)strlen(num); i++) {
        if (num[i]=='.') {
            index_of_dot=i;
            break;
        }
    }
    if (index_of_dot==-1) {
        return num;
    }
    else{
        int length=(int)strlen(num);
        int i=length-1;
        int zero_that_need_to_delete=0;
        for (; i>0; i--) {
            if (num[i]=='0'&&num[i-1]!='.') {
                zero_that_need_to_delete++;
                continue;
            }
            if (num[i]!='0'||num[i]=='.') {
                break;
            }
        }
        if(zero_that_need_to_delete!=0){
            num=substr(num, 0, length-zero_that_need_to_delete);
        }
        if (num[(int)strlen(num)-1]=='.') {
            num=substr(num, 0, (int)strlen(num)-1);
        }
        return num;
    }
}
