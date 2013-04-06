//
//  walley_var.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_parser.h"

// eg var_name :a  address :0
//    then found value of a at address 0
struct Var{
    char *var_name;
    int address;
};

struct Var_List{
    Var current_var;
    struct Var_List *next;
};

void VL_init(Var_List **vl){
    (*vl)=(Var_List *)malloc(sizeof(Var_List)*1);
    (*vl)->next=NULL;
    (*vl)->current_var.var_name=NULL;
    (*vl)->current_var.address=-1;
}

void VL_addVar(Var_List **vl, Var add_var){

    
    if ((*vl)->current_var.var_name==NULL) {
        (*vl)->current_var=add_var;
    }
    else{
        Var_List **current_vl=&(*vl);
        while ((*current_vl)->next!=NULL) {
            current_vl=&((*current_vl)->next);
        }
        Var_List *temp_vl;
        VL_init(&temp_vl);
        temp_vl->current_var=add_var;
        (*current_vl)->next=temp_vl;
    }
}

void VL_addVarAccordingToVarNameAndAddress(Var_List **vl, char *var_name, int address){
    Var add_var;
    add_var.var_name=var_name;
    add_var.address=address;
    VL_addVar(vl, add_var);
}

int VL_address(Var_List *vl, char *var_name){
    while (vl->next!=NULL) {
        if (strcmp(vl->current_var.var_name, var_name)==0) {
            return vl->current_var.address;
        }
        vl=vl->next;
    }
    if (vl->current_var.var_name==NULL) {
        return -1;
    }
    if (strcmp(vl->current_var.var_name, var_name)==0) {
        return vl->current_var.address;
    }
    //does not find
    return -1;
}

void VL_printVL(Var_List *vl){
    while (vl->next!=NULL) {
        printf("%s  %d\n",vl->current_var.var_name,vl->current_var.address);
        vl=vl->next;
    }
    printf("%s  %d\n",vl->current_var.var_name,vl->current_var.address);
}


struct Var_List_Set{
    Var_List *current_var_list;
    struct Var_List_Set *next;
    int index;
};

void VLS_init(Var_List_Set **vls){
    (*vls)=(Var_List_Set *)malloc(sizeof(Var_List_Set)*1);
    
    VL_init(&((*vls)->current_var_list));
    (*vls)->next=NULL;
    (*vls)->index=1;
}

// push new empty inside
void VLS_push(Var_List_Set **vls){
    Var_List_Set *new_vls;
    VLS_init(&new_vls);
    
    Var_List_Set **temp_vls=&(*vls);
    
    while ((*temp_vls)->next!=NULL) {
        temp_vls=&((*temp_vls)->next);
    }

    new_vls->index=(*temp_vls)->index+1;
    (*temp_vls)->next=new_vls;

}

int VLS_length(Var_List_Set *vls){
    if (vls->current_var_list->current_var.var_name==NULL) {
        return 0;
    }
    int length=0;
    while (vls->next!=NULL) {
        length++;
        vls=vls->next;
    }
    return length+1;
}

void VLS_pop(Var_List_Set **vls){
    if (VLS_length(*vls)==0) {
        printf("Error. VLS can not pop\n");
        exit(0);
    }
    Var_List_Set **temp_vls=&(*vls);

    while ((*temp_vls)->next!=NULL) {
        temp_vls=&((*temp_vls)->next);
    }

    // reinit
    if((*temp_vls)->index==1){
        VLS_init(temp_vls);
    }
    // remove
    else{
        (*temp_vls)=NULL;
    }
}

Var_List ** VLS_finalVL(Var_List_Set **vls){
    Var_List_Set **temp_vls=&(*vls);
    
    while ((*temp_vls)->next!=NULL) {
        temp_vls=&((*temp_vls)->next);
    }
    return &((*temp_vls)->current_var_list);
}


