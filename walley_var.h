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
        temp_vl->current_var.var_name=add_var.var_name;
        temp_vl->current_var.address=add_var.address;
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




