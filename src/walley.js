none=null;function isalpha(input_char){return/^[a-z]+$/i.test(input_char)}function isdigit(e){return!isNaN(parseFloat(e))&&isFinite(e)}String.prototype.find=function(find_str,start){if(typeof start=="undefined"){start=0}return this.indexOf(find_str,start)};String.prototype.tolower=function(){return this.toLowerCase()};String.prototype.toupper=function(){return this.toUpperCase()};String.prototype.reverse=function(){return this.split("").reverse().join("")};Math["cot"]=function(num){return 1/Math.tan(num)};Math["sec"]=function(num){return 1/Math.cos(num)};Math["csc"]=function(num){return 1/Math.sin(num)};Object.prototype.slice=function(start,end){var return_obj={};var a=0;for(var i=start;i<end;i++){return_obj[a]=this[i];a++}return return_obj};Object.prototype.append=function(e){var t=this.maxn()+1;this[t]=e};Object.prototype.maxn=function(){var t=0;if(typeof this[0]=="undefined"){return-1}while(typeof this[t]!="undefined"){t=t+1}return t-1};Object.prototype.insert=function(insert_obj,pos){if(typeof pos=="undefined"){pos=table.maxn(this)+1;this[pos]=insert_obj}else{this[pos]=insert_obj}};Object.prototype.remove=function(pos){if(typeof pos=="undefined"){pos=table.maxn(obj)}delete this[pos]};Object.prototype.length=function(){return Object.keys(this).length};function len(obj){if(typeof obj=="string"){return obj.length}else if(typeof obj=="object"){return Object.keys(obj).length}else{console.log("Error..\nfunctin len() only support table or string\n")}}WALLEY={};WALLEY.stringToObject=function(input_str){if(typeof input_str=="string"){obj={};for(var i=0;i<input_str.length;i=i+1){obj[i]=input_str[i]}return obj}else{return input_str}};WALLEY.slice=function(obj,start,end){if(typeof obj=="object"){var return_obj={};var a=0;for(var i=start;i<end;i++){return_obj[a]=obj[i];a++}return return_obj}else if(typeof obj=="string"){return this.slice(start,end)}else{console.log("Error.. WALLEY.slice only support object and string type")}};function range(start,end,step){if(typeof end=="undefined"&&typeof step=="undefined"){end=start;start=0;step=1}else if(typeof step=="undefined"){step=1}var return_obj={};var count=0;for(var i=start;i<end;i=i+step){return_obj[count]=i;count++}return return_obj}
BEAUTIFUL_SPACES = 0;
if (typeof(exports)==="undefined"){
    exports = {};
}
INCOMPLETE_STATEMENT = false;
toString = function(input_str){
    if (input_str[0]==="\""){
        return input_str;
    }
    else{
        return "\""+input_str+"\"";
    }
}
Walley_Print_Error = function(input_str,error_message,error_start_index){
    console.log("Error.. %s\n",error_message);
    console.log("%s\n",input_str);
    var empty = "";
    var i = 0;
    for ( ; i<error_start_index ; i = i+1){
        empty = empty+" ";
    }
    empty = empty+"^";
    console.log("%s\n",empty);
}
Token_init = function(){
    var Token = {};
    Token["TOKEN_CLASS"] = "";
    Token["TOKEN_STRING"] = "";
    Token["TOKEN_START"] = -1;
    Token["TOKEN_END"] = -1;
    return Token;
}
TOKEN_print = function(token){
    console.log(token["TOKEN_CLASS"]+":"+"|"+token["TOKEN_STRING"]+"|"+token["TOKEN_START"]+"|"+token["TOKEN_END"]);
}
TL_toString = function(tl){
    var return_string = "";
    for(i in WALLEY.stringToObject(tl)){
        if((WALLEY.stringToObject(tl)).hasOwnProperty(i)){
            v=(WALLEY.stringToObject(tl))[i];
            return_string = return_string+v["TOKEN_STRING"];
        }
    };
}
TL_addToken = function(tl,add_token){
    var temp_token = Token_init();
    temp_token["TOKEN_CLASS"] = add_token["TOKEN_CLASS"];
    temp_token["TOKEN_STRING"] = add_token["TOKEN_STRING"];
    temp_token["TOKEN_START"] = add_token["TOKEN_START"];
    temp_token["TOKEN_END"] = add_token["TOKEN_END"];
    tl.append(temp_token);
}
TL_indexOfTokenThatHasTokenString = function(tl,token_string){
    var output = -1;
    var i = 0;
    for (i = 0 ; i<len(tl) ; i = i+1){
        if (tl[i]["TOKEN_STRING"]===token_string){
            return i;
        }
    }
    return -1;
}
TL_indexOfTokenThatHasTokenClass = function(tl,token_string){
    var output = -1;
    var i = 0;
    for (i = 0 ; i<len(tl) ; i = i+1){
        if (tl[i]["TOKEN_CLASS"]===token_string){
            return i;
        }
    }
    return -1;
}
match = function(input_str,index,match_string){
    var length_of_input_str = len(input_str);
    var length_of_match_str = len(match_string);
    if (length_of_input_str<index+length_of_match_str){
        return false;
    }
    var i = 0;
    var match = true;
    for ( ; i<length_of_match_str ; i = i+1){
        if (input_str[index+i]!==match_string[i]){
            match = false;
            break;
        }
    }
    if (match===true){
        return true;
    }
    else{
        return false;
    }
}
term = function(input_str1,input_str2){
    if (input_str1===input_str2){
        return true;
    }
    else{
        return false;
    }
}
LIST_indexOfFinalBracket = function(input_str,index_of_first_bracket){
    var count = 0;
    var in_string = false;
    var length_of_input_str = len(input_str);
    var i = index_of_first_bracket;
    for ( ; i<length_of_input_str ; i = i+1){
        if (((in_string===false && input_str[i]==="\"") && input_str[i-1]!=="\\")){
            in_string = true;
            continue;
        }
        if (((in_string===true && input_str[i]==="\"") && input_str[i-1]!=="\\")){
            in_string = false;
            continue;
        }
        if (in_string===false){
            if (input_str[i]==="["){
                count = count+1;
                continue;
            }
            if (input_str[i]==="]"){
                count = count-1;
                if (count===0){
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
indexOfFinalDoubleQuote = function(input_str,first_index){
    var first_char = input_str[first_index];
    var i = first_index+1;
    var length = len(input_str);
    if (first_char==="\""){
        for ( ; i<length ; i = i+1){
            if ((input_str[i]==="\"" && input_str[i-1]!=="\\")){
                return i;
            }
            if ((input_str[i]==="\"" && input_str[i-1]==="\\")){
                if (input_str[i-2]==="\\"){
                    return i;
                }
            }
        }
    }
    return -1;
}
Walley_Analyze_Token_Class = function(input_str,i){
    var return_obj = {};
    var length = len(input_str);
    if ((match(input_str,i,"&&") || match(input_str,i,"||"))){
        console.log("Error.. Does not support && and ||");
        console.log("Please use ' and ' and ' or ' instead");
    }
    if ((match(input_str,i,"++") || match(input_str,i,"--"))){
        end_index = i+2;
        return_obj[0] = end_index;
        return_obj[1] = "self_operator";
        return return_obj;
    }
    if (((((match(input_str,i,"+=") || match(input_str,i,"-=")) || match(input_str,i,"*=")) || match(input_str,i,"//=")) || match(input_str,i,"%="))){
        end_index = i+2;
        return_obj[0] = end_index;
        return_obj[1] = "self_assignment";
        return return_obj;
    }
    if (match(input_str,i,"**")){
        end_index = i+2;
        return_obj[0] = end_index;
        return_obj[1] = "m_operator";
        return return_obj;
    }
    if ((((((input_str[i]==="+" || input_str[i]==="-") || input_str[i]==="*") || input_str[i]==="/") || input_str[i]==="^") || input_str[i]==="%")){
        end_index = i+1;
        return_obj[0] = end_index;
        return_obj[1] = "m_operator";
        return return_obj;
    }
    if ((input_str[i]==="," || input_str[i]===":")){
        end_index = i+1;
        return_obj[0] = end_index;
        return_obj[1] = "punctuation";
        return return_obj;
    }
    if ((((match(input_str,i,"==") || match(input_str,i,">=")) || match(input_str,i,"<=")) || match(input_str,i,"!="))){
        end_index = i+2;
        return_obj[0] = end_index;
        return_obj[1] = "judge_sign";
        return return_obj;
    }
    if ((input_str[i]===">" || input_str[i]==="<")){
        end_index = i+1;
        return_obj[0] = end_index;
        return_obj[1] = "judge_sign";
        return return_obj;
    }
    if (((i<=length-2 && input_str[i]==="#") && input_str[i+1]==="~")){
        end_index = i+2;
        return_obj[0] = end_index;
        return_obj[1] = "l_annotation";
        return return_obj;
    }
    if ((i<=length-2 && (input_str[i]==="~" && input_str[i+1]==="#"))){
        end_index = i+2;
        return_obj[0] = end_index;
        return_obj[1] = "r_annotation";
    }
    if (input_str[i]==="="){
        end_index = i+1;
        return_obj[0] = end_index;
        return_obj[1] = "assignment_operator";
        return return_obj;
    }
    if (input_str[i]==="#"){
        end_index = i+1;
        return_obj[0] = end_index;
        return_obj[1] = "annotation";
        return return_obj;
    }
    if ((((input_str[i]==="(" || input_str[i]===")") || input_str[i]==="{") || input_str[i]==="}")){
        end_index = i+1;
        var output = input_str[i];
        return_obj[0] = end_index;
        return_obj[1] = output;
        return return_obj;
    }
    if (input_str[i]==="["){
        var index_of_final = LIST_indexOfFinalBracket(input_str,i);
        if (index_of_final===-1){
            INCOMPLETE_STATEMENT = true;
        }
        end_index = index_of_final+1;
        return_obj[0] = end_index;
        return_obj[1] = "list_table";
        return return_obj;
    }
    if (input_str[i]==="\""){
        var index_of_right_dq = indexOfFinalDoubleQuote(input_str,i);
        if (index_of_right_dq===-1){
            console.log("incomplete str\n");
            process.exit(0);
            }
        else{
            end_index = index_of_right_dq+1;
            return_obj[0] = end_index;
            return_obj[1] = "string";
            return return_obj;
        }
    }
    if (isdigit(input_str[i])===true){
        var a = i;
        var temp_str = input_str[i];
        while (isdigit(temp_str)){
            a = a+1;
            temp_str = temp_str+input_str[a];
        }
        end_index = a;
        return_obj[0] = end_index;
        return_obj[1] = "num";
        return return_obj;
    }
    if (((input_str[i]===" " || input_str[i]==="\n") || input_str[i]==="\t")){
        var a = i+1;
        for ( ; a<length ; a = a+1){
            if (((input_str[a]!==" " && input_str[a]!=="\n") && input_str[a]!=="\t")){
                break;
            }
        }
        end_index = a;
        return_obj[0] = end_index;
        return_obj[1] = "white_space";
        return return_obj;
    }
    if (((isalpha(input_str[i]) || input_str[i]==="_") || input_str[i]==="$")){
        var a = i+1;
        for ( ; a<length ; a = a+1){
            if ((((isalpha(input_str[a]) || input_str[a]==="_") || input_str[a]==="$") || isdigit(input_str[a]))){
                continue;
                    }
            else{
                break;
            }
        }
        var id_string = input_str.slice(i,a);
        if (id_string==="import"){
            end_index = i+6;
            return_obj[0] = end_index;
            return_obj[1] = "import";
            return return_obj;
            }
        else if ((id_string==="and" || id_string==="not")){
            end_index = i+3;
            return_obj[0] = end_index;
            return_obj[1] = "relation";
            return return_obj;
            }
        else if (id_string==="or"){
            end_index = i+2;
            return_obj[0] = end_index;
            return_obj[1] = "relation";
            return return_obj;
            }
        else if (id_string==="if"){
            end_index = i+2;
            return_obj[0] = end_index;
            return_obj[1] = "keyword";
            return return_obj;
            }
        else if ((id_string==="def" || id_string==="for")){
            end_index = i+3;
            return_obj[0] = end_index;
            return_obj[1] = "keyword";
            return return_obj;
            }
        else if (((id_string==="elif" || id_string==="else") || id_string==="case")){
            end_index = i+4;
            return_obj[0] = end_index;
            return_obj[1] = "keyword";
            return return_obj;
            }
        else if (id_string==="while"){
            end_index = i+5;
            return_obj[0] = end_index;
            return_obj[1] = "keyword";
            return return_obj;
            }
        else if (id_string==="then"){
            end_index = i+4;
            return_obj[0] = end_index;
            return_obj[1] = "then";
            return return_obj;
            }
        else if (id_string==="end"){
            end_index = i+3;
            return_obj[0] = end_index;
            return_obj[1] = "end";
            return return_obj;
            }
        else if (id_string==="return"){
            end_index = i+6;
            return_obj[0] = end_index;
            return_obj[1] = "return";
            return return_obj;
            }
        else if (id_string==="local"){
            end_index = i+5;
            return_obj[0] = end_index;
            return_obj[1] = "local";
            return return_obj;
            }
        else if (id_string==="switch"){
            end_index = i+6;
            return_obj[0] = end_index;
            return_obj[1] = "keyword";
            return return_obj;
            }
        else if (id_string==="new"){
            end_index = i+3;
            return_obj[0] = end_index;
            return_obj[1] = "new";
            return return_obj;
            }
        else{
            end_index = a;
            return_obj[0] = end_index;
            return_obj[1] = "id";
            return return_obj;
        }
    }
    if (input_str[i]==="."){
        var a = i+1;
        end_index = a;
        return_obj[0] = end_index;
        return_obj[1] = "dot";
        return return_obj;
    }
    Walley_Print_Error(input_str,"Can not analyze this input",i);
    process.exit(0);
}
Walley_Lexical_Analyzie = function(input_str){
    var i = 0;
    var length = len(input_str);
    var tl = {};
    var end_index = 0;
    for ( ; i<length ; i = i+1){
        var output_data = Walley_Analyze_Token_Class(input_str,i);
        end_index = output_data[0];
        var token_class = output_data[1];
        if (INCOMPLETE_STATEMENT===true){
            break;
        }
        if (token_class==="white_space"){
            i = end_index-1;
            continue;
        }
        if (token_class==="annotation"){
            for (i = end_index ; i<length ; i = i+1){
                if (input_str[i]==="\n"){
                    break;
                }
            }
            continue;
        }
        if (token_class==="l_annotation"){
            i = end_index;
            var count = 0;
            var find_right_annotation = false;
            for ( ; i<length-1 ; i = i+1){
                if (input_str[i]==="\""){
                    count = count+1;
                    continue;
                }
                if (((count%2===0 && input_str[i]==="~") && input_str[i+1]==="#")){
                    i = i+1;
                    find_right_annotation = true;
                    break;
                }
            }
            if (find_right_annotation===false){
                INCOMPLETE_STATEMENT = true;
                return tl;
            }
            continue;
        }
        temp_token = Token_init();
        temp_token["TOKEN_START"] = i;
        temp_token["TOKEN_END"] = end_index;
        temp_token["TOKEN_CLASS"] = token_class;
        var token_string = "";
        token_string = input_str.slice(i,end_index).trim();
        temp_token["TOKEN_STRING"] = token_string;
        tl.append(temp_token);
        i = end_index-1;
    }
    return tl;
}
TREE_INDEX = 0;
TREE_init = function(name){
    var TREE = {};
    TREE["name"] = name||"";
    TREE["token_class"] = "";
    TREE["index"] = 0;
    TREE["layer"] = 0;
    TREE["node_list"] = {};
    TREE_INDEX = TREE_INDEX+1;
    return TREE;
}
TREE_addNode = function(tree,name,token_class){
    var length_of_nl = len(tree["node_list"]);
    tree["node_list"][length_of_nl] = TREE_init();
    tree["node_list"][length_of_nl]["name"] = name;
    tree["node_list"][length_of_nl]["token_class"] = token_class;
    tree["node_list"][length_of_nl]["index"] = TREE_INDEX-1;
    tree["node_list"][length_of_nl]["layer"] = tree["layer"]+1;
    tree["node_list"][length_of_nl]["node_list"] = {};
}
TREE_addTree = function(tree,add_tree){
    var index = TREE_INDEX;
    var length_of_nl = len(tree["node_list"]);
    tree["node_list"][length_of_nl] = add_tree;
    tree["node_list"][length_of_nl]["index"] = index;
    tree["node_list"][length_of_nl]["layer"] = tree["layer"]+1;
    TREE_INDEX = TREE_INDEX+1;
}
TREE_getTreeAccordingToIndex = function(tree,index){
    if (index===tree["index"]){
        return tree;
    }
    else{
        var nl = tree["node_list"];
        if (len(nl)===0){
            return null;
        }
        var i = 0;
        var length = len(nl);
        for ( ; i<length ; i = i+1){
            var node = nl[i];
            if (index===node["index"]){
                return node;
            }
        }
        nl = tree["node_list"];
        i = 0;
        for ( ; i<length ; i = i+1){
            found_tree = TREE_getTreeAccordingToIndex(nl[i],index);
            if (found_tree!==null){
                return found_tree;
            }
        }
    }
    return null;
}
TREE_print = function(tree){
    process["stdout"].write("("+tree["token_class"]+" "+tree["name"]);
    var length_of_node_list = len(tree["node_list"]);
    if (length_of_node_list!==0){
        var i = 0;
        var nl = tree["node_list"];
        for (i = 0 ; i<length_of_node_list ; i = i+1){
            TREE_print(nl[i]);
        }
    }
    process["stdout"].write(")");
}
TREE_changeNameAccordingToIndex = function(tree,index,change_to_name){
    var temp_tree = TREE_getTreeAccordingToIndex(tree,index);
    temp_tree["name"] = change_to_name;
}
TREE_layer = function(tree){
    var temp_tree = TREE_getTreeAccordingToIndex(tree,TREE_INDEX);
    return temp_tree["layer"];
}
TREE_addNodeAtIndex = function(tree,index,add_name,add_token_class){
    var temp_tree = TREE_getTreeAccordingToIndex(tree,index);
    TREE_addNode(temp_tree,add_name,add_token_class);
}
elements = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    var index_of_comma = TL_indexOfTokenThatHasTokenString(tl,",");
    if (index_of_comma===-1){
        var index_of_tl = TREE_INDEX;
        TREE_addNode(tree,"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index_of_tl),tl);
    }
    else{
        var tl1 = tl.slice(0,index_of_comma);
        var tl2 = tl.slice(index_of_comma+1,length_of_tl);
        var index_of_tl1 = TREE_INDEX;
        TREE_addNode(tree,"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index_of_tl1),tl1)&&elements(tree,tl2);
    }
}
value = function(tree,tl){
    if (INCOMPLETE_STATEMENT){
        return false;
    }
    var length_of_tl = len(tl);
    if (length_of_tl===0){
        tree["name"] = "none";
        tree["token_class"] = "id";
        return true;
    }
    else if (length_of_tl===1){
        if ((("num"===tl[0]["TOKEN_CLASS"] || "string"===tl[0]["TOKEN_CLASS"]) || "id"===tl[0]["TOKEN_CLASS"])){
            tree["name"] = tl[0]["TOKEN_STRING"];
            tree["token_class"] = tl[0]["TOKEN_CLASS"];
            return true;
            }
        else if ("list_table"===tl[0]["TOKEN_CLASS"]){
            tree["name"] = tl[0]["TOKEN_STRING"];
            tree["token_class"] = "table";
            var key_index = {val:0};
            return table(tree,tl,key_index);
            }
        else{
            return false;
        }
    }
    else{
        return (((func_value(tree,tl) || table_value(tree,tl)) || func(tree,tl)) || relation(tree,tl))||expr(tree,tl);
    }
}
new_value = function(tree,tl){
    if (tl[0]["TOKEN_STRING"]==="new"){
        tree["name"] = "new_value";
        tree["token_class"] = "";
        tl[0]["TOKEN_STRING"] = ".";
        tl[0]["TOKEN_CLASS"] = "dot";
        return table_value_key(tree,tl);
    }
    return false;
}
table_elements = function(tree,tl,key_index){
    if (INCOMPLETE_STATEMENT){
        return false;
    }
    var length_of_tl = len(tl);
    var i = 0;
    var index_of_comma = -1;
    var count = 0;
    for (i = 0 ; i<length_of_tl ; i = i+1){
        if (tl[i]["TOKEN_STRING"]==="("){
            count++;
            continue;
        }
        if (tl[i]["TOKEN_STRING"]===")"){
            count--;
            continue;
        }
        if ((count===0 && tl[i]["TOKEN_STRING"]===",")){
            index_of_comma = i;
            break;
        }
    }
    if (index_of_comma!==-1){
        table_expr_tl = tl.slice(0,index_of_comma);
        table_elements_tl = tl.slice(index_of_comma+1,length_of_tl);
        var index1 = TREE_INDEX;
        TREE_addNode(tree,"table_expr","");
        return table_expr(TREE_getTreeAccordingToIndex(tree,index1),table_expr_tl,key_index)&&table_elements(tree,table_elements_tl,key_index);
    }
    else{
        var index = TREE_INDEX;
        TREE_addNode(tree,"table_expr","");
        return table_expr(TREE_getTreeAccordingToIndex(tree,index),tl,key_index);
    }
}
table_expr = function(tree,tl,key_index){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if ((((3<length_of_tl && term(tl[0]["TOKEN_CLASS"],"@")) && term(tl[1]["TOKEN_CLASS"],"id")) && term(tl[2]["TOKEN_STRING"],"="))){
        var append_key = tl[1]["TOKEN_STRING"];
        var length_of_append_key = len(append_key);
        var new_key = "@"+append_key;
        TREE_addNode(tree,new_key,"key");
        var index = TREE_INDEX;
        TREE_addNode(tree,"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index),tl.slice(3,length_of_tl));
    }
    else if ((term(tl[0]["TOKEN_CLASS"],"id") && term(tl[1]["TOKEN_STRING"],"="))){
        var index1 = TREE_INDEX;
        TREE_addNode(tree,"key","");
        var key_tl = Walley_Lexical_Analyzie(toString(tl[0]["TOKEN_STRING"]));
        var key_tree = TREE_init("key");
        value(key_tree,key_tl);
        TREE_addTree(TREE_getTreeAccordingToIndex(tree,index1),key_tree);
        var index2 = TREE_INDEX;
        TREE_addNode(tree,"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index2),tl.slice(2,length_of_tl));
    }
    else if (((term(tl[0]["TOKEN_CLASS"],"list_table") && typeof(tl[1])!=="undefined") && term(tl[1]["TOKEN_STRING"],"="))){
        var length = len(tl[0]["TOKEN_STRING"]);
        var string_inside = tl[0]["TOKEN_STRING"].slice(1,length-1);
        var index1 = TREE_INDEX;
        TREE_addNode(tree,"key","");
        var key_tl = Walley_Lexical_Analyzie(string_inside);
        TREE;
        key_tree = TREE_init("key");
        value(key_tree,key_tl);
        TREE_addTree(TREE_getTreeAccordingToIndex(tree,index1),key_tree);
        var index2 = TREE_INDEX;
        TREE_addNode(tree,"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index2),tl.slice(2,length_of_tl));
    }
    else{
        var index1 = TREE_INDEX;
        TREE_addNode(tree,"key","");
        var key_tl = Walley_Lexical_Analyzie(key_index["val"]+"");
        var key_tree = TREE_init("key");
        value(key_tree,key_tl);
        TREE_addTree(TREE_getTreeAccordingToIndex(tree,index1),key_tree);
        var index = TREE_INDEX;
        TREE_addNode(tree,"value","");
        key_index["val"] = key_index["val"]+1;
        return value(TREE_getTreeAccordingToIndex(tree,index),tl);
    }
    return false;
}
table = function(tree,tl,key_index){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if (length_of_tl===1){
        var list_string = tl[0]["TOKEN_STRING"];
        var length_of_list_string = len(list_string);
        if ((list_string[0]==="[" && list_string[length_of_list_string-1]==="]")){
            var list_string2 = list_string.slice(1,len(list_string)-1).trim();
            if (list_string2===""){
                return true;
            }
            var table_tl = Walley_Lexical_Analyzie(list_string2);
            return table_elements(tree,table_tl,key_index);
            }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}
table_value = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    var i = 0;
    var count = 0;
    for (i = 0 ; i<length_of_tl ; i = i+1){
        if (term(tl[i]["TOKEN_STRING"],"(")){
            count = count+1;
            }
        else if (term(tl[i]["TOKEN_STRING"],")")){
            count = count-1;
        }
        if ((count===0 && term(tl[i]["TOKEN_CLASS"],"m_operator"))){
            return false;
        }
    }
    if (((2<=length_of_tl && (((term(tl[0]["TOKEN_CLASS"],"id") || term(tl[0]["TOKEN_CLASS"],"string")) || term(tl[0]["TOKEN_CLASS"],"list_table")) || term(tl[0]["TOKEN_CLASS"],"num"))) && (term(tl[1]["TOKEN_STRING"],".") || term(tl[1]["TOKEN_CLASS"],"list_table")))){
        var index1 = TREE_INDEX;
        TREE_addNode(tree,"table_value","");
        var index2 = TREE_INDEX;
        TREE_addNode(TREE_getTreeAccordingToIndex(tree,index1),"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index2),tl.slice(0,1))&&table_value_key(TREE_getTreeAccordingToIndex(tree,index1),tl.slice(1,length_of_tl));
    }
    else if (((3<=length_of_tl && term(tl[0]["TOKEN_CLASS"],"id")) && term(tl[1]["TOKEN_STRING"],"("))){
        var index = -1;
        var i = 0;
        var count = 0;
        for (i = 0 ; i<len(tl) ; i = i+1){
            if (term(tl[i]["TOKEN_STRING"],"(")){
                count = count+1;
                    }
            else if (term(tl[i]["TOKEN_STRING"],")")){
                count = count-1;
                if (count===0){
                    index = i;
                    break;
                }
            }
        }
        if (index===length_of_tl-1){
            return false;
        }
        if ((typeof(tl[i+1])!=="undefined" && term(tl[i+1]["TOKEN_CLASS"],"relation"))){
            return false;
        }
        var tree_index = TREE_INDEX;
        TREE_addNode(tree,"table_value","");
        var tree_index2 = TREE_INDEX;
        TREE_addNode(TREE_getTreeAccordingToIndex(tree,tree_index),"func","");
        func(TREE_getTreeAccordingToIndex(tree,tree_index2),tl.slice(0,index+1));
        return table_value_key(TREE_getTreeAccordingToIndex(tree,tree_index),tl.slice(index+1,length_of_tl));
    }
    else{
        if (term(tl[0]["TOKEN_STRING"],"(")){
            var index_of_right = -1;
            var i = 0;
            var count = 0;
            for (i = 0 ; i<len(tl) ; i = i+1){
                if (term(tl[i]["TOKEN_STRING"],"(")){
                    count = count+1;
                            }
                else if (term(tl[0]["TOKEN_STRING"],")")){
                    count = count-1;
                    if (count===0){
                        index_of_right = i;
                        break;
                    }
                }
            }
            if (index_of_right===-1){
                return false;
                    }
            else{
                if (index_of_right===length_of_tl-1){
                    return false;
                }
                if ((term(tl[index_of_right+1]["TOKEN_CLASS"],"list_table")===false || term(tl[index_of_right+1]["TOKEN_STRING"],".")===false)){
                    return false;
                }
                var index = TREE_INDEX;
                TREE_addNode(tree,"table_value","");
                var index2 = TREE_INDEX;
                TREE_addNode(TREE_getTreeAccordingToIndex(tree,index),"expr","");
                return expr(TREE_getTreeAccordingToIndex(tree,index2),tl.slice(0,index_of_right+1))&&table_value_key(TREE_getTreeAccordingToIndex(tree,index),tl.slice(index_of_right+1,length_of_tl));
            }
        }
        return false;
    }
}
table_value_key = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if ((length_of_tl===1 && term(tl[0]["TOKEN_CLASS"],"list_table"))){
        var length = len(tl[0]["TOKEN_STRING"]);
        var string_inside = tl[0]["TOKEN_STRING"].slice(1,length-1);
        var key_tl = Walley_Lexical_Analyzie(string_inside);
        var index_of_colon = -1;
        var i = 0;
        for (i = 0 ; i<len(key_tl) ; i = i+1){
            if (term(key_tl[i]["TOKEN_STRING"],":")){
                index_of_colon = i;
                break;
            }
        }
        if (index_of_colon===-1){
            var index1 = TREE_INDEX;
            TREE_addNode(tree,"key","");
            var key_tree = TREE_init(key_tree,"key");
            value(key_tree,key_tl);
            TREE_addTree(TREE_getTreeAccordingToIndex(tree,index1),key_tree);
            return true;
            }
        else{
            var length_of_key_tl = len(key_tl);
            var index1 = TREE_INDEX;
            TREE_addNode(tree,"key","");
            var slice_tree = TREE_init("slice");
            var left_tl = null;
            var right_tl = null;
            if (index_of_colon===0){
                left_tl = null;
                    }
            else{
                left_tl = key_tl.slice(0,index_of_colon);
            }
            if (index_of_colon===length_of_key_tl-1){
                right_tl = null;
                    }
            else{
                right_tl = key_tl.slice(index_of_colon+1,length_of_key_tl);
            }
            var index_left = TREE_INDEX;
            if (left_tl===null){
                TREE_addNode(slice_tree,"0","num");
                    }
            else{
                TREE_addNode(slice_tree,"value","");
                value(TREE_getTreeAccordingToIndex(slice_tree,index_left),left_tl);
            }
            var index_right = TREE_INDEX;
            if (right_tl===null){
                TREE_addNode(slice_tree,"its_length","special");
                    }
            else{
                TREE_addNode(slice_tree,"value","");
                value(TREE_getTreeAccordingToIndex(slice_tree,index_right),right_tl);
            }
            TREE_addTree(TREE_getTreeAccordingToIndex(tree,index1),slice_tree);
            return true;
        }
    }
    else if (((length_of_tl===2 && term(tl[0]["TOKEN_STRING"],".")) && term(tl[1]["TOKEN_CLASS"],"id"))){
        var index1 = TREE_INDEX;
        TREE_addNode(tree,"key","");
        var key_tl = Walley_Lexical_Analyzie(toString(tl[1]["TOKEN_STRING"]));
        var key_tree = TREE_init("key");
        value(key_tree,key_tl);
        TREE_addTree(TREE_getTreeAccordingToIndex(tree,index1),key_tree);
        return true;
    }
    else if ((((4<=length_of_tl && term(tl[0]["TOKEN_STRING"],".")) && term(tl[1]["TOKEN_CLASS"],"id")) && term(tl[2]["TOKEN_STRING"],"("))){
        var index_of_right = -1;
        var i = 0;
        var count = 0;
        for (i = 0 ; i<len(tl) ; i = i+1){
            if (term(tl[i]["TOKEN_STRING"],"(")){
                count = count+1;
                    }
            else if (term(tl[i]["TOKEN_STRING"],")")){
                count = count-1;
                if (count===0){
                    index_of_right = i;
                    break;
                }
            }
        }
        if (index_of_right===-1){
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        if (index_of_right===length_of_tl-1){
            var index1 = TREE_INDEX;
            TREE_addNode(tree,"key","");
            return func(TREE_getTreeAccordingToIndex(tree,index1),tl.slice(1,length_of_tl));
            }
        else{
            return table_value_key(tree,tl.slice(0,index_of_right+1))&&table_value_key(tree,tl.slice(index_of_right+1,length_of_tl));
        }
    }
    else if (((2<=length_of_tl && term(tl[0]["TOKEN_CLASS"],"list_table")) && (term(tl[1]["TOKEN_STRING"],".") || term(tl[1]["TOKEN_CLASS"],"list_table")))){
        return table_value_key(tree,tl.slice(0,1))&&table_value_key(tree,tl.slice(1,length_of_tl));
    }
    else if (((3<=length_of_tl && term(tl[0]["TOKEN_CLASS"],"list_table")) && term(tl[1]["TOKEN_STRING"],"("))){
        var index = -1;
        var i = 0;
        var count = 0;
        for (i = 0 ; i<len(tl) ; i = i+1){
            if (term(tl[i]["TOKEN_STRING"],"(")){
                count = count+1;
                    }
            else if (term(tl[i]["TOKEN_STRING"],")")){
                count = count-1;
                if (count===0){
                    index = i;
                    break;
                }
            }
        }
        if (index===-1){
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        var func_tree = TREE_init("func");
        var tree_index = TREE_INDEX;
        TREE_addNode(func_tree,"","table_call");
        TREE_addNode(TREE_getTreeAccordingToIndex(func_tree,tree_index),"","");
        tree_index = tree_index+1;
        var length = len(tl[0]["TOKEN_STRING"]);
        var string_inside = tl[0]["TOKEN_STRING"].slice(1,length-1);
        var string_inside_tl = Walley_Lexical_Analyzie(string_inside);
        value(TREE_getTreeAccordingToIndex(func_tree,tree_index),string_inside_tl);
        tree_index = TREE_INDEX;
        TREE_addNode(func_tree,"params","");
        if (2!==index){
            params(TREE_getTreeAccordingToIndex(func_tree,tree_index),tl.slice(2,index));
        }
        TREE_addTree(tree,func_tree);
        if (index===length_of_tl-1){
            return true;
        }
        return table_value(tree,tl.slice(index+1,length_of_tl));
    }
    else if ((((3<=length_of_tl && term(tl[0]["TOKEN_STRING"],".")) && term(tl[1]["TOKEN_CLASS"],"id")) && (term(tl[2]["TOKEN_STRING"],".") || term(tl[2]["TOKEN_CLASS"],"list_table")))){
        return table_value_key(tree,tl.slice(0,2))&&table_value_key(tree,tl.slice(2,length_of_tl));
    }
    else{
        return false;
    }
}
expr = function(tree,tl){
    if (INCOMPLETE_STATEMENT){
        return false;
    }
    var length_of_tl = len(tl);
    var count_of_parenthesis = 0;
    var i = length_of_tl-1;
    for ( ; 0<=i ; i = i-1){
        if (tl[i]["TOKEN_STRING"]==="("){
            count_of_parenthesis = count_of_parenthesis+1;
            continue;
        }
        if (tl[i]["TOKEN_STRING"]===")"){
            count_of_parenthesis = count_of_parenthesis-1;
            continue;
        }
        if ((count_of_parenthesis===0 && ("+"===tl[i]["TOKEN_STRING"] || "-"===tl[i]["TOKEN_STRING"]))){
            var sign = tl[i]["TOKEN_STRING"];
            var index_of_first_sign = i;
            if (index_of_first_sign===0){
                temp_tl = {};
                var temp_token = Token_init();
                temp_token["TOKEN_STRING"] = "0";
                temp_token["TOKEN_CLASS"] = "num";
                temp_token["TOKEN_START"] = -1;
                temp_token["TOKEN_END"] = -1;
                temp_tl.append(temp_token);
                var a = 0;
                for (a = 0 ; a<len(tl) ; a = a+1){
                    temp_tl.append(tl[a]);
                }
                return expr(tree,temp_tl);
            }
            var tl1 = tl.slice(0,index_of_first_sign);
            var tl2 = tl.slice(index_of_first_sign+1,length_of_tl);
            tree["name"] = sign;
            var index_of_expr1_node = TREE_INDEX;
            TREE_addNode(tree,"expr","");
            var index_of_expr2_node = TREE_INDEX;
            TREE_addNode(tree,"expr","");
            return expr(TREE_getTreeAccordingToIndex(tree,index_of_expr1_node),tl1)&&expr(TREE_getTreeAccordingToIndex(tree,index_of_expr2_node),tl2);
        }
    }
    return s_term(tree,tl);
}
s_term = function(tree,tl){
    if (INCOMPLETE_STATEMENT){
        return false;
    }
    var length_of_tl = len(tl);
    var count_of_parenthesis = 0;
    var i = length_of_tl-1;
    for ( ; 0<=i ; i = i-1){
        if (tl[i]["TOKEN_STRING"]==="("){
            count_of_parenthesis = count_of_parenthesis+1;
            continue;
        }
        if (tl[i]["TOKEN_STRING"]===")"){
            count_of_parenthesis = count_of_parenthesis-1;
            continue;
        }
        if ((count_of_parenthesis===0 && (("*"===tl[i]["TOKEN_STRING"] || "/"===tl[i]["TOKEN_STRING"]) || "%"===tl[i]["TOKEN_STRING"]))){
            var sign = tl[i]["TOKEN_STRING"];
            var index_of_first_sign = i;
            var tl1 = tl.slice(0,index_of_first_sign);
            var tl2 = tl.slice(index_of_first_sign+1,length_of_tl);
            tree["name"] = sign;
            var current_index = tree["index"];
            TREE_addNode(tree,"s_term","");
            TREE_addNodeAtIndex(tree,current_index,"p_term","");
            var index_of_node1 = TREE_INDEX-2;
            var index_of_node2 = TREE_INDEX-1;
            return s_term(TREE_getTreeAccordingToIndex(tree,index_of_node1),tl1)&&p_term(TREE_getTreeAccordingToIndex(tree,index_of_node2),tl2);
        }
    }
    return p_term(tree,tl);
}
p_term = function(tree,tl){
    if (INCOMPLETE_STATEMENT){
        return false;
    }
    var length_of_tl = len(tl);
    var count_of_parenthesis = 0;
    var i = length_of_tl-1;
    for ( ; 0<=i ; i = i-1){
        if (tl[i]["TOKEN_STRING"]==="("){
            count_of_parenthesis = count_of_parenthesis+1;
            continue;
        }
        if (tl[i]["TOKEN_STRING"]===")"){
            count_of_parenthesis = count_of_parenthesis-1;
            continue;
        }
        if ((count_of_parenthesis===0 && ("^"===tl[i]["TOKEN_STRING"] || "**"===tl[i]["TOKEN_STRING"]))){
            var sign = "^";
            var index_of_first_sign = i;
            var tl1 = tl.slice(0,index_of_first_sign);
            var tl2 = tl.slice(index_of_first_sign+1,length_of_tl);
            tree["name"] = sign;
            var current_index = tree["index"];
            TREE_addNode(tree,"p_term","");
            TREE_addNodeAtIndex(tree,current_index,"factor","");
            var index_of_node1 = TREE_INDEX-2;
            var index_of_node2 = TREE_INDEX-1;
            return p_term(TREE_getTreeAccordingToIndex(tree,index_of_node1),tl1)&&factor(TREE_getTreeAccordingToIndex(tree,index_of_node2),tl2);
        }
    }
    return factor(tree,tl);
}
factor = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if ((term(tl[0]["TOKEN_STRING"],"(") && term(tl[length_of_tl-1]["TOKEN_STRING"],")"))){
        tree["name"] = "expr";
        tree["token_class"] = "";
        return expr(tree,TL_subtl(tl,1,length_of_tl-1));
    }
    else{
        return new_value(tree,tl)||value(tree,tl);
    }
}
assignment = function(tree,tl){
    var test = self_operator_stm(tree,tl)||self_assignment_stm(tree,tl);
    if (test===true){
        return true;
    }
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var is_local = false;
    if (term(tl[0]["TOKEN_STRING"],"local")){
        is_local = true;
    }
    var count = 0;
    var count_of_equal = 0;
    var index_of_equal = -1;
    var i = 0;
    for (i = 0 ; i<len(tl) ; i = i+1){
        if (((((term(tl[i]["TOKEN_STRING"],"(") || term(tl[i]["TOKEN_STRING"],"if")) || term(tl[i]["TOKEN_STRING"],"def")) || term(tl[i]["TOKEN_STRING"],"for")) || term(tl[i]["TOKEN_STRING"],"while"))){
            count = count+1;
            }
        else if ((term(tl[i]["TOKEN_STRING"],")") || term(tl[i]["TOKEN_STRING"],"end"))){
            count = count-1;
        }
        if ((count===0 && tl[i]["TOKEN_STRING"]==="=")){
            count_of_equal = count_of_equal+1;
            index_of_equal = i;
        }
    }
    if (count_of_equal!==1){
        return false;
    }
    else{
        var length_of_tl = len(tl);
        var save_TREE_INDEX = TREE_INDEX;
        TREE_INDEX = 0;
        var var_name_tree = TREE_init("var_name");
        var var_name_list = {};
        if (is_local===true){
            var_name_list = tl.slice(1,index_of_equal);
            }
        else{
            var_name_list = tl.slice(0,index_of_equal);
        }
        var_name(var_name_tree,var_name_list);
        TREE_INDEX = 0;
        var var_value_tree = TREE_init("var_value");
        var var_value_list = tl.slice(index_of_equal+1,length_of_tl);
        var_value(var_value_tree,var_value_list);
        TREE_INDEX = save_TREE_INDEX;
        var var_name_num = len(var_name_tree["node_list"]);
        var i = 0;
        var var_name_nl = var_name_tree["node_list"];
        var var_value_nl = var_value_tree["node_list"];
        for ( ; i<var_name_num ; i = i+1){
            var index = TREE_INDEX;
            TREE_addNode(tree,"=","");
            if (is_local===true){
                TREE_addNode(TREE_getTreeAccordingToIndex(tree,index),"local","");
            }
            TREE_addTree(TREE_getTreeAccordingToIndex(tree,index),var_name_nl[i]);
            if (typeof(var_value_nl[i])==="undefined"){
                var temp_tree = TREE_init();
                temp_tree["name"] = "none";
                temp_tree["token_class"] = "id";
                temp_tree["node_list"] = {};
                TREE_addTree(TREE_getTreeAccordingToIndex(tree,index),temp_tree);
                    }
            else{
                TREE_addTree(TREE_getTreeAccordingToIndex(tree,index),var_value_nl[i]);
            }
        }
        return true;
    }
}
var_name = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var index_of_comma = TL_indexOfTokenThatHasTokenString(tl,",");
    if (index_of_comma!==-1){
        var length_of_tl = len(tl);
        var tl1 = tl.slice(0,index_of_comma);
        var tl2 = tl.slice(index_of_comma+1,length_of_tl);
        return var_name(tree,tl1)&&var_name(tree,tl2);
    }
    else{
        var length_of_tl = len(tl);
        if (length_of_tl===1){
            if ("id"===tl[0]["TOKEN_CLASS"]){
                TREE_addNode(tree,tl[0]["TOKEN_STRING"],"id");
                return true;
                    }
            else{
                return false;
            }
            }
        else{
            return table_value(tree,tl);
        }
    }
    return false;
}
var_value = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    var index_of_comma = -1;
    var i = 0;
    var count = 0;
    for ( ; i<length_of_tl ; i = i+1){
        if (((((term(tl[i]["TOKEN_STRING"],"def") || term(tl[i]["TOKEN_STRING"],"for")) || term(tl[i]["TOKEN_STRING"],"if")) || term(tl[i]["TOKEN_STRING"],"while")) || term(tl[i]["TOKEN_STRING"],"("))){
            count = count+1;
        }
        if ((term(tl[i]["TOKEN_STRING"],"end") || term(tl[i]["TOKEN_STRING"],")"))){
            count = count-1;
        }
        if ((count===0 && term(tl[i]["TOKEN_STRING"],","))){
            index_of_comma = i;
            break;
        }
    }
    if (count!==0){
        INCOMPLETE_STATEMENT = true;
        return false;
    }
    if (index_of_comma!==-1){
        var tl1 = tl.slice(0,index_of_comma);
        var tl2 = tl.slice(index_of_comma+1,length_of_tl);
        var index_of_tl1 = TREE_INDEX;
        TREE_addNode(tree,"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index_of_tl1),tl1)&&var_value(tree,tl2);
    }
    else{
        var index_of_tl = TREE_INDEX;
        TREE_addNode(tree,"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index_of_tl),tl);
    }
}
func_assign = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if (((4<=length_of_tl && term(tl[0]["TOKEN_STRING"],"def")) && term(tl[1]["TOKEN_STRING"],"("))){
        var index_of_right = -1;
        var count = 0;
        var i = 0;
        for ( ; i<length_of_tl ; i = i+1){
            if (term(tl[i]["TOKEN_STRING"],"(")){
                count = count+1;
            }
            if (term(tl[i]["TOKEN_STRING"],")")){
                count = count-1;
                if (count===0){
                    index_of_right = i;
                    break;
                }
            }
        }
        if (index_of_right===-1){
            INCOMPLETE_STATEMENT = true;
            console.log("INCOMPLETE_STATEMENT func_assign\n");
            process.exit(0);
            }
        else{
            TREE_addNode(tree,"def","");
            var index = TREE_INDEX;
            TREE_addNode(tree,"params","");
            var params_tl = {};
            if (index_of_right!==2){
                params_tl = tl.slice(2,index_of_right);
                    }
            else{
                params_tl = {};
                var add_token = Token_init();
                add_token["TOKEN_CLASS"] = "id";
                add_token["TOKEN_STRING"] = "none";
                params_tl.append(add_token);
            }
            return params(TREE_getTreeAccordingToIndex(tree,index),params_tl);
        }
    }
    return false;
}
return_stm = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if ((2<=length_of_tl && term(tl[0]["TOKEN_STRING"],"return"))){
        var index1 = TREE_INDEX;
        TREE_addNode(tree,"return","");
        var index2 = TREE_INDEX;
        TREE_addNode(TREE_getTreeAccordingToIndex(tree,index1),"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index2),tl.slice(1,length_of_tl));
    }
    return false;
}
func_value = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if ((term(tl[0]["TOKEN_STRING"],"def") && term(tl[length_of_tl-1]["TOKEN_STRING"],"end"))){
        tree["name"] = "func_value";
        tree["token_class"] = "";
        var index_of_then = TL_indexOfTokenThatHasTokenString(tl,"then");
        if (index_of_then===-1){
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        func_assign(tree,tl.slice(0,index_of_then+1));
        var walley_statements_index = TREE_INDEX;
        TREE_addNode(tree,"walley_statements","");
        return walley_statements(TREE_getTreeAccordingToIndex(tree,walley_statements_index),tl.slice(index_of_then+1,length_of_tl-1))&&end_stm(tree,tl.slice(length_of_tl-1,length_of_tl));
    }
    return false;
}
params = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    if (len(tl)===0){
        return true;
    }
    var length_of_tl = len(tl);
    var index_of_comma = -1;
    var count = 0;
    var i = 0;
    for (i = 0 ; i<length_of_tl ; i = i+1){
        if (term(tl[i]["TOKEN_STRING"],"(")){
            count = count+1;
            continue;
        }
        if (term(tl[i]["TOKEN_STRING"],")")){
            count = count-1;
            continue;
        }
        if ((count===0 && term(tl[i]["TOKEN_STRING"],","))){
            index_of_comma = i;
            break;
        }
    }
    if (index_of_comma===-1){
        if (assignment(tree,tl)===true){
            return true;
            }
        else{
            var index = TREE_INDEX;
            TREE_addNode(tree,"value","");
            return value(TREE_getTreeAccordingToIndex(tree,index),tl);
        }
    }
    else{
        var tl1 = tl.slice(0,index_of_comma);
        var tl2 = tl.slice(index_of_comma+1,length_of_tl);
        if (assignment(tree,tl1)===true){
            return params(tree,tl2);
            }
        else{
            var index_of_tl1 = TREE_INDEX;
            TREE_addNode(tree,"value","");
            return value(TREE_getTreeAccordingToIndex(tree,index_of_tl1),tl1)&&params(tree,tl2);
        }
    }
}
func = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    var index_of_left = TL_indexOfTokenThatHasTokenString(tl,"(");
    var index_of_right = -1;
    if (index_of_left===-1){
        return false;
    }
    var i = 0;
    var count = 0;
    for ( ; i<length_of_tl ; i = i+1){
        if (term(tl[i]["TOKEN_STRING"],"(")){
            count = count+1;
            }
        else if (term(tl[i]["TOKEN_STRING"],")")){
            count = count-1;
            if (count===0){
                index_of_right = i;
                break;
            }
        }
    }
    if (index_of_right===-1){
        INCOMPLETE_STATEMENT = true;
        return false;
    }
    if (((index_of_right+1!==length_of_tl || index_of_left===-1) || index_of_left===0)){
        return false;
    }
    else{
        var test_id = tl.slice(0,index_of_left);
        var params_tl = {};
        if (index_of_left+1===index_of_right){
            params_tl = {};
            }
        else{
            params_tl = tl.slice(index_of_left+1,index_of_right);
        }
        var length_of_test_id = len(test_id);
        if ((length_of_test_id!==1 || test_id[0]["TOKEN_CLASS"]!=="id")){
            return false;
        }
        tree["name"] = "func";
        tree["token_class"] = "";
        TREE_addNode(tree,"","call");
        TREE_addNode(TREE_getTreeAccordingToIndex(tree,TREE_INDEX-1),toString(test_id[0]["TOKEN_STRING"]),"string");
        var index = TREE_INDEX;
        TREE_addNode(tree,"params","");
        return params(TREE_getTreeAccordingToIndex(tree,index),params_tl);
    }
}
relation = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    var i = length_of_tl-1;
    var count = 0;
    var index_of_and_or = -1;
    for ( ; 0<=i ; i = i-1){
        if (term(tl[i]["TOKEN_STRING"],"(")){
            count = count+1;
            continue;
        }
        if (term(tl[i]["TOKEN_STRING"],")")){
            count = count-1;
            continue;
        }
        if (((count===0 && term(tl[i]["TOKEN_CLASS"],"relation")) && tl[i]["TOKEN_STRING"]!=="not")){
            index_of_and_or = i;
            var and_or_string = tl[i]["TOKEN_STRING"];
            var tl1 = tl.slice(0,index_of_and_or);
            var tl2 = tl.slice(index_of_and_or+1,length_of_tl);
            var index = TREE_INDEX;
            TREE_addNode(tree,and_or_string,"");
            var index1 = TREE_INDEX;
            TREE_addNodeAtIndex(tree,index,"relation","");
            var index2 = TREE_INDEX;
            TREE_addNodeAtIndex(tree,index,"relation","");
            return relation(TREE_getTreeAccordingToIndex(tree,index1),tl1)&&relation(TREE_getTreeAccordingToIndex(tree,index2),tl2);
        }
    }
    if (term(tl[0]["TOKEN_STRING"],"not")){
        TREE_addNode(tree,"not","");
        var index = TREE_INDEX;
        TREE_addNodeAtIndex(tree,index-1,"relation","");
        return relation(TREE_getTreeAccordingToIndex(tree,index),tl.slice(1,length_of_tl));
    }
    return simple_relation(tree,tl);
}
simple_relation = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if ((term("(",tl[0]["TOKEN_STRING"]) && term(")",tl[length_of_tl-1]["TOKEN_STRING"]))){
        return relation(tree,tl.slice(1,length_of_tl-1));
    }
    else{
        tree["name"] = "simple_relation";
        var index_of_judge_sign = TL_indexOfTokenThatHasTokenClass(tl,"judge_sign");
        if (index_of_judge_sign===-1){
            return expr(tree,tl);
        }
        var tl1 = tl.slice(0,index_of_judge_sign);
        var tl2 = tl.slice(index_of_judge_sign+1,length_of_tl);
        var judge_sign = tl[index_of_judge_sign]["TOKEN_STRING"];
        if ((term(">=",judge_sign) || term(">",judge_sign))){
            var temp_tl = tl1;
            tl1 = tl2;
            tl2 = temp_tl;
            if (term(">=",judge_sign)){
                judge_sign = "<=";
                    }
            else{
                judge_sign = "<";
            }
        }
        var index = TREE_INDEX;
        TREE_addNode(tree,judge_sign,"");
        var temp_tree = TREE_getTreeAccordingToIndex(tree,index);
        var index1 = TREE_INDEX;
        TREE_addNode(temp_tree,"value","");
        var index2 = TREE_INDEX;
        TREE_addNode(temp_tree,"value","");
        return value(TREE_getTreeAccordingToIndex(tree,index1),tl1)&&value(TREE_getTreeAccordingToIndex(tree,index2),tl2);
    }
    return false;
}
if_stms = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if (term(tl[0]["TOKEN_STRING"],"if")){
        var index_of_then = TL_indexOfTokenThatHasTokenString(tl,"then");
        if (index_of_then===-1){
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        if ((term(tl[length_of_tl-1]["TOKEN_STRING"],"end") && 2<length_of_tl)){
            var relation_tl = tl.slice(1,index_of_then);
            TREE_addNode(tree,"if","");
            var index = TREE_INDEX;
            TREE_addNode(tree,"relation","");
            var walley_statements_index = TREE_INDEX;
            TREE_addNode(tree,"walley_statements","");
            return relation(TREE_getTreeAccordingToIndex(tree,index),relation_tl)&&walley_statements(TREE_getTreeAccordingToIndex(tree,walley_statements_index),tl.slice(index_of_then+1,length_of_tl-1));
            }
        else{
            INCOMPLETE_STATEMENT = true;
            return false;
        }
    }
    return false;
}
elif_stms = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if (term(tl[0]["TOKEN_STRING"],"elif")){
        var index_of_then = TL_indexOfTokenThatHasTokenString(tl,"then");
        if (index_of_then===-1){
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        if ((term(tl[length_of_tl-1]["TOKEN_STRING"],"end") && 2<length_of_tl)){
            var relation_tl = tl.slice(1,index_of_then);
            TREE_addNode(tree,"elif","");
            var index = TREE_INDEX;
            TREE_addNode(tree,"relation","");
            var walley_statements_index = TREE_INDEX;
            TREE_addNode(tree,"walley_statements","");
            return relation(TREE_getTreeAccordingToIndex(tree,index),relation_tl)&&walley_statements(TREE_getTreeAccordingToIndex(tree,walley_statements_index),tl.slice(index_of_then+1,length_of_tl-1));
            }
        else{
            INCOMPLETE_STATEMENT = true;
            return false;
        }
    }
    return false;
}
else_stms = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if (term(tl[0]["TOKEN_STRING"],"else")){
        if (term(tl[length_of_tl-1]["TOKEN_STRING"],"end")){
            TREE_addNode(tree,"else","");
            var walley_statements_index = TREE_INDEX;
            TREE_addNode(tree,"walley_statements","");
            return walley_statements(TREE_getTreeAccordingToIndex(tree,walley_statements_index),tl.slice(1,length_of_tl-1));
            }
        else{
            INCOMPLETE_STATEMENT = true;
            return false;
        }
    }
    return false;
}
while_stms = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if (term(tl[0]["TOKEN_STRING"],"while")){
        var index_of_then = TL_indexOfTokenThatHasTokenString(tl,"then");
        if (index_of_then===-1){
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        if ((term(tl[length_of_tl-1]["TOKEN_STRING"],"end") && 2<length_of_tl)){
            var relation_tl = tl.slice(1,index_of_then);
            TREE_addNode(tree,"while","");
            var index = TREE_INDEX;
            TREE_addNode(tree,"relation","");
            var walley_statements_index = TREE_INDEX;
            TREE_addNode(tree,"walley_statements","");
            return (relation(TREE_getTreeAccordingToIndex(tree,index),relation_tl) && walley_statements(TREE_getTreeAccordingToIndex(tree,walley_statements_index),tl.slice(index_of_then+1,length_of_tl-1)))&&end_stm(tree,tl.slice(length_of_tl-1,length_of_tl));
            }
        else{
            INCOMPLETE_STATEMENT = true;
            return false;
        }
    }
    return false;
}
for_stms = function(tree,tl){
    if (term(tl[0]["TOKEN_STRING"],"for")===false){
        return false;
    }
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if ((term(tl[4]["TOKEN_STRING"],"in") || term(tl[2]["TOKEN_STRING"],"in"))){
        var index_of_then = -1;
        var i = 0;
        for ( ; i<length_of_tl ; i = i+1){
            if (term(tl[i]["TOKEN_STRING"],"then")){
                index_of_then = i;
                break;
            }
        }
        TREE_addNode(tree,"foreach","");
        if (term(tl[1]["TOKEN_CLASS"],"id")===false){
            Walley_Print_Error(TL_toString(tl),"for each statements error, for i,v in value, i,v must be id",tl[1]["TOKEN_START"]);
        }
        TREE_addNode(tree,tl[1]["TOKEN_STRING"],"foreach_index");
        if (term(tl[2]["TOKEN_STRING"],",")){
            if (term(tl[3]["TOKEN_CLASS"],"id")===false){
                Walley_Print_Error(TL_toString(tl),"for each statements error, for i,v in value, i,v must be id",tl[3]["TOKEN_START"]);
            }
            TREE_addNode(tree,tl[3]["TOKEN_STRING"],"foreach_value");
            var index = TREE_INDEX;
            TREE_addNode(tree,"","foreach_in");
            TREE_addNode(TREE_getTreeAccordingToIndex(tree,index),"value","");
            index = index+1;
            value(TREE_getTreeAccordingToIndex(tree,index),tl.slice(5,index_of_then));
            }
        else{
            TREE_addNode(tree,"","foreach_value");
            var index = TREE_INDEX;
            TREE_addNode(tree,"","foreach_in");
            TREE_addNode(TREE_getTreeAccordingToIndex(tree,index),"value","");
            index = index+1;
            value(TREE_getTreeAccordingToIndex(tree,index),tl.slice(3,index_of_then));
        }
        var walley_statements_index = TREE_INDEX;
        TREE_addNode(tree,"walley_statements","");
        return walley_statements(TREE_getTreeAccordingToIndex(tree,walley_statements_index),tl.slice(index_of_then+1,length_of_tl-1))&&end_stm(tree,tl.slice(length_of_tl-1,length_of_tl));
    }
    var num_of_comma = 0;
    var count_of_p = 0;
    var index_of_comma = {0:-1,1:-1,2:-1};
    var index = 0;
    var i = 0;
    var index_of_then = -1;
    for ( ; i<length_of_tl ; i = i+1){
        if (term(tl[i]["TOKEN_STRING"],"then")){
            index_of_then = i;
            break;
        }
        if (term(tl[i]["TOKEN_STRING"],"(")){
            count_of_p = count_of_p+1;
            continue;
        }
        if (term(tl[i]["TOKEN_STRING"],")")){
            count_of_p = count_of_p-1;
            continue;
        }
        if ((count_of_p===0 && term(tl[i]["TOKEN_STRING"],","))){
            if (index<2){
                index_of_comma[index] = i;
                index = index+1;
            }
            num_of_comma = num_of_comma+1;
        }
    }
    if ((index_of_then===-1 || term(tl[length_of_tl-1]["TOKEN_STRING"],"end")===false)){
        INCOMPLETE_STATEMENT = true;
        return false;
    }
    if (((length_of_tl!==2 && num_of_comma!==0) && num_of_comma<=2)){
        if (num_of_comma===1){
            var simple_relation_tl = tl.slice(1,index_of_comma[0]);
            var assignment_tl = tl.slice(index_of_comma[0]+1,index_of_then);
            TREE_addNode(tree,"for","");
            var index_of_sr = TREE_INDEX;
            TREE_addNode(tree,"simple_relation","");
            var index_of_a = TREE_INDEX;
            TREE_addNode(tree,"assignment","");
            var walley_statements_index = TREE_INDEX;
            TREE_addNode(tree,"walley_statements","");
            return ((simple_relation(TREE_getTreeAccordingToIndex(tree,index_of_sr),simple_relation_tl) && assignment(TREE_getTreeAccordingToIndex(tree,index_of_a),assignment_tl)) && walley_statements(TREE_getTreeAccordingToIndex(tree,walley_statements_index),tl.slice(index_of_then+1,length_of_tl-1)))&&end_stm(tree,tl.slice(length_of_tl-1,length_of_tl));
            }
        else{
            if (term(tl[1]["TOKEN_STRING"],",")){
                var simple_relation_tl = tl.slice(2,index_of_comma[1]);
                var assignment_tl = tl.slice(index_of_comma[1]+1,index_of_then);
                TREE_addNode(tree,"for","");
                var index_of_sr = TREE_INDEX;
                TREE_addNode(tree,"simple_relation","");
                var index_of_a = TREE_INDEX;
                TREE_addNode(tree,"assignment","");
                var walley_statements_index = TREE_INDEX;
                TREE_addNode(tree,"walley_statements","");
                return ((simple_relation(TREE_getTreeAccordingToIndex(tree,index_of_sr),simple_relation_tl) && assignment(TREE_getTreeAccordingToIndex(tree,index_of_a),assignment_tl)) && walley_statements(TREE_getTreeAccordingToIndex(tree,walley_statements_index),tl.slice(index_of_then+1,length_of_tl-1)))&&end_stm(tree,tl.slice(length_of_tl-1,length_of_tl));
                    }
            else{
                var assignment_tl1 = tl.slice(1,index_of_comma[0]);
                var simple_relation_tl = tl.slice(index_of_comma[0]+1,index_of_comma[1]);
                var assignment_tl2 = tl.slice(index_of_comma[1]+1,index_of_then);
                TREE_addNode(tree,"for","");
                var index_of_a_tl1 = TREE_INDEX;
                TREE_addNode(tree,"assignment","");
                var index_of_sr = TREE_INDEX;
                TREE_addNode(tree,"simple_relation","");
                var index_of_a_tl2 = TREE_INDEX;
                TREE_addNode(tree,"assignment","");
                var walley_statements_index = TREE_INDEX;
                TREE_addNode(tree,"walley_statements","");
                return (((assignment(TREE_getTreeAccordingToIndex(tree,index_of_a_tl1),assignment_tl1) && simple_relation(TREE_getTreeAccordingToIndex(tree,index_of_sr),simple_relation_tl)) && assignment(TREE_getTreeAccordingToIndex(tree,index_of_a_tl2),assignment_tl2)) && walley_statements(TREE_getTreeAccordingToIndex(tree,walley_statements_index),tl.slice(index_of_then+1,length_of_tl-1)))&&end_stm(tree,tl.slice(length_of_tl-1,length_of_tl));
            }
        }
    }
    return false;
}
func_stms = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if (term(tl[0]["TOKEN_STRING"],"def")){
        if ((2<length_of_tl && term(tl[length_of_tl-1]["TOKEN_STRING"],"then"))){
            TREE_addNode(tree,"def","");
            var func_tl = tl.slice(1,length_of_tl-1);
            var index = TREE_INDEX;
            TREE_addNode(tree,"func","");
            return func(TREE_getTreeAccordingToIndex(tree,index),func_tl)&&end_stm(tree,tl.slice(length_of_tl-1,length_of_tl));
            }
        else{
            INCOMPLETE_STATEMENT = true;
            return false;
        }
    }
    return false;
}
end_stm = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    if ((len(tl)===1 && term(tl[0]["TOKEN_CLASS"],"end"))){
        TREE_addNode(tree,"end","");
        return true;
    }
    return false;
}
def_stms = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if ((term(tl[0]["TOKEN_STRING"],"def") && term(tl[1]["TOKEN_STRING"],"(")===false)){
        var index_of_then = TL_indexOfTokenThatHasTokenString(tl,"then");
        var index_of_left_bracket = TL_indexOfTokenThatHasTokenString(tl,"(");
        if (index_of_then===-1){
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        if (term(tl[length_of_tl-1]["TOKEN_STRING"],"end")===false){
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        var new_tl = {};
        var begin = 1;
        var i = 0;
        for ( ; i<index_of_left_bracket ; i = i+1){
            if (begin<=i){
                new_tl.append(tl[i]);
            }
        }
        var add_token = Token_init();
        add_token["TOKEN_STRING"] = "=";
        add_token["TOKEN_CLASS"] = "assignment_operator";
        new_tl.append(add_token);
        i = 0;
        for (i = 0 ; i<length_of_tl ; i = i+1){
            if ((begin<=i && i<index_of_left_bracket)){
                continue;
            }
            new_tl.append(tl[i]);
        }
        return assignment(tree,new_tl);
    }
    else{
        return false;
    }
}
self_operator_stm = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    if (tl[length_of_tl-1]["TOKEN_CLASS"]==="self_operator"){
        var index = TREE_INDEX;
        TREE_addNode(tree,"self_operator_stm","");
        var valid_var_name = var_name(TREE_getTreeAccordingToIndex(tree,index),tl.slice(0,length_of_tl-1));
        if (valid_var_name===true){
            TREE_addNode(TREE_getTreeAccordingToIndex(tree,index),tl[length_of_tl-1]["TOKEN_STRING"],"self_operator");
            return true;
            }
        else{
            console.log("Error.. invalid self operation\n");
            process.exit(0);
        }
    }
    else{
        return false;
    }
}
self_assignment_stm = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var length_of_tl = len(tl);
    var index_of_self_assignment_operator = TL_indexOfTokenThatHasTokenClass(tl,"self_assignment");
    if (index_of_self_assignment_operator===-1){
        return false;
    }
    else{
        var var_name_tl = tl.slice(0,index_of_self_assignment_operator);
        var var_value_tl = tl.slice(index_of_self_assignment_operator+1,length_of_tl);
        var temp_tree = TREE_init("self_assignment_stm");
        var valid_var_name = var_name(temp_tree,var_name_tl);
        if (valid_var_name===false){
            return false;
        }
        TREE_addNode(temp_tree,tl[index_of_self_assignment_operator]["TOKEN_STRING"],"self_assignment");
        var index2 = TREE_INDEX;
        TREE_addNode(temp_tree,"","value");
        var valid_var_value = value(TREE_getTreeAccordingToIndex(temp_tree,index2),var_value_tl);
        if (valid_var_value===false){
            return false;
            }
        else{
            TREE_addTree(tree,temp_tree);
            return true;
        }
    }
}
import_stm = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    if (tl[0]["TOKEN_CLASS"]==="import"){
        TREE_addNode(tree,"import","");
        var index = TREE_INDEX;
        var length_of_tl = len(tl);
        if ((length_of_tl!==2 || tl[1]["TOKEN_CLASS"]!=="string")){
            console.log("Error.. only support import statements like 'import \" hello.wy \"'");
            process.exit(0);
        }
        TREE_addNode(tree,tl[1]["TOKEN_STRING"],"import_file");
        return true;
    }
    else{
        return false;
    }
}
statements = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    return (((((((((import_stm(tree,tl) || return_stm(tree,tl)) || if_stms(tree,tl)) || elif_stms(tree,tl)) || else_stms(tree,tl)) || while_stms(tree,tl)) || for_stms(tree,tl)) || def_stms(tree,tl)) || end_stm(tree,tl)) || assignment(tree,tl))||value(tree,tl);
}
walley_statements = function(tree,tl){
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    var temp_tl = {val:{}};
    var begin = {val:0};
    while (sentences_separation(tl,temp_tl,begin)===true){
        if (INCOMPLETE_STATEMENT===true){
            return false;
        }
        var index = TREE_INDEX;
        TREE_addNode(tree,"statements","");
        if (statements(TREE_getTreeAccordingToIndex(tree,index),temp_tl["val"])===false){
            console.log("Walley Statements Parse Error\n");
            return false;
        }
    }
    if (INCOMPLETE_STATEMENT===true){
        return false;
    }
    return true;
}
sentences_separation = function(tl,output_tl,begin){
    var length_of_tl = len(tl);
    if (length_of_tl<=begin["val"]){
        return false;
    }
    i = begin["val"];
    var count_of_parenthesis = 0;
    for ( ; i<length_of_tl ; i = i+1){
        if (tl[i]["TOKEN_STRING"]==="("){
            count_of_parenthesis++;
        }
        if (tl[i]["TOKEN_STRING"]===")"){
            count_of_parenthesis--;
        }
        if ((((count_of_parenthesis===0 && i<length_of_tl-1) && (((((term(tl[i]["TOKEN_CLASS"],"num") || term(tl[i]["TOKEN_CLASS"],"string")) || term(tl[i]["TOKEN_CLASS"],"id")) || term(tl[i]["TOKEN_CLASS"],"list_table")) || term(tl[i]["TOKEN_STRING"],")")) || term(tl[i]["TOKEN_CLASS"],"self_operator"))) && ((((((term(tl[1+i]["TOKEN_CLASS"],"id") || term(tl[1+i]["TOKEN_CLASS"],"num")) || term(tl[i+1]["TOKEN_CLASS"],"return")) || term(tl[i+1]["TOKEN_STRING"],"continue")) || term(tl[1+i]["TOKEN_STRING"],"break")) || term(tl[1+i]["TOKEN_CLASS"],"local")) || term(tl[i+1]["TOKEN_CLASS"],"import")))){
            var end_index = i+1;
            var ahead_tl = tl.slice(begin["val"],end_index);
            output_tl["val"] = ahead_tl;
            begin["val"] = end_index;
            return true;
        }
        if ((count_of_parenthesis===0 && ((term(tl[i]["TOKEN_STRING"],"def") || term(tl[i]["TOKEN_STRING"],"for")) || term(tl[i]["TOKEN_STRING"],"while")))){
            if (begin["val"]!==i){
                if ((term(tl[i]["TOKEN_STRING"],"def") && term(tl[i+1]["TOKEN_STRING"],"("))){
                    console.log("");
                            }
                else{
                    var end_index = i;
                    var ahead_tl = tl.slice(begin["val"],end_index);
                    begin["val"] = end_index;
                    output_tl["val"] = ahead_tl;
                    return true;
                }
            }
            var count = 0;
            for ( ; i<length_of_tl ; i = i+1){
                if ((((term(tl[i]["TOKEN_STRING"],"def") || term(tl[i]["TOKEN_STRING"],"for")) || term(tl[i]["TOKEN_STRING"],"if")) || term(tl[i]["TOKEN_STRING"],"while"))){
                    count = count+1;
                }
                if (term(tl[i]["TOKEN_STRING"],"end")){
                    count = count-1;
                }
                if (count===0){
                    break;
                }
            }
            if (count===0){
                var end_index = i+1;
                var ahead_tl = tl.slice(begin["val"],end_index);
                output_tl["val"] = ahead_tl;
                begin["val"] = end_index;
                return true;
                    }
            else{
                INCOMPLETE_STATEMENT = true;
                return false;
            }
        }
        if (term(tl[i]["TOKEN_STRING"],"if")){
            if (begin["val"]!==i){
                var end_index = i;
                var ahead_tl = tl.slice(begin["val"],end_index);
                begin["val"] = end_index;
                output_tl["val"] = ahead_tl;
                return true;
            }
            var count_of_if = 0;
            var count_of_end = 0;
            for ( ; i<length_of_tl ; i = i+1){
                if ((((term(tl[i]["TOKEN_STRING"],"if") || term(tl[i]["TOKEN_STRING"],"def")) || term(tl[i]["TOKEN_STRING"],"while")) || term(tl[i]["TOKEN_STRING"],"for"))){
                    count_of_if = count_of_if+1;
                    count_of_end = count_of_end+1;
                }
                if (term(tl[i]["TOKEN_STRING"],"end")){
                    count_of_if = count_of_if-1;
                    count_of_end = count_of_end-1;
                }
                if (count_of_end===0){
                    break;
                }
                if ((count_of_if===1 && (term(tl[i]["TOKEN_STRING"],"elif") || term(tl[i]["TOKEN_STRING"],"else")))){
                    var end_index = i;
                    var ahead_tl = tl.slice(begin["val"],end_index);
                    var end_token = Token_init();
                    end_token["TOKEN_STRING"] = "end";
                    end_token["TOKEN_CLASS"] = "end";
                    ahead_tl.append(end_token);
                    begin["val"] = end_index;
                    output_tl["val"] = ahead_tl;
                    return true;
                }
            }
            if ((count_of_if!==count_of_end || count_of_if!==0)){
                INCOMPLETE_STATEMENT = true;
                return false;
                    }
            else{
                var end_index = i+1;
                var ahead_tl = tl.slice(begin["val"],end_index);
                begin["val"] = end_index-1;
                output_tl["val"] = ahead_tl;
                return true;
            }
        }
        if (term(tl[i]["TOKEN_STRING"],"elif")){
            var count_of_if = 0;
            var count_of_end = 0;
            var temp_i = i;
            for ( ; i<length_of_tl ; i = i+1){
                if ((((term(tl[i]["TOKEN_STRING"],"if") || term(tl[i]["TOKEN_STRING"],"def")) || term(tl[i]["TOKEN_STRING"],"while")) || term(tl[i]["TOKEN_STRING"],"for"))){
                    count_of_if = count_of_if+1;
                    count_of_end = count_of_end+1;
                }
                if (term(tl[i]["TOKEN_STRING"],"end")){
                    count_of_end = count_of_end-1;
                    count_of_if = count_of_if-1;
                }
                if (((count_of_if===0 && i!==temp_i) && (term(tl[i]["TOKEN_STRING"],"elif") || term(tl[i]["TOKEN_STRING"],"else")))){
                    var end_index = i;
                    var ahead_tl = tl.slice(begin["val"],end_index);
                    var end_token = Token_init();
                    end_token["TOKEN_STRING"] = "end";
                    end_token["TOKEN_CLASS"] = "end";
                    ahead_tl.append(end_token);
                    begin["val"] = end_index;
                    output_tl["val"] = ahead_tl;
                    return true;
                }
                if ((count_of_end===-1 && count_of_if===-1)){
                    var end_index = i+1;
                    var ahead_tl = tl.slice(begin["val"],end_index);
                    begin["val"] = end_index-1;
                    output_tl["val"] = ahead_tl;
                    return true;
                }
            }
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        if (term(tl[i]["TOKEN_STRING"],"else")){
            var count_of_if = 0;
            var count_of_end = 0;
            var temp_i = i;
            for ( ; i<length_of_tl ; i = i+1){
                if ((((term(tl[i]["TOKEN_STRING"],"if") || term(tl[i]["TOKEN_STRING"],"def")) || term(tl[i]["TOKEN_STRING"],"while")) || term(tl[i]["TOKEN_STRING"],"for"))){
                    count_of_if = count_of_if+1;
                    count_of_end = count_of_end+1;
                }
                if (term(tl[i]["TOKEN_STRING"],"end")){
                    count_of_if = count_of_if-1;
                    count_of_end = count_of_end-1;
                }
                if (((count_of_if===0 && i!==temp_i) && (term(tl[i]["TOKEN_STRING"],"elif") || term(tl[i]["TOKEN_STRING"],"else")))){
                    Walley_Print_Error(TL_toString(temp_tl),"elif or else statements error",tl[i]["TOKEN_START"]);
                }
                if (count_of_end===-1){
                    var end_index = i+1;
                    var ahead_tl = tl.slice(begin["val"],end_index);
                    begin["val"] = end_index-1;
                    output_tl["val"] = ahead_tl;
                    return true;
                }
            }
            INCOMPLETE_STATEMENT = true;
            return false;
        }
        if ((count_of_parenthesis===0 && term(tl[i]["TOKEN_STRING"],"end"))){
            var end_index = i;
            if (begin["val"]<i){
                var ahead_tl = tl.slice(begin["val"],end_index);
                begin["val"] = end_index;
                output_tl["val"] = ahead_tl;
                return true;
                    }
            else{
                begin["val"] = end_index;
            }
            end_index = i+1;
            var ahead_tl = tl.slice(begin["val"],end_index);
            begin["val"] = end_index;
            output_tl["val"] = ahead_tl;
            return true;
        }
    }
    if (begin["val"]<length_of_tl){
        var ahead_tl = tl.slice(begin["val"],length_of_tl);
        begin["val"] = length_of_tl;
        output_tl["val"] = ahead_tl;
        return true;
    }
    return false;
}
parser = function(tl){
    TREE_INDEX = 0;
    var output_tree = TREE_init("walley_statements");
    if (len(tl)===0){
        return output_tree;
    }
    if ((walley_statements(output_tree,tl)===false && INCOMPLETE_STATEMENT===false)){
        console.log("Fail to parse statements\n");
    }
    return output_tree;
}
ism_operator = function(input_str){
    if ((((((term(input_str,"+") || term(input_str,"-")) || term(input_str,"*")) || term(input_str,"/")) || term(input_str,"^")) || term(input_str,"%"))){
        return true;
    }
    return false;
}
Walley_Calculation = function(value1,value2,sign){
    if ((value1[0]!=="\"" && value2[0]!=="\"")){
        if (sign==="^"){
            return eval("Math.pow("+value1+","+value2+")");
        }
        return eval(value1+sign+value2);
    }
    else{
        var value1IsString = false;
        var value2IsString = false;
        if (value1[0]==="\""){
            value1 = value1.slice(1,len(value1)-1);
            value1IsString = true;
        }
        if (value2[0]==="\""){
            value2 = value2.slice(1,len(value2)-1);
            value2IsString = true;
        }
        if (sign[0]==="+"){
            var output_str = "\""+value1+value2+"\"";
            return output_str;
            }
        else if (sign[0]==="*"){
            if ((value1IsString===true && value2IsString===true)){
                console.log("Error.. Can not multiply two string %s and %s\n",value1,value2);
                process.exit(0);
                    }
            else{
                var num = 0;
                var mult_str = "";
                if (value1IsString===true){
                    mult_str = value1;
                    num = parseInt(value2);
                            }
                else{
                    mult_str = value2;
                    num = parseInt(value1);
                }
                var output_str = "\"";
                var i = 0;
                for ( ; i<num ; i = i+1){
                    output_str = output_str+mult_str;
                }
                output_str = output_str+"\"";
                return output_str;
            }
            }
        else{
            console.log("Error.. Sign %s can not be used for string calculation for %s and %s\n",sign,value1,value2);
            process.exit(0);
        }
    }
}
appendSpacesAhead = function(input_str,num){
    for (i = 0 ; i<num ; i = i+1){
        input_str = " "+input_str;
    }
    return input_str;
}
isString = function(input_str){
    if ((input_str[0]!=="\"" || input_str[input_str["length"]-1]!=="\"")){
        return false;
    }
    var count = 0;
    var i = 0;
    var length = input_str["length"];
    for ( ; i<length ; i = i+1){
        if (input_str[i]==="\""){
            count = count+1;
        }
    }
    if (count!==2){
        return false;
    }
    else{
        return true;
    }
}
js_isTableValue = false;
Code_Generation_2_Javascript = function(sl,tree){
    if (term(tree["token_class"],"id")){
        if (term(tree["name"],"continue")){
            return "continue;";
        }
        if (term(tree["name"],"break")){
            return "break;";
        }
        if (term(tree["name"],"none")){
            return "null";
        }
        return tree["name"];
    }
    else if (term(tree["name"],"walley_statements")){
        var nl = tree["node_list"];
        var output_str = "";
        var i = 0;
        var length_of_nl = len(nl);
        for (i = 0 ; i<length_of_nl ; i = i+1){
            var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
            if (len(temp_str)!==0){
                temp_str = appendSpacesAhead(temp_str,BEAUTIFUL_SPACES);
                output_str = output_str+temp_str;
                if (output_str[len(output_str)-1]!=="\n"){
                    if (output_str[len(output_str)-1]!==";"){
                        output_str = output_str+";\n";
                                    }
                    else{
                        output_str = output_str+"\n";
                    }
                }
            }
        }
        return output_str;
    }
    else if (term(tree["name"],"statements")){
        nl = tree["node_list"];
        if (term(nl[0]["name"],"if")){
            var append_str = "if (";
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES+4;
            var judge_str = Code_Generation_2_Javascript(sl,nl[1]);
            append_str = append_str+judge_str;
            append_str = append_str+"){\n";
            var i = 2;
            var length_of_nl = len(nl);
            var output_str = "";
            for (i = 2 ; i<length_of_nl ; i = i+1){
                var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
                if (len(temp_str)!==0){
                    output_str = output_str+temp_str;
                    if (output_str[len(output_str)-1]!=="\n"){
                        if (output_str[len(output_str)-1]!==";"){
                            output_str = output_str+";\n";
                                            }
                        else{
                            output_str = output_str+"\n";
                        }
                    }
                }
            }
            append_str = append_str+output_str;
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES-4;
            return append_str;
            }
        else if (term(nl[0]["name"],"elif")){
            var append_str = "}\n";
            append_str = appendSpacesAhead(append_str,BEAUTIFUL_SPACES-4);
            append_str = append_str+appendSpacesAhead("else if (",BEAUTIFUL_SPACES);
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES+4;
            var judge_str = Code_Generation_2_Javascript(sl,nl[1]);
            append_str = append_str+judge_str;
            append_str = append_str+"){\n";
            var i = 2;
            var length_of_nl = len(nl);
            var output_str = "";
            for (i = 2 ; i<length_of_nl ; i = i+1){
                var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
                if (len(temp_str)!==0){
                    output_str = output_str+temp_str;
                    if (output_str[len(output_str)-1]!=="\n"){
                        if (output_str[len(output_str)-1]!==";"){
                            output_str = output_str+";\n";
                                            }
                        else{
                            output_str = output_str+"\n";
                        }
                    }
                }
            }
            append_str = append_str+output_str;
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES-4;
            return append_str;
            }
        else if (term(nl[0]["name"],"else")){
            var append_str = "}\n";
            append_str = appendSpacesAhead(append_str,BEAUTIFUL_SPACES-4);
            append_str = append_str+appendSpacesAhead("else{\n",BEAUTIFUL_SPACES);
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES+4;
            var i = 1;
            var length_of_nl = len(nl);
            var output_str = "";
            for (i = 1 ; i<length_of_nl ; i = i+1){
                var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
                if (len(temp_str)!==0){
                    output_str = output_str+temp_str;
                    if (output_str[len(output_str)-1]!=="\n"){
                        if (output_str[len(output_str)-1]!==";"){
                            output_str = output_str+";\n";
                                            }
                        else{
                            output_str = output_str+"\n";
                        }
                    }
                }
            }
            append_str = append_str+output_str;
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES-4;
            return append_str;
            }
        else if (term(nl[0]["name"],"while")){
            var append_str = "while (";
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES+4;
            var judge_str = Code_Generation_2_Javascript(sl,nl[1]);
            append_str = append_str+judge_str;
            append_str = append_str+"){\n";
            var i = 2;
            var length_of_nl = len(nl);
            var output_str = "";
            for ( ; i<length_of_nl-1 ; i = i+1){
                var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
                if (len(temp_str)!==0){
                    output_str = output_str+temp_str;
                    if (output_str[len(output_str)-1]!=="\n"){
                        if (output_str[len(output_str)-1]!==";"){
                            output_str = output_str+";\n";
                                            }
                        else{
                            output_str = output_str+"\n";
                        }
                    }
                }
            }
            append_str = append_str+output_str;
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES-4;
            append_str = append_str+appendSpacesAhead("}\n",BEAUTIFUL_SPACES);
            return append_str;
            }
        else if (term(nl[0]["name"],"for")){
            var append_str = "for (";
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES+4;
            var nl_index = 1;
            if (term(nl[1]["name"],"assignment")){
                append_str = append_str+Code_Generation_2_Javascript(sl,nl[1]["node_list"][0]);
                append_str = append_str+" ; ";
                nl_index = 2;
                    }
            else{
                append_str = append_str+" ; ";
                nl_index = 1;
            }
            var judge_str = Code_Generation_2_Javascript(sl,nl[nl_index]);
            append_str = append_str+judge_str;
            append_str = append_str+" ; ";
            nl_index = nl_index+1;
            if (term(nl[nl_index]["name"],"assignment")){
                append_str = append_str+Code_Generation_2_Javascript(sl,nl[nl_index]["node_list"][0]);
                nl_index = nl_index+1;
            }
            append_str = append_str+"){\n";
            var output_str = "";
            var i = nl_index;
            var length_of_nl = len(nl);
            for ( ; i<length_of_nl-1 ; i = i+1){
                var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
                if (len(temp_str)!==0){
                    output_str = output_str+temp_str;
                    if (output_str[len(output_str)-1]!=="\n"){
                        if (output_str[len(output_str)-1]!==";"){
                            output_str = output_str+";\n";
                                            }
                        else{
                            output_str = output_str+"\n";
                        }
                    }
                }
            }
            append_str = append_str+output_str;
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES-4;
            append_str = append_str+appendSpacesAhead("}\n",BEAUTIFUL_SPACES);
            return append_str;
            }
        else if (term(nl[0]["name"],"foreach")){
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES+4;
            var append_str = "for(";
            var foreach_index = nl[1]["name"];
            append_str = append_str+foreach_index;
            append_str = append_str+" in ";
            var has_v = true;
            if (term(nl[2]["name"],"")){
                has_v = false;
            }
            var foreach_in_value = Code_Generation_2_Javascript(sl,nl[3]["node_list"][0]);
            foreach_in_value = "WALLEY.stringToObject("+foreach_in_value+")";
            append_str = append_str+foreach_in_value;
            append_str = append_str+"){\n";
            append_str = append_str+appendSpacesAhead("if(("+foreach_in_value+").hasOwnProperty("+foreach_index+")){\n",BEAUTIFUL_SPACES);
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES+4;
            if (has_v===true){
                var value_var_name = nl[2]["name"];
                append_str = append_str+appendSpacesAhead(value_var_name,BEAUTIFUL_SPACES)+"=";
                var in_value = "("+foreach_in_value+")";
                var in_value_and_key = in_value+"["+foreach_index+"]";
                append_str = append_str+in_value_and_key;
                append_str = append_str+";\n";
            }
            var i = 4;
            var length_of_nl = len(nl);
            var output_str = "";
            for ( ; i<length_of_nl-1 ; i = i+1){
                var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
                if (len(temp_str)!==0){
                    output_str = output_str+temp_str;
                    if (output_str[len(output_str)-1]!=="\n"){
                        if (output_str[len(output_str)-1]!==";"){
                            output_str = output_str+";\n";
                                            }
                        else{
                            output_str = output_str+"\n";
                        }
                    }
                }
            }
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES-4;
            append_str = append_str+output_str;
            append_str = append_str+appendSpacesAhead("}\n",BEAUTIFUL_SPACES);
            BEAUTIFUL_SPACES = BEAUTIFUL_SPACES-4;
            append_str = append_str+appendSpacesAhead("};\n",BEAUTIFUL_SPACES);
            return append_str;
            }
        else if (nl[0]["name"]==="import"){
            var import_file = nl[1]["name"];
            import_file = import_file.slice(1,import_file["length"]-1);
            var fs = require("fs");
            var content_in_import_file = fs.readFileSync(import_file,"utf8");
            var output_str = exports.Code_Generation(content_in_import_file);
            if (exports["INCOMPLETE_STATEMENT"]===true){
                console.log("Error.. statements in file %s is incomplete\n",import_file);
                process.exit(0);
            }
            return output_str;
            }
        else{
            var append_str = "";
            var i = 0;
            var length_of_nl = len(nl);
            var output_str = "";
            for ( ; i<length_of_nl ; i = i+1){
                var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
                if (len(temp_str)!==0){
                    output_str = output_str+temp_str;
                    if (output_str[len(output_str)-1]!=="\n"){
                        if (output_str[len(output_str)-1]!==";"){
                            output_str = output_str+";\n";
                                            }
                        else{
                            output_str = output_str+"\n";
                        }
                    }
                }
            }
            append_str = append_str+output_str;
            return append_str;
        }
        return "";
    }
    else if (term(tree["name"],"relation")){
        var judge_tree = tree["node_list"][0];
        var left_tree = judge_tree["node_list"][0];
        var right_tree = judge_tree["node_list"][1];
        var left_str = Code_Generation_2_Javascript(sl,left_tree);
        var right_str = Code_Generation_2_Javascript(sl,right_tree);
        var append_str = left_str;
        var relationship = null;
        if (term(judge_tree["name"],"and")){
            relationship = " && ";
            }
        else{
            relationship = " || ";
        }
        append_str = append_str+relationship;
        append_str = append_str+right_str;
        append_str = "("+append_str+")";
        return append_str;
    }
    else if (term(tree["name"],"simple_relation")){
        var judge_tree = tree["node_list"][0];
        var left_tree = judge_tree["node_list"][0];
        var right_tree = judge_tree["node_list"][1];
        var left_str = Code_Generation_2_Javascript(sl,left_tree);
        var right_str = Code_Generation_2_Javascript(sl,right_tree);
        var append_str = left_str;
        var judge_sign = judge_tree["name"];
        if (term(judge_sign,"==")){
            judge_sign = "===";
            }
        else if (term(judge_sign,"!=")){
            judge_sign = "!==";
        }
        append_str = append_str+judge_sign;
        append_str = append_str+right_str;
        return append_str;
    }
    else if (term(tree["name"],"self_operator_stm")){
        var var_name = Code_Generation_2_Javascript(sl,tree["node_list"][0]);
        return var_name+tree["node_list"][1]["name"];
    }
    else if (term(tree["name"],"self_assignment_stm")){
        var var_name = Code_Generation_2_Javascript(sl,tree["node_list"][0]);
        var append_string = var_name;
        append_string = append_string+tree["node_list"][1]["name"];
        var var_value = Code_Generation_2_Javascript(sl,tree["node_list"][2]);
        append_string = append_string+var_value;
        return append_string;
    }
    else if (term(tree["name"],"=")){
        var is_local = false;
        var append_string = "";
        var nl = tree["node_list"];
        var var_name_tree = nl[0];
        if (term(var_name_tree["name"],"local")){
            is_local = true;
            var_name_tree = nl[1];
        }
        var var_value_tree = null;
        if (is_local===true){
            var_value_tree = nl[2];
            }
        else{
            var_value_tree = nl[1];
        }
        var var_name = Code_Generation_2_Javascript(sl,var_name_tree);
        append_string = var_name;
        if (is_local===true){
            append_string = "var "+append_string;
        }
        append_string = append_string+" = ";
        var var_value = Code_Generation_2_Javascript(sl,var_value_tree);
        append_string = append_string+var_value;
        return append_string;
    }
    else if (term(tree["name"],"func_value")){
        var append_string = "function(";
        var param_str = Code_Generation_2_Javascript(sl,tree["node_list"][1]);
        append_string = append_string+param_str;
        append_string = append_string+"){\n";
        BEAUTIFUL_SPACES = BEAUTIFUL_SPACES+4;
        var nl = tree["node_list"];
        var i = 2;
        var output_str = "";
        var length_of_nl = len(nl);
        for ( ; i<length_of_nl-1 ; i = i+1){
            var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
            if (len(temp_str)!==0){
                output_str = output_str+temp_str;
                if (output_str[len(output_str)-1]!=="\n"){
                    if (output_str[len(output_str)-1]!==";"){
                        output_str = output_str+";\n";
                                    }
                    else{
                        output_str = output_str+"\n";
                    }
                }
            }
        }
        append_string = append_string+output_str;
        BEAUTIFUL_SPACES = BEAUTIFUL_SPACES-4;
        append_string = append_string+appendSpacesAhead("}\n",BEAUTIFUL_SPACES);
        return append_string;
    }
    else if (term(tree["token_class"],"table")){
        var append_str = "{";
        var nl = tree["node_list"];
        var i = 0;
        var length_of_nl = len(nl);
        for (i = 0 ; i<length_of_nl ; i = i+1){
            var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
            append_str = append_str+temp_str;
            if (i+1!==length_of_nl){
                append_str = append_str+",";
            }
        }
        append_str = append_str+"}";
        return append_str;
    }
    else if (term(tree["name"],"table_expr")){
        var key_tree = tree["node_list"][0];
        var value_tree = tree["node_list"][1];
        var left = Code_Generation_2_Javascript(sl,key_tree["node_list"][0]);
        var left_is_string = isString(left);
        if ((left_is_string===false && isdigit(left)===false)){
            console.log("Error.. invalid key %s\n",left);
            process.exit(0);
        }
        if (left_is_string===true){
            left = left.slice(1,left["length"]-1);
        }
        var right = Code_Generation_2_Javascript(sl,value_tree);
        return left+":"+right;
    }
    else if (term(tree["name"],"table_value")){
        var nl = tree["node_list"];
        var var_name = Code_Generation_2_Javascript(sl,nl[0]);
        var var_name_is_table = false;
        if (nl[0]["token_class"]==="table"){
            var_name_is_table = true;
        }
        var append_str = var_name;
        js_isTableValue = true;
        var i = 1;
        var length_of_nl = len(nl);
        for ( ; i<length_of_nl ; i = i+1){
            var key_tree = nl[i];
            var key_str = Code_Generation_2_Javascript(sl,key_tree);
            if ((var_name_is_table===true && key_str.indexOf(".slice(")===0)){
                append_str = "WALLEY.slice("+append_str+","+key_str.slice(7,key_str["length"]-1)+")";
                continue;
            }
            append_str = append_str+key_str;
        }
        js_isTableValue = false;
        return append_str;
    }
    else if (term(tree["name"],"key")){
        if (term(tree["node_list"][0]["name"],"slice")){
            var append_str = ".slice(";
            var nl = tree["node_list"][0]["node_list"];
            var left = nl[0];
            var right = nl[1];
            var left_str = Code_Generation_2_Javascript(sl,left);
            append_str = append_str+left_str;
            js_isTableValue = false;
            if (term(right["name"],"its_length")){
                console.log("");
                    }
            else{
                append_str = append_str+",";
                var right_str = Code_Generation_2_Javascript(sl,right);
                append_str = append_str+right_str;
            }
            append_str = append_str+")";
            js_isTableValue = true;
            return append_str;
            }
        else{
            var key_tree = tree["node_list"][0];
            js_isTableValue = false;
            var append_str = "["+Code_Generation_2_Javascript(sl,key_tree)+"]";
            js_isTableValue = true;
            return append_str;
        }
    }
    else if (term(tree["name"],"func")){
        var used_to_be_js_isTableValue = false;
        var append_str = "";
        if (js_isTableValue===false){
            var func_name_string = Code_Generation_2_Javascript(sl,tree["node_list"][0]["node_list"][0]);
            var func_name = func_name_string.slice(1,len(func_name_string)-1);
            append_str = func_name;
            }
        else{
            var func_name = Code_Generation_2_Javascript(sl,tree["node_list"][0]["node_list"][0]);
            if (isString(func_name)===true){
                append_str = "."+func_name.slice(1,func_name["length"]-1);
                    }
            else{
                append_str = "["+func_name+"]";
            }
            used_to_be_js_isTableValue = true;
            js_isTableValue = false;
        }
        append_str = append_str+"(";
        var params_tree = tree["node_list"][1];
        var params_nl = params_tree["node_list"];
        var i = 0;
        var length_of_params_nl = len(params_nl);
        for (i = 0 ; i<length_of_params_nl ; i = i+1){
            append_str = append_str+Code_Generation_2_Javascript(sl,params_nl[i]);
            if (i+1!==length_of_params_nl){
                append_str = append_str+",";
            }
        }
        append_str = append_str+")";
        if (used_to_be_js_isTableValue===true){
            js_isTableValue = true;
        }
        return append_str;
    }
    else if ((term(tree["name"],"and") || term(tree["name"],"or"))){
        var left_str = Code_Generation_2_Javascript(sl,tree["node_list"][0]);
        var right_str = Code_Generation_2_Javascript(sl,tree["node_list"][1]);
        var judge_sign = "&&";
        if (term(tree["name"],"or")){
            judge_sign = "||";
        }
        return left_str+judge_sign+right_str;
    }
    else if (term(tree["name"],"params")){
        var append_string = "";
        var nl = tree["node_list"];
        var i = 0;
        var length_of_nl = len(nl);
        for ( ; i<length_of_nl ; i = i+1){
            if (term(nl[i]["name"],"=")){
                console.log("Does not support = in params now \n");
            }
            var need_to_be_appended = Code_Generation_2_Javascript(sl,nl[i]);
            if (term(need_to_be_appended,"null")){
                continue;
            }
            append_string = append_string+need_to_be_appended;
            if (i+1!==length_of_nl){
                append_string = append_string+",";
            }
        }
        return append_string;
    }
    else if (term(tree["name"],"end")){
        return "}\n";
    }
    else if (term(tree["token_class"],"num")){
        return tree["name"];
    }
    else if (term(tree["token_class"],"string")){
        return tree["name"];
    }
    else if (term(tree["name"],"value")){
        var nl = tree["node_list"];
        return Code_Generation_2_Javascript(sl,nl[0]);
    }
    else if (ism_operator(tree["name"])){
        var nl = tree["node_list"];
        var left = nl[0];
        var right = nl[1];
        var left_str = Code_Generation_2_Javascript(sl,left);
        var right_str = Code_Generation_2_Javascript(sl,right);
        if (((isdigit(left_str) || isString(left_str)) && (isdigit(right_str) || isString(right_str)))){
            var value = Walley_Calculation(left_str,right_str,tree["name"]);
            return value;
        }
        var left_need_bracket = true;
        var right_need_bracket = true;
        if (((term(left["token_class"],"id") || term(left["token_class"],"string")) || term(left["token_class"],"num"))){
            left_need_bracket = false;
        }
        if (((term(right["token_class"],"id") || term(right["token_class"],"string")) || term(right["token_class"],"num"))){
            right_need_bracket = false;
        }
        var need_bracket = false;
        if ((((term(tree["name"],"*") || term(tree["name"],"//")) || term(tree["name"],"^")) || term(tree["name"],"%"))){
            need_bracket = true;
        }
        if (need_bracket){
            if (left_need_bracket){
                left_str = "("+left_str+")";
            }
            if (right_need_bracket){
                right_str = "("+right_str+")";
            }
            if (term(tree["name"],"^")){
                var append_str = "Math.pow("+left_str+","+right_str+")";
                return append_str;
                    }
            else{
                var append_str = left_str+tree["name"]+right_str;
                return append_str;
            }
            }
        else{
            if (term(tree["name"],"^")){
                return "Math.pow("+left_str+","+right_str+")";
                    }
            else{
                var append_str = left_str;
                append_str = append_str+tree["name"];
                append_str = append_str+right_str;
                return append_str;
            }
        }
    }
    else if (term(tree["name"],"expr")){
        return Code_Generation_2_Javascript(sl,tree["node_list"][0]);
    }
    else if (term(tree["name"],"return")){
        var append_str = "return ";
        var nl = tree["node_list"];
        append_str = append_str+Code_Generation_2_Javascript(sl,nl[0]);
        append_str = append_str+";\n";
        return append_str;
    }
    else if (tree["name"]==="new_value"){
        js_isTableValue = true;
        var append_str = "new ";
        var nl = tree["node_list"];
        for (i = 0 ; i<len(nl) ; i = i+1){
            var temp_str = Code_Generation_2_Javascript(sl,nl[i]);
            if (i===0){
                temp_str = temp_str.slice(1,temp_str["length"]);
            }
            append_str+=temp_str;
        }
        js_isTableValue = false;
        return append_str;
    }
    else{
        console.log("Code Generation Error..\n");
        process.exit(0);
    }
}
exports["Code_Generation"] = function(input_str){
    INCOMPLETE_STATEMENT = false;
    var tl = Walley_Lexical_Analyzie(input_str);
    var tree = parser(tl);
    var sl = {};
    var output = Code_Generation_2_Javascript(sl,tree);
    if (output!==""){
        sl.append(output);
    }
    var output_str = "";
    var length = len(sl);
    for (i = 0 ; i<length ; i = i+1){
        output_str = output_str+sl[i];
    }
    exports["INCOMPLETE_STATEMENT"] = INCOMPLETE_STATEMENT;
    return output_str;
}
