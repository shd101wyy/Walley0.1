//
//  walley_data.h
//  CPractice
//
//  Created by shd101wyy on 12-10-17.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include "walley_lexical.h"

struct VAR{
    char *var_name;
    char *var_value;
    char *var_type;
};

void Var_PrintVar(struct VAR *struct_var){
    int row=0;
    int length=0;
    if (strcmp((struct_var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_PrintVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((struct_var)->var_value);
    }
    while (row<length) {
        printf("%s:%s:%s:\n",struct_var[row].var_name,struct_var[row].var_value,struct_var[row].var_type);
        row++;
    }
}

void Var_initVar(struct VAR **var){
    *var=(struct VAR*)malloc(sizeof(struct VAR)*1);
    (*var)->var_name="__size_of_array__";
    (*var)->var_value="1";
    (*var)->var_type="int";
}
void Var_addProperty(struct VAR **var,char *var_name, char *var_value, char *var_type){
    
    int length=0;
    if (strcmp((*var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_addProperty..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*var)->var_value);
    }
    
    (*var)->var_value=intToCString(1+atoi((*var)->var_value));
    
    *var=(struct VAR*)realloc(*var, sizeof(struct VAR)*(length+1));
    (*var+length)->var_name=var_name;
    (*var+length)->var_type=var_type;
    (*var+length)->var_value=var_value;    
}
int Var_Existed(struct VAR var[], char *var_name){
    int existed=0;
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_Existed..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((var)->var_value);
    }

    while (i<length) {
    
        if (strcmp(var[i].var_name,var_name)==0) {
            existed=1;
            break;
        }
        i=i+1;
    }
    return existed;
}

void Var_removeVar(struct VAR **var, char *remove_var_name){
    
    
    int length=0;
    if (strcmp((*var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_removeVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*var)->var_value);
    }
    
    
    int i=0;
    int find_var=0;
    int remove_num=0;
    bool is_deleting_list_or_dict=FALSE;
    
    
    char *delete_var_type="";
    char *delete_var_name="";
    
    
    while (i<length) {
        if (find_var==1) {
            if(is_deleting_list_or_dict==TRUE&&strcmp(delete_var_type, "list")==0){
                char *temp_var_name=(*var+i)->var_name;
                int index_of=find(temp_var_name,"[");
                if(index_of!=-1){
                    char *ahead=substr(temp_var_name, 0, index_of);
                    if (strcmp(ahead, delete_var_name)==0) {
                        remove_num+=1;
                        (*var+i)->var_name=NULL;
                        (*var+i)->var_value=NULL;
                        (*var+i)->var_type=NULL;
                        i++;
                        continue;
                    }
                    else{
                        is_deleting_list_or_dict=FALSE;
                    }
                }
                else{
                    is_deleting_list_or_dict=FALSE;
                }
            }
            else if(is_deleting_list_or_dict==TRUE && strcmp(delete_var_type, "dictionary")==0){
                char *temp_var_name=(*var+i)->var_name;
                int index_of=find(temp_var_name,"{");
                if(index_of!=-1){
                    char *ahead=substr(temp_var_name, 0, index_of);
                    if (strcmp(ahead, delete_var_name)==0) {
                        remove_num+=1;
                        (*var+i)->var_name=NULL;
                        (*var+i)->var_value=NULL;
                        (*var+i)->var_type=NULL;
                        i++;
                        continue;
                    }
                    else{
                        is_deleting_list_or_dict=FALSE;
                    }
                }
                else{
                    is_deleting_list_or_dict=FALSE;
                }
            }
            else{
                is_deleting_list_or_dict=FALSE;
            }
            
            if(is_deleting_list_or_dict==FALSE){
            
                (*var+i-remove_num)->var_name=(*var+i)->var_name;
                (*var+i-remove_num)->var_type=(*var+i)->var_type;
                (*var+i-remove_num)->var_value=(*var+i)->var_value;
                i++;
            }
            continue;
            
            
        }
        if (strcmp((*var+i)->var_name,remove_var_name)==0) {
            find_var=1;
            remove_num+=1;
            if (strcmp((*var+i)->var_type, "dictionary")==0||strcmp((*var+i)->var_type, "list")==0) {
                is_deleting_list_or_dict=TRUE;
                delete_var_name=(*var+i)->var_name;
                delete_var_type=(*var+i)->var_type;
            }
        }
        i=i+1;
    }
    if (find_var==1) {
       
        //(*var+length-remove_num)->var_name=NULL;
        //(*var+length-remove_num)->var_type=NULL;
        //(*var+length-remove_num)->var_value=NULL;
        int a=length-remove_num;
        for (; a<length; a++) {
            (*var+a)->var_name=NULL;
            (*var+a)->var_type=NULL;
            (*var+a)->var_value=NULL;
        }
        *var=(struct VAR*)realloc(*var, sizeof(struct VAR)*(length-remove_num));
        (*var)->var_value=intToCString(atoi((*var)->var_value)-remove_num);
    }
       
}

void Var_changeValueOfVar(struct VAR **var, char *var_name, char *var_value, char *var_type){
    int i=0;
    int length=0;
    if (strcmp((*var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*var)->var_value);
    }
    
    while (i<length) {
        if (strcmp((*var+i)->var_name,var_name)==0) {
            (*var+i)->var_value=var_value;
            (*var+i)->var_type=var_type;
            break;
        }
        i=i+1;
    }
}

char *Var_getValueOfVar(struct VAR *var, char *var_name){
    
    if (strcmp(var_name, "None")==0) {
        return "None";
    }
    
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_getValueOfVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((var)->var_value);
    }
    
    while (i<length) {
        if (strcmp(var[i].var_name,var_name)==0) {
            return var[i].var_value;
        }
        i=i+1;
    }

    
    
    printf("Undefined var |%s|\n",var_name);
    exit(0);
    return var_name;
}


int Var_length(struct VAR *struct_var){
    
    int length=0;
    if (strcmp((struct_var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("Var_getValueOfVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((struct_var)->var_value);
    }
    return length;
    

}


//=====================================================

struct IF{
    char **if_elif_else;
    char ***content;
};

void IF_PrintIf(struct IF If_elif_else,int length_of_content){
    Str_PrintStr(If_elif_else.if_elif_else);
    int i=0;
    for (; i<length_of_content; i++) {
        Str_PrintStr(If_elif_else.content[i]);
    }
}

//======================================================

struct CLASS{
    char *class_name;
    char *class_mother_name;  //extend class
    char *string_in_class;
};
void CLASS_initCLASSList(struct CLASS **var){
    *var=(struct CLASS*)malloc(sizeof(struct CLASS)*1);
    (*var)->class_name="__size_of_array__";
    (*var)->string_in_class="1";
}
int CLASS_Length(struct CLASS *class_list){
    
    int length=0;
    if (strcmp((class_list)->class_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("CLASS_Length..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((class_list)->string_in_class);
    }
    return length;
}

void CLASS_addProperty(struct CLASS **class_list,char *class_name, char *class_mother_name, char *string_in_class){
    
    int length=CLASS_Length(*class_list);
    (*class_list)->string_in_class=intToCString(1+atoi((*class_list)->string_in_class));
    
    *class_list=(struct CLASS*)realloc(*class_list, sizeof(struct CLASS)*(length+1));
    (*class_list+length)->class_name=class_name;
    (*class_list+length)->class_mother_name=class_mother_name;
    (*class_list+length)->string_in_class=string_in_class;
}


void CLASS_PrintCLASS(struct CLASS *class_list){
    int row=1;
    int length=CLASS_Length(class_list);
    while (row<length) {
        printf("class: %s\nextend: %s\nstring: %s\n\n",class_list[row].class_name,class_list[row].class_mother_name,class_list[row].string_in_class);
        row++;
    }
}

char *CLASS_classMother(struct CLASS *class_list,char *class_name){
    int length=CLASS_Length(class_list);
    int row=1;
    while (row<length) {
        if (strcmp(class_name, class_list[row].class_name)==0) {
            return class_list[row].class_mother_name;
        }
        
        row++;
    }
    printf("Error.. Can not find required class_name %s\n",class_name);
    exit(0);
}

char *CLASS_stringInClass(struct CLASS *class_list,char *class_name){
    int length=CLASS_Length(class_list);
    int row=1;
    while (row<length) {
        if (strcmp(class_name, class_list[row].class_name)==0) {
            return class_list[row].string_in_class;
        }
        
        row++;
    }
    printf("Error.. Can not find required string_in_class %s\n",class_name);
    exit(0);
}
//==============================================================================
//===================== Math Data ==============================================

// coefficient
// value
// power

// 3*x^3
// coefficient 3
// value x
// power 3

// 9
// coefficient 9
// value 0       // 0 means it is number not symbol
// power 1


struct Math_Data{
    char *coefficient;
    char *value;
    char *power;
};


struct Math_Data_List{
    int length;
    struct Math_Data *math_data_list;
};


// MDL IS MATH DATA LIST
void MDL_init(struct Math_Data_List *mdl){
    (*mdl).length=0;
    (*mdl).math_data_list=(struct Math_Data*)malloc(sizeof(struct Math_Data)*1);
}

void MDL_addProperty(struct Math_Data_List *mdl,char *coefficient, char *value, char *power){
    int length=(*mdl).length;
    if (length==0) {
        (*mdl).math_data_list[0].coefficient=coefficient;
        (*mdl).math_data_list[0].value=value;
        (*mdl).math_data_list[0].power=power;
        (*mdl).length=1;
    }
    else{
        (*mdl).length=length+1;
        length=length+1;
        (*mdl).math_data_list=(struct Math_Data*)realloc((*mdl).math_data_list, sizeof(struct Math_Data)*length);
        (*mdl).math_data_list[length-1].coefficient=coefficient;
        (*mdl).math_data_list[length-1].value=value;
        (*mdl).math_data_list[length-1].power=power;
    }
}

void MDL_addMathData(struct Math_Data_List *mdl, struct Math_Data math_data){
    MDL_addProperty(mdl, math_data.coefficient, math_data.value, math_data.power);
}


void MDL_PrintMathDataList(struct Math_Data_List mdl){
    int length=mdl.length;
    int i=0;
    for (;i<length;i++) {
        printf("%d -> %s:%s:%s\n",i,mdl.math_data_list[i].coefficient,mdl.math_data_list[i].value,mdl.math_data_list[i].power);
    }
}

// MDA is MDL Array
struct Math_Data_Array{
    int length;
    struct Math_Data_List *mdl;
};
void MDA_init(struct Math_Data_Array *mda){
    (*mda).length=0;
    (*mda).mdl=(struct Math_Data_List*)malloc(sizeof(struct Math_Data_List)*1);
    MDL_init(&((*mda).mdl[0]));
}

void MDA_addMathDataList(struct Math_Data_Array *mda, struct Math_Data_List mdl){
    int length=(*mda).length;
    if (length==0) {
        (*mda).length=1;
        (*mda).mdl[0]=mdl;
    }
    else{
        (*mda).length=(*mda).length+1;
        (*mda).mdl=(struct Math_Data_List*)realloc((*mda).mdl, sizeof(struct Math_Data_List)*((*mda).length));
        (*mda).mdl[(*mda).length-1]=mdl;
    }
}

struct Math_Data_List MDA_pop(struct Math_Data_Array *mda){
    int length=(*mda).length;
    (*mda).length=length-1;
    struct Math_Data_List return_mdl=(*mda).mdl[length-1];
    (*mda).mdl=(struct Math_Data_List*)realloc((*mda).mdl, sizeof(struct Math_Data_List)*((*mda).length));
    
    return return_mdl;
}

char *MDL_changeMathDataListToString(struct Math_Data_List mdl){
    char *output_str="";
    int length=mdl.length;
    int i=0;
    for (;i<length ; i++) {
        struct Math_Data left_md=mdl.math_data_list[i];
        int j=i;
        int smallest_md_index=i;
        char *smallest_string=left_md.value;
        for (; j<length; j++) {
            if (strcmp(smallest_string, mdl.math_data_list[j].value)>0) {
                smallest_string=mdl.math_data_list[j].value;
                smallest_md_index=j;
            }
        }
        
        // swap
        mdl.math_data_list[i]=mdl.math_data_list[smallest_md_index];
        mdl.math_data_list[smallest_md_index]=left_md;
    }
    
    //printf("Finishing Sorting\n");
    //MDL_PrintMathDataList(mdl);
    
    i=0;
    for(i=0;i<length;i++){
        char *coef=mdl.math_data_list[i].coefficient;
        char *value=mdl.math_data_list[i].value;
        char *power=mdl.math_data_list[i].power;
        if(strcmp(value,"0")==0){
            if (strcmp(coef, "0")!=0) {
                output_str=append(output_str, coef);
                if(strcmp(power, "1")!=0){
                    if(stringIsDigit(power)){
                        output_str=append(output_str, append("^", power));
                    }
                    else{
                        output_str=append(output_str, append("^(", append(power,")")));
                    }
                    
                }

            }
            continue;
        }
        else{
            if(strcmp(coef, "1")!=0){
                if(strcmp(coef, "-1")==0){
                    output_str=append(output_str, "-");
                }
                else{
                    output_str=append(output_str, append(coef,"*"));
                }
            }
            output_str=append(output_str, value);
            if(strcmp(power, "1")!=0){
                if(stringIsDigit(power)){
                    output_str=append(output_str, append("^", power));
                }
                else{
                    output_str=append(output_str, append("^(", append(power,")")));
                }
            }
        }
        if(i!=length-1)
            output_str=append(output_str, "+");
    }
    output_str=replace(output_str, "+-", "-");
    //printf("OUTPUT_STR-----> %s\n",output_str);
    return output_str;
}


//==============================================================================================
void Walley_Tool_get_TO_RUN_From_File(char *file_name){
    FILE *fp;
    char arr[10000]="";

    Str_List *str_list;
    SL_initSL(&str_list);
    
    
    
    if ((fp = fopen(file_name, "r")) == NULL) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        perror("File open error!\n");
        exit(1);
    }    
    while ((fgets(arr, 10000, fp)) != NULL) {
        if (stringIsEmpty(arr)) {
            continue;
        }
        char *arr_arr=removeNFromBack(arr);
        SL_addString(&str_list, arr_arr);
    }
        
    printf("================ COPY TO_RUN ==============\n");
    char *output_str="char *TO_RUN[]={\n";
    int i=0;
    int length=SL_length(str_list);
    
    Str_List **current_sl=&(str_list);
    
    for (i=0; i<length; i++) {
        (*current_sl)->string_content=replace((*current_sl)->string_content, "\"", "\\\"");
        output_str=append(output_str,append("\"", append((*current_sl)->string_content, "\"")));
        if (i+1!=length) {
            output_str=append(output_str, ",\n");
        }
        current_sl=&((*current_sl)->next);
    }
    output_str=append(output_str, "\n};");
    printf("%s\n",output_str);
    fclose(fp);
}

char *TO_RUN[]={
    "178",
    "def matrix_num(row=1,col):",
    "    x=[] ",
    "    y=[]",
    "    i=0",
    "    j=0",
    "    while i<row:",
    "        y=[]",
    "        j=0",
    "        while j<col:",
    "            y.append(0)",
    "            j=j+1",
    "        x.append(y)",
    "        i=i+1",
    "    return x",
    "#end define matrix",
    "# matrix_str(\"[1,2;3,4]\")",
    "def matrix_str(mat):",
    "    output=\"[\"",
    "    i=0",
    "    length=mat.length()",
    "    while i<length:",
    "        if mat[i]==';':",
    "            output=output+'],['",
    "        else:",
    "            output=output+mat[i]",
    "        i=i+1",
    "    output=output+\"]\"",
    "    return nstr(output)",
    "def matrix(param1,param2):",
    "    if type(param1)=='int':",
    "        return matrix_num(param1,param2)",
    "    else:",
    "        return matrix_str(param1)",
    "def matrix_add(mat1,mat2):",
    "    output=mat1",
    "    for i in range(output.length()):",
    "        for j in range(output[0].length()):",
    "            output[i][j]=output[i][j]+mat2[i][j]",
    "    return output",
    "def matrix_minus(mat1,mat2):",
    "    output=mat1",
    "    for i in range(output.length()):",
    "        for j in range(output[0].length()):",
    "            output[i][j]=output[i][j]-mat2[i][j]",
    "    return output",
    "def matrix_mult(mat1,mat2):",
    "    mat1_row=mat1.length()",
    "    mat2_col=mat2[0].length()",
    "    r_row=mat1_row",
    "    r_col=mat2_col",
    "    output=matrix(r_row,r_col)",
    "    for i in range(r_row):",
    "        for j in range(r_col):",
    "            for k in range(mat1[0].length()):",
    "                output[i][j]=output[i][j]+mat1[i][k]*mat2[k][j]",
    "    return output",
    "def matrix_dot_mult(mat1,mat2):",
    "    mat1_row=mat1.length()",
    "    mat1_col=mat1[0].length()",
    "    output=matrix(mat1_row,mat1_col)",
    "    for i in range(mat1_row):",
    "        for j in range(mat1_col):",
    "            output[i][j]=mat1[i][j]*mat2[i][j]",
    "    return output",
    "def matrix_transpose(mat1):",
    "    exp:",
    "        {mat1 transpose}",
    "    row=mat1.length()",
    "    col=mat1[0].length()",
    "    output=matrix(col,row)",
    "    for i in range(row):",
    "        for j in range(col):",
    "            output[j][i]=mat1[i][j]",
    "    return output",
    "# 2 by 2 matrix det",
    "def matrix_2_2_det(mat):    ",
    "    return mat[0][0]*mat[1][1]-mat[0][1]*mat[1][0]",
    "def matrix_det(mat):",
    "    row=len(mat)",
    "    col=len(mat[0])",
    "    if row!=col:",
    "        print \"Row != Col\"",
    "    if row==2:",
    "        return matrix_2_2_det(mat)",
    "    output=0",
    "    for j in range(col):",
    "        coeff=1",
    "        if j%2==0:",
    "            coeff=1",
    "        else:",
    "            coeff=-1",
    "        temp_mat=matrix(row-1,row-1)",
    "        temp_row_num=0",
    "        temp_col_num=0",
    "        for a in range(row):",
    "            if a==0:",
    "                continue",
    "            temp_col_num=0",
    "            for b in range(col):",
    "                if b==j:",
    "                    continue",
    "                temp_mat[temp_row_num][temp_col_num]=mat[a][b]",
    "                temp_col_num=temp_col_num+1",
    "            temp_row_num=temp_row_num+1",
    "        x=matrix_det(temp_mat)",
    "        output=output+coeff*x*mat[0][j]",
    "    return output",
    "def matrix_LU_U(mat):",
    "    for i in range(len(mat)-1):",
    "        for a in range(len(mat)-1):",
    "            row=a+i+1",
    "            pivot=mat[row][i]",
    "            for j in range(len(mat[0])):",
    "                mat[row][j]=mat[row][j]-mat[i][j]/mat[i][i]*pivot",
    "    return mat",
    "def matrix_LU_L(mat):",
    "    temp_mat=matrix(len(mat),len(mat[0]))",
    "    temp_mat[0][0]=1",
    "    for i in range(len(mat)):",
    "        temp_mat[i][i]=1",
    "    for i in range(len(mat)-1):",
    "        for a in range(len(mat)-1):",
    "            row=a+i+1",
    "            pivot=mat[row][i]",
    "            temp_mat[row][i]=1/mat[i][i]*pivot",
    "    return temp_mat                    ",
    "def matrix_print(mat):",
    "    println mat",
    "    for i in range(len(mat)):",
    "        print \"[\"",
    "        for j in range(len(mat[0])):",
    "            print mat[i][j]",
    "            print \" \"    ",
    "        println \"]\"",
    "def matrix_eye(num1,num2=\"None\"):",
    "    if num2==\"None\":",
    "        output=matrix(num1,num1)",
    "    else:",
    "        output=matrix(num1,num2)",
    "    if num1<num2:",
    "        for i in range(num1):",
    "            output[i][i]=1",
    "    else:",
    "        for i in range(num2):",
    "            output[i][i]=1",
    "    return output",
    "#end define matrix",
    "def matrix_inverse(mat):",
    "    temp_mat=matrix(len(mat),len(mat[0]))",
    "    for i in range(len(mat)):",
    "        temp_mat[i][i]=1",
    "    for i in range(len(mat)-1):",
    "        for a in range(len(mat)-1):",
    "            row=a+i+1",
    "            pivot=mat[row][i]",
    "            for j in range(len(mat[0])):",
    "                mat[row][j]=mat[row][j]-mat[i][j]/mat[i][i]*pivot",
    "                temp_mat[row][j]=temp_mat[row][j]-temp_mat[i][j]/mat[i][i]*pivot",
    "    for i in range(len(mat)-1):",
    "        i=len(mat)-i-1",
    "        pivot=mat[i][i]",
    "        for a in range(i):",
    "            temp=mat[a][i]",
    "            for j in range(len(mat[0])):",
    "                temp_mat[a][j]=temp_mat[a][j]-(temp_mat[i][j]/pivot)*temp",
    "                mat[a][j]=mat[a][j]-(mat[i][j]/pivot)*temp",
    "    for i in range(len(mat)):",
    "        for j in range(len(mat[0])):",
    "            temp_mat[i][j]=temp_mat[i][j]/mat[i][i]",
    "    return temp_mat",
    "def matrix_lu(mat):",
    "    l=matrix_LU_L(mat)",
    "    u=matrix_LU_U(mat)",
    "    output=[]",
    "    output.append(l)",
    "    output.append(u)",
    "    return output"
};

