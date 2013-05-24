//
//  walley_statements.h
//  Walley0.1
//
//  Created by shd101wyy on 13-3-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_judge.h"

/*

 version 1.0
 if x>=0 then
 
 if_stms  -> 'if' relation 'then'
 elif_stms-> 'elif' relation 'then'
 else_stms-> 'else'
 
 
 version 2.0
 if_stms -> 'if' relation 'then' walley_statements 'end'       // if elif, then add 'end' while lexer analysis
 elif_stms -> 'elif' relation 'then' walley_statements 'end'   // there is no real 'end', add here while lexer analysis
 else_stms -> 'else' walley_statements 'end'
 
 ( walley_statements
    ( statements
        ( if)
        ( simple_relation( <(num 3)(id x)))
        ( statements
            ( if)
            ( simple_relation( <(num 4)(id x)))
            ( statements( =(id y)(num 12)))
        )
    )
)
 
 if x>0 then
     if x>3 then
         x=12
     else 
         x=5
     end
 else
     x=16
 end
 
 ===========
 
 while x<=0 then
 version 1.0
 while_stms -> 'while' relation 'then'
 
 version 2.0
 while_stms -> 'while' relation 'then' walley_statements 'end'

 ===========
 
 for i=0,i<10,i++ then
 for i<10,i++ then
 
 // not support 'for i in range(10):' kind of for statements now
 
 version 1.0
 for_stms ->
 |  'for' simple_relation ',' assignment 'then'
 |  'for' ',' simple_relation ',' assignment 'then'
 |  'for' assignment ',' simple_relation ',' assignment 'then'
 
 version 2.0
 for_stms ->
 
 # new on May 16    foreach
 |  'for' id ',' id 'in' value 'then' walley_statements 'end'
 |  'for' id        'in' value 'then' walley_statements 'end'
 
 |  'for' simple_relation ',' assignment 'then' walley_statements 'end'
 |  'for' ',' simple_relation ',' assignment 'then' walley_statements 'end'
 |  'for' assignment ',' simple_relation ',' assignment 'then' walley_statements 'end'
 
 ===========
 
 def add(num1,num2) then
 
 func_stms -> 'def' func 'then'
 

 ===========
 end_stm -> 'end'
 ===========
 does not support:
    class
    switch
    i++
    i--
    +=
    -=
    exp:
now
============
 
 statements ->
 |  return_stm
 |  if_stms
 |  elif_stms
 |  else_stms
 |  while_stms
 |  for_stms
 |  func_stms
 |  end_stm
 |  assignment
 |  value
 
 ============
 func_name_stm -> id
                | table_value
 def_stms -> 'def' func_name_stm '(' params ')' 'then' walley_statements 'end'
 
============
 walley_statements ->
                    | statements, statements        // use sentences_seperation
*/


//============================================================================================
// version 1.0
//  if_stms  -> 'if' relation 'then'

// version 2.0
// if_stms -> 'if' relation 'then' walley_statements 'end'       // if elif, then add 'end' while lexer analysis

bool if_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    
    //if_stms -> 'if' relation 'then' walley_statements 'end'
    if (term(tl->current_token.TOKEN_STRING, "if")) {
        int index_of_then=TL_indexOfTokenThatHasTokenString(tl, "then");
        if (index_of_then==-1) {
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
        
        if (term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "end") && length_of_tl>2) {
            Token_List *relation_tl=TL_subtl(tl, 1, index_of_then);

            TREE_addNode(tree, "if", "");
            int index=TREE_INDEX;
            TREE_addNode(tree, "relation", "");
            return relation(TREE_getTreeAccordingToIndex(tree, index), relation_tl) && walley_statements(tree, TL_subtl(tl, index_of_then+1, length_of_tl-1));
        }
        // incomplete
        else{
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
        
    }
    
    return FALSE;
}

// version 1.0
// elif_stms-> 'elif' relation 'then'

//version 2.0
// elif_stms -> 'elif' relation 'then' walley_statements 'end'   // there is no real 'end', add here while lexer analysis

bool elif_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    // elif_stms -> 'elif' relation 'then' walley_statements 'end'
    if (term(tl->current_token.TOKEN_STRING, "elif")) {
        int index_of_then=TL_indexOfTokenThatHasTokenString(tl, "then");
        if (index_of_then==-1) {
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
        if (term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "end") && length_of_tl>2) {
            Token_List *relation_tl=TL_subtl(tl, 1, index_of_then);
            
            TREE_addNode(tree, "elif", "");
            int index=TREE_INDEX;
            TREE_addNode(tree, "relation", "");
            return relation(TREE_getTreeAccordingToIndex(tree, index), relation_tl)
            && walley_statements(tree, TL_subtl(tl, index_of_then+1, length_of_tl-1));

        }
        // incomplete
        else{
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
    }
    return FALSE;
}

// version 1.0
// else_stms-> 'else'

// version 2.0
//  else_stms -> 'else' walley_statements 'end'

bool else_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    
    // 'else'
    if (term(tl->current_token.TOKEN_STRING, "else")) {
        if (term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "end")) {
            TREE_addNode(tree, "else", "");
            return walley_statements(tree, TL_subtl(tl, 1, length_of_tl-1));
        }
        else{
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
    }
    
    return FALSE;
}

//==================================================
/*
 version 1.0
 while_stms -> 'while' relation 'then'
 
 version 2.0
 while_stms -> 'while' relation 'then' walley_statements 'end'
 
 */
/*
 
 
 ( walley_statements
    ( statements
        ( while)
        ( simple_relation( <(id x)(num 5)))
        ( statements( =(id y)(num 12)))
    )
 )
 */
 bool while_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    //'while' relation 'then'
    if (term(tl->current_token.TOKEN_STRING, "while")) {
        int index_of_then=TL_indexOfTokenThatHasTokenString(tl, "then");
        if (index_of_then==-1) {
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
        
        if (term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "end") &&length_of_tl>2) {
            Token_List *relation_tl=TL_subtl(tl, 1, index_of_then);
            
            TREE_addNode(tree, "while", "");
            int index=TREE_INDEX;
            TREE_addNode(tree, "relation", "");
            return relation(TREE_getTreeAccordingToIndex(tree, index), relation_tl)
                && walley_statements(tree, TL_subtl(tl, index_of_then+1, length_of_tl-1))
            && end_stm(tree, TL_subtl(tl, length_of_tl-1, length_of_tl));

        }
        // incomplete
        else{
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
    }
    return FALSE;
}

//=================================================

/*
 , is not in ()
 for_stms ->
 |  'for' simple_relation ',' assignment 'then'
 |  'for' ',' simple_relation ',' assignment 'then'
 |  'for' assignment ',' simple_relation ',' assignment 'then'
 
 
 */
/*
version 1.0
for_stms ->
|  'for' simple_relation ',' assignment 'then'
|  'for' ',' simple_relation ',' assignment 'then'
|  'for' assignment ',' simple_relation ',' assignment 'then'

version 2.0
for_stms ->
 # new on May 16    foreach
|  'for' id ',' id 'in' value 'then' walley_statements 'end'
|  'for' id        'in' value 'then' walley_statements 'end'
 
|  'for' simple_relation ',' assignment 'then' walley_statements 'end'
|  'for' ',' simple_relation ',' assignment 'then' walley_statements 'end'
|  'for' assignment ',' simple_relation ',' assignment 'then' walley_statements 'end'
*/

/*
 ( walley_statements
    ( statements
        ( for)
        ( assignment( =(id i)(num 0)))
        ( simple_relation( <(id i)(num 5)))
        ( assignment( =(id i)( +(id i)(num 1))))
        ( statements( =(id x)(num 15)))
    )
 )
 
 */
bool for_stms(TREE *tree, Token_List *tl){
    if (term(tl->current_token.TOKEN_STRING, "for")==FALSE) {
        return FALSE;
    }
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    
    int length_of_tl=TL_length(tl);
    
    /*
     
     check 
     |  'for' id ',' id 'in' value 'then' walley_statements 'end'
     |  'for' id        'in' value 'then' walley_statements 'end'
     
     */
    // assume it is correct
    if (term(TL_tokenAtIndex(tl, 4).TOKEN_STRING, "in") || term(TL_tokenAtIndex(tl, 2).TOKEN_STRING, "in")) {
        
        
        int index_of_then=-1;
        // check then index;
        Token_List *temp_tl=tl;
        int i=0;
        while (temp_tl!=NULL) {
            if (term(temp_tl->current_token.TOKEN_STRING, "then")) {
                index_of_then=i;
                break;
            }
            temp_tl=temp_tl->next;
            i++;
        }
        
        
        TREE_addNode(tree, "foreach", "");
        
        temp_tl=tl;
        
        // for i,v in x
        // check i error
        if (term(tl->next->current_token.TOKEN_CLASS, "id")==FALSE) {
            Walley_Print_Error(TL_toString(tl), "for each statements error, for i,v in value, i,v must be id", tl->next->current_token.TOKEN_START);
        }
        
        // add i
        TREE_addNode(tree, tl->next->current_token.TOKEN_STRING, "foreach_index");
        
        if (term(tl->next->next->current_token.TOKEN_STRING, ",")) {
            // check v error
            if (term(tl->next->next->next->current_token.TOKEN_CLASS, "id")==FALSE) {
                Walley_Print_Error(TL_toString(tl), "for each statements error, for i,v in value, i,v must be id", tl->next->current_token.TOKEN_START);
            }
            
            // add v
            TREE_addNode(tree, tl->next->next->next->current_token.TOKEN_STRING, "foreach_value");
            tl=tl->next->next->next->next->next; // value
            
            // add in value
            int index=TREE_INDEX;
            TREE_addNode(tree, "", "foreach_in");
            TREE_addNode(TREE_getTreeAccordingToIndex(tree, index), "value", "");
            index+=1;
            value(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(temp_tl, 5, index_of_then));
            
        }
        else{
            // add v
            TREE_addNode(tree, "", "foreach_value");
            tl=tl->next->next->next; // value
            
            // add in value
            int index=TREE_INDEX;
            TREE_addNode(tree, "", "foreach_in");
            TREE_addNode(TREE_getTreeAccordingToIndex(tree, index), "value", "");
            index+=1;
            value(TREE_getTreeAccordingToIndex(tree, index), TL_subtl(temp_tl, 3, index_of_then));
        }
        
        
        return walley_statements(tree, TL_subtl(temp_tl, index_of_then+1, length_of_tl-1))
        && end_stm(tree, TL_subtl(temp_tl, length_of_tl-1, length_of_tl));
    }
    
    
    
    int num_of_semi_colon=0;
    int count_of_p=0; // count of ()
    Token_List *temp_tl=tl;
    
    int index_of_semi_colon[3];
    index_of_semi_colon[0]=-1;
    index_of_semi_colon[1]=-1;
    index_of_semi_colon[2]=-1;
    
    int index=0;
    int i=0;
    
    int index_of_then=-1;
    
    while (term(tl->current_token.TOKEN_STRING, "then")==FALSE && tl->next!=NULL) {
        if (term(tl->current_token.TOKEN_STRING, "(")) {
            count_of_p++;
            tl=tl->next;
            i++;
            continue;
        }
        if (term(tl->current_token.TOKEN_STRING, ")")) {
            count_of_p--;
            tl=tl->next;
            i++;
            continue;
        }
        
        if (count_of_p==0 && term(tl->current_token.TOKEN_STRING, ",")) {
            
            
            //mistake... to many ,
            if (index<2) {
                index_of_semi_colon[index]=i;
                index++;
            }
            num_of_semi_colon++;
            
        }
        i++;
        tl=tl->next;
    }
    if (term(tl->current_token.TOKEN_STRING,"then")) {
        index_of_then=i;
    }
    tl=temp_tl;
    
    // incomplete
    if (index_of_then==-1 || term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "end")==FALSE) {
        INCOMPLETE_STATEMENT=TRUE;
        return FALSE;
    }
    
    if (//term(tl->current_token.TOKEN_STRING, "for")
        //&&term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "then")
        //&&length_of_tl!=2
        length_of_tl!=2
        &&num_of_semi_colon!=0
        &&num_of_semi_colon<=2
        ) {
        //|  'for' simple_relation ',' assignment 'then' walley_statements 'end'
        if (num_of_semi_colon==1) {
            Token_List *simple_relation_tl=TL_subtl(tl, 1, index_of_semi_colon[0]);
            Token_List *assignment_tl=TL_subtl(tl, index_of_semi_colon[0]+1, index_of_then);
            
            TREE_addNode(tree, "for", "");
            int index_of_sr=TREE_INDEX;
            TREE_addNode(tree, "simple_relation", "");
            int index_of_a=TREE_INDEX;
            TREE_addNode(tree, "assignment", "");
            
            return simple_relation(TREE_getTreeAccordingToIndex(tree, index_of_sr), simple_relation_tl)
            && assignment(TREE_getTreeAccordingToIndex(tree, index_of_a), assignment_tl)&&
            walley_statements(tree, TL_subtl(tl, index_of_then+1, length_of_tl-1))
            && end_stm(tree, TL_subtl(tl, length_of_tl-1, length_of_tl));
        }
        //|  'for' ',' simple_relation ',' assignment 'then' walley_statements 'end'
        //|  'for' assignment ',' simple_relation ',' assignment 'then' walley_statements 'end'
        else{
            //|  'for' ',' simple_relation ',' assignment 'then' walley_statements 'end'
            if (term(tl->next->current_token.TOKEN_STRING, ",")) {
                Token_List *simple_relation_tl=TL_subtl(tl, 2, index_of_semi_colon[1]);
                Token_List *assignment_tl=TL_subtl(tl, index_of_semi_colon[1]+1, index_of_then);
                
                TREE_addNode(tree, "for", "");
                int index_of_sr=TREE_INDEX;
                TREE_addNode(tree, "simple_relation", "");
                int index_of_a=TREE_INDEX;
                TREE_addNode(tree, "assignment", "");
                
                return simple_relation(TREE_getTreeAccordingToIndex(tree, index_of_sr), simple_relation_tl)
                && assignment(TREE_getTreeAccordingToIndex(tree, index_of_a), assignment_tl)&&
                walley_statements(tree, TL_subtl(tl, index_of_then+1, length_of_tl-1))
                && end_stm(tree, TL_subtl(tl, length_of_tl-1, length_of_tl));
            }
            //|  'for' assignment ',' simple_relation ',' assignment 'then' walley_statements 'end'

            else{
                Token_List *assignment_tl1=TL_subtl(tl, 1, index_of_semi_colon[0]);
                Token_List *simple_relation_tl=TL_subtl(tl, index_of_semi_colon[0]+1, index_of_semi_colon[1]);
                Token_List *assignment_tl2=TL_subtl(tl, index_of_semi_colon[1]+1, index_of_then);
                
                TREE_addNode(tree, "for","");
                int index_of_a_tl1=TREE_INDEX;
                TREE_addNode(tree, "assignment", "");
                int index_of_sr=TREE_INDEX;
                TREE_addNode(tree, "simple_relation","");
                int index_of_a_tl2=TREE_INDEX;
                TREE_addNode(tree, "assignment","");
                
                return assignment(TREE_getTreeAccordingToIndex(tree, index_of_a_tl1), assignment_tl1)
                    && simple_relation(TREE_getTreeAccordingToIndex(tree, index_of_sr),simple_relation_tl)
                && assignment(TREE_getTreeAccordingToIndex(tree, index_of_a_tl2),assignment_tl2)&&
                walley_statements(tree, TL_subtl(tl, index_of_then+1, length_of_tl-1))
                && end_stm(tree, TL_subtl(tl, length_of_tl-1, length_of_tl));

            }
        }
    }
    return FALSE;
}


//========================
// func_stms -> 'def' func 'then'
/*
    x = def (a,b) then return a+b end
 
 ( walley_statements
    ( statements
        ( =(id x)
            ( func_value
                ( def)( params(id a)(id b))
                ( statements( return)( +(id a)(id b)))
                ( statements( end))
            )
        )
    )
 )
 
    def x (a,b) then return a+b end
 
 
    def x (a,b) then return a+b end
 
 ( walley_statements
    ( statements( def)( func(call x)( params(id a)(id b))))
    ( statements( return)( +(id a)(id b)))
    ( statements( end))
 )
 
 
 */
bool func_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    //'def' func 'then'
    if (term(tl->current_token.TOKEN_STRING, "def")) {
        if (length_of_tl>2 && term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "then")) {
            TREE_addNode(tree, "def", "");
            
            Token_List *func_tl=TL_subtl(tl, 1, length_of_tl-1);
            
            int index=TREE_INDEX;
            TREE_addNode(tree, "func","");
            return func(TREE_getTreeAccordingToIndex(tree, index), func_tl)
            && end_stm(tree, TL_subtl(tl, length_of_tl-1, length_of_tl));
        }
        // incomplete 
        else{
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
       
    }
    return FALSE;

}



bool end_stm(TREE *tree, Token_List *tl){
    
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }

    if (TL_length(tl)==1 && term(tl->current_token.TOKEN_CLASS, "end")) {
        TREE_addNode(tree, "end","");
        return TRUE;
    }
    return FALSE;
}


/*
 
 func_name_stm -> id
 | table_value
 def_stms -> 'def' func_name_stm '(' params ')' 'then' walley_statements 'end'

 ( walley_statements
    ( statements
        ( =(id x)
            ( func_value
                ( def)( params(id a)(id b))
                ( statements( return)( +(id a)(id b)))
                ( statements( end))
            )
        )
    )
 )

 >>> def add() then return 3+4 end

 ( walley_statements
    ( statements
        ( =(id add)
            ( func_value
                ( def)( params(id none))
                ( statements( return)( +(num 3)(num 4)))
                ( statements( end))
            )
        )
    )
 )
 
 */




// def_stms -> 'def' func_name_stm '(' params ')' 'then' walley_statements 'end'
bool def_stms(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    int length_of_tl=TL_length(tl);
    if (term(tl->current_token.TOKEN_STRING, "def") && term(tl->next->current_token.TOKEN_STRING, "(")==FALSE) {
        int index_of_then=TL_indexOfTokenThatHasTokenString(tl, "then");
        int index_of_left_bracket=TL_indexOfTokenThatHasTokenString(tl, "(");
        if(index_of_then==-1){
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
        
        if (term(TL_tokenAtIndex(tl, length_of_tl-1).TOKEN_STRING, "end")==FALSE) {
            INCOMPLETE_STATEMENT=TRUE;
            return FALSE;
        }
        
        
       
        
        Token_List *new_tl;
        TL_init(&new_tl);
        
        int begin=1;
        int end=index_of_left_bracket;
        
        Token_List *temp_tl=tl;
        int i=0;
        for (i=0; i<end; i++) {
            if (i>=begin) {
                TL_addToken(&new_tl, temp_tl->current_token);
            }
            temp_tl=temp_tl->next;
        }
        Token add_token;
        add_token.TOKEN_STRING="=";
        add_token.TOKEN_CLASS="assignment_operator";
        TL_addToken(&new_tl, add_token);
        
        temp_tl=tl;
        i=0;
        for (i=0; i<length_of_tl; i++) {
            if (i>=begin && i<end) {
                temp_tl=temp_tl->next;
                continue;
            }
            TL_addToken(&new_tl, temp_tl->current_token);
            temp_tl=temp_tl->next;
        }
        
        return assignment(tree, new_tl);
    }
    else{
        return FALSE;
    }
}

//========================
/*
 
 statements -> 
 |  return_stm
 |  if_stms
 |  elif_stms
 |  else_stms
 |  while_stms
 |  for_stms
 (|  func_stms    removed)
 |  def_stms
 |  end_stm
 |  assignment
 |  value
 
 ( walley_statements
    ( statements
        ( if)
        ( simple_relation( <(num 0)(id x))
            ( statements
                ( if)
                ( simple_relation( <(num 3)(id y))
                    ( statements( =(id x)(num 12)))
                )
            )
        )
    )
 
 )
 

 
 */

bool statements(TREE *tree, Token_List *tl){
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    
    return return_stm(tree, tl)
        ||if_stms(tree, tl)
        ||elif_stms(tree, tl)
        ||else_stms(tree, tl)
        ||while_stms(tree, tl)
        ||for_stms(tree, tl)
        // ||func_stms(tree, tl)        removed
        ||def_stms(tree, tl)
        ||end_stm(tree, tl)
        ||assignment(tree, tl)
        ||value(tree, tl);
    
}


//walley_statements ->
//| statements, statements        // use sentences_seperation
bool walley_statements(TREE *tree, Token_List *tl){
    
  
    
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    Token_List *temp_tl;
    TL_init(&temp_tl);
    int begin=0;
    
    while (sentences_seperation(tl, &temp_tl, &begin)) {
        if (INCOMPLETE_STATEMENT) {
            return FALSE;
        }
        
        int index=TREE_INDEX;
        TREE_addNode(tree, "statements", "");
      
        
        if (!statements(TREE_getTreeAccordingToIndex(tree, index), temp_tl)) {
            printf("Walley Statements Parse Error\n");
            return FALSE;
        }
    }
    if (INCOMPLETE_STATEMENT) {
        return FALSE;
    }
    return TRUE;
}





