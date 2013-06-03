function isalpha(e){return/^[a-z]+$/i.test(e)}function isdigit(e){return!isNaN(parseFloat(e))&&isFinite(e)}function len(e){if(typeof e=="string"){return e.length}else if(typeof e=="object"){return Object.keys(e).length}else{console.log("Error..\nfunctin len() only support table or string\n")}}none=null;String.prototype.find=function(e,t){if(typeof t=="undefined"){t=0}return this.indexOf(e,t)};String.prototype.tolower=function(){return this.toLowerCase()};String.prototype.toupper=function(){return this.toUpperCase()};String.prototype.reverse=function(){return this.split("").reverse().join("")};Math["cot"]=function(e){return 1/Math.tan(e)};Math["sec"]=function(e){return 1/Math.cos(e)};Math["csc"]=function(e){return 1/Math.sin(e)};Object.prototype.slice=function(e,t){var n={};var r=0;for(var i=e;i<t;i++){n[r]=this[i];r++}return n};Object.prototype.append=function(e){var t=-1;for(var n in this){if(isdigit(n)){n=parseInt(n);if(n>t){t=n}}}if(t!==-1){t=t+1}else{t=0}this[t]=e};Object.prototype.length=function(){return Object.keys(this).length}
Code_Generation_2_Javascript=function(sl,tree){
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
var nl=tree["node_list"];
var output_str="";
var i=0;
var length_of_nl=len(nl);
for (i=0;i<length_of_nl;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
if (len(temp_str)!==0){
output_str=output_str+temp_str;
if (output_str[["len"](output_str)-1]!=="\n"){
if (output_str[["len"](output_str)-1]!==";"){
output_str=output_str+";\n";
}
else{
output_str=output_str+"\n";
}
}
}

}
return output_str;
     }
else if (term(tree["name"],"statements")){
nl=tree["node_list"];
if (term(nl[0]["name"],"if")){
var append_str="if (";
var judge_str=Code_Generation_2_Javascript(sl,nl[1]);
append_str=append_str+judge_str;
append_str=append_str+"){\n";
var i=2;
var length_of_nl=len(nl);
var output_str="";
for (i=2;i<length_of_nl;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
if (len(temp_str)!==0){
output_str=output_str+temp_str;
if (output_str[["len"](output_str)-1]!=="\n"){
if (output_str[["len"](output_str)-1]!==";"){
output_str=output_str+";\n";
}
else{
output_str=output_str+"\n";
}
}
}

}
append_str=append_str+output_str;
return append_str;
}
else if (term(nl[0]["name"],"elif")){
var append_str="}\nelse if (";
var judge_str=Code_Generation_2_Javascript(sl,nl[1]);
append_str=append_str+judge_str;
append_str=append_str+"){\n";
var i=2;
var length_of_nl=len(nl);
var output_str="";
for (i=2;i<length_of_nl;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
if (len(temp_str)!==0){
output_str=output_str+temp_str;
if (output_str[["len"](output_str)-1]!=="\n"){
if (output_str[["len"](output_str)-1]!==";"){
output_str=output_str+";\n";
}
else{
output_str=output_str+"\n";
}
}
}

}
append_str=append_str+output_str;
return append_str;
}
else if (term(nl[0]["name"],"else")){
var append_str="}\nelse{\n";
var i=1;
var length_of_nl=len(nl);
var output_str="";
for (i=1;i<length_of_nl;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
if (len(temp_str)!==0){
output_str=output_str+temp_str;
if (output_str[["len"](output_str)-1]!=="\n"){
if (output_str[["len"](output_str)-1]!==";"){
output_str=output_str+";\n";
}
else{
output_str=output_str+"\n";
}
}
}

}
append_str=append_str+output_str;
return append_str;
}
else if (term(nl[0]["name"],"while")){
var append_str="while (";
var judge_str=Code_Generation_2_Javascript(sl,nl[1]);
append_str=append_str+judge_str;
append_str=append_str+"){\n";
var i=2;
var length_of_nl=len(nl);
var output_str="";
for (;i<length_of_nl;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
if (len(temp_str)!==0){
output_str=output_str+temp_str;
if (output_str[["len"](output_str)-1]!=="\n"){
if (output_str[["len"](output_str)-1]!==";"){
output_str=output_str+";\n";
}
else{
output_str=output_str+"\n";
}
}
}

}
append_str=append_str+output_str;
return append_str;
}
else if (term(nl[0]["name"],"for")){
var append_str="for (";
var nl_index=1;
if (term(nl[1]["name"],"assignment")){
append_str=append_str+Code_Generation_2_Javascript(sl,nl[1]["node_list"][0]);
append_str=append_str+";";
nl_index=2;
}
else{
append_str=append_str+";";
nl_index=1;
}
var judge_str=Code_Generation_2_Javascript(sl,nl[nl_index]);
append_str=append_str+judge_str;
append_str=append_str+";";
nl_index=nl_index+1;
if (term(nl[nl_index]["name"],"assignment")){
append_str=append_str+Code_Generation_2_Javascript(sl,nl[nl_index]["node_list"][0]);
nl_index=nl_index+1;
}
append_str=append_str+"){\n";
var output_str="";
var i=nl_index;
var length_of_nl=len(nl);
for (;i<length_of_nl-1;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
if (len(temp_str)!==0){
output_str=output_str+temp_str;
if (output_str[["len"](output_str)-1]!=="\n"){
if (output_str[["len"](output_str)-1]!==";"){
output_str=output_str+";\n";
}
else{
output_str=output_str+"\n";
}
}
}

}
append_str=append_str+output_str;
append_str=append_str+"\n}";
return append_str;
}
else if (term(nl[0]["name"],"foreach")){
var append_str="for(";
var foreach_index=nl[1]["name"];
append_str=append_str+foreach_index;
append_str=append_str+" in ";
var has_v=true;
if (term(nl[2]["name"],"")){
has_v=false;
}
var foreach_in_value=Code_Generation_2_Javascript(sl,nl[3]["node_list"][0]);
append_str=append_str+foreach_in_value;
append_str=append_str+"){\n";
if (has_v===true){
var value_var_name=nl[2]["name"];
append_str=append_str+value_var_name+"=";
var in_value="("+foreach_in_value+")";
var in_value_and_key=in_value+"["+foreach_index+"]";
append_str=append_str+in_value_and_key;
append_str=append_str+";\n";
}
var i=4;
var length_of_nl=len(nl);
var output_str="";
for (;i<length_of_nl;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
if (len(temp_str)!==0){
output_str=output_str+temp_str;
if (output_str[["len"](output_str)-1]!=="\n"){
if (output_str[["len"](output_str)-1]!==";"){
output_str=output_str+";\n";
}
else{
output_str=output_str+"\n";
}
}
}

}
append_str=append_str+output_str;
return append_str;
}
else{
var i=0;
var length_of_nl=len(nl);
var output_str="";
for (;i<length_of_nl;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
if (len(temp_str)!==0){
output_str=output_str+temp_str;
if (output_str[["len"](output_str)-1]!=="\n"){
if (output_str[["len"](output_str)-1]!==";"){
output_str=output_str+";\n";
}
else{
output_str=output_str+"\n";
}
}
}

}
append_str=append_str+output_str;
return append_str;
}
return "";
     }
else if (term(tree["name"],"relation")){
var judge_tree=tree["node_list"][0];
var left_tree=judge_tree["node_list"][0];
var right_tree=judge_tree["node_list"][1];
var left_str=Code_Generation_2_Javascript(sl,left_tree);
var right_str=Code_Generation_2_Javascript(sl,right_tree);
var append_str=left_str;
var relationship=null;
if (term(judge_tree["name"],"and")){
relationship=" && ";
}
else{
relationship=" || ";
}
append_str=append_str+relationship;
append_str=append_str+right_str;
append_str="("+append(append_str,")");
return append_str;
     }
else if (term(tree["name"],"simple_relation")){
var judge_tree=tree["node_list"][0];
var left_tree=judge_tree["node_list"][0];
var right_tree=judge_tree["node_list"][1];
var left_str=Code_Generation_2_Javascript(sl,left_tree);
var right_str=Code_Generation_2_Javascript(sl,right_tree);
var append_str=left_str;
var judge_sign=judge_tree["name"];
if (term(judge_sign,"==")){
judge_sign="===";
}
else if (term(judge_sign,"!=")){
judge_sign="!==";
}
append_str=append_str+judge_sign;
append_str=append_str+right_str;
return append_str;
     }
else if (term(tree["name"],"=")){
var is_local=false;
var append_string="";
var nl=tree["node_list"];
var var_name_tree=nl[0];
if (term(var_name_tree["name"],"local")){
is_local=true;
var_name_tree=nl[1];
}
var var_value_tree=null;
if (is_local===true){
var_value_tree=nl[2];
}
else{
var_value_tree=nl[1];
}
var var_name=Code_Generation_2_Javascript(sl,var_name_tree);
append_string=var_name;
if (is_local===true){
append_string="var "+append_string;
}
append_string=append_string+"=";
var var_value=Code_Generation_2_Javascript(sl,var_value_tree);
append_string=append_string+var_value;
return append_string;
     }
else if (term(tree["name"],"func_value")){
var append_string="function(";
var param_str=Code_Generation_2_Javascript(sl,tree["node_list"][1]);
append_string=append_string+param_str;
append_string=append_string+"){\n";
var nl=tree["node_list"];
var i=2;
var output_str="";
var length_of_nl=len(nl);
for (;i<length_of_nl-1;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
if (len(temp_str)!==0){
output_str=output_str+temp_str;
if (output_str[["len"](output_str)-1]!=="\n"){
if (output_str[["len"](output_str)-1]!==";"){
output_str=output_str+";\n";
}
else{
output_str=output_str+"\n";
}
}
}

}
append_string=append_string+output_str;
append_string=append_string+" }";
return append_string;
     }
else if (term(tree["token_class"],"table")){
var append_str="{";
var nl=tree["node_list"];
var i=0;
var length_of_nl=len(nl);
for (i=0;i<length_of_nl;i=i+1){
var temp_str=Code_Generation_2_Javascript(sl,nl[i]);
append_str=append_str+temp_str;
if (i+1!==length_of_nl){
append_str=append_str+",";
}

}
append_str=append_str+"}";
return append_str;
     }
else if (term(tree["name"],"table_expr")){
var key_tree=tree["node_list"][0];
var value_tree=tree["node_list"][1];
var left=Code_Generation_2_Javascript(sl,key_tree["node_list"][0]);
bool
left_is_string=isString(left);
if ((left_is_string===false && stringIsDigit(left)===false)){
console["log"]("Error.. invalid key %s\n",left);
exit(0)
}
if (left_is_string===true){
left=substr(left,1,left["length"]-1);
}
var right=Code_Generation_2_Javascript(sl,value_tree);
return append(left,append(":",right));
     }
else if (term(tree["name"],"table_value")){
var nl=tree["node_list"];
var var_name=Code_Generation_2_Javascript(sl,nl[0]);
var append_str=var_name;
js_isTableValue=true;
var i=1;
var length_of_nl=len(nl);
for (;i<length_of_nl;i=i+1){
var key_tree=nl[i];
var key_str=Code_Generation_2_Javascript(sl,key_tree);
append_str=append_str+key_str;

}
js_isTableValue=false;
return append_str;
     }
else if (term(tree["name"],"key")){
if (term(tree["node_list"][0]["name"],"slice")){
var append_str=".slice(";
var nl=tree["node_list"][0]["node_list"];
TREE
left=nl[0];
TREE
right=nl[1];
var left_str=Code_Generation_2_Javascript(sl,left);
append_str=append(append_str,left_str);
js_isTableValue=false;
if (term(right["name"],"its_length")){
console["log"]("");
}
else{
append_str=append_str+",";
var right_str=Code_Generation_2_Javascript(sl,right);
append_str=append_str+right_str;
}
append_str=append_str+")";
js_isTableValue=true;
return append_str;
}
else{
var key_tree=tree["node_list"][0];
js_isTableValue=true;
return "["+Code_Generation_2_Javascript(sl,key_tree);
"0]"
}
     }
else if (term(tree["name"],"func")){
var used_to_be_js_isTableValue=false;
var append_str="";
if (js_isTableValue===false){
var func_name_string=Code_Generation_2_Javascript(sl,tree["node_list"][0]["node_list"][0]);
var func_name=func_name_string.slice(1,len(func_name_string)-1);
append_str=func_name;
}
else{
var func_name=Code_Generation_2_Javascript(sl,tree["node_list"][0]["node_list"][0]);
append_str="["+func_name+"]";
used_to_be_js_isTableValue=true;
js_isTableValue=false;
}
append_str=append_str+"(";
var params_tree=tree["node_list"][1];
var params_nl=params_tree["node_list"];
var i=0;
var length_of_params_nl=len(params_nl);
for (i=0;i<length_of_params_nl;i=i+1){
append_str=append_str+Code_Generation_2_Javascript(sl,params_nl[i]);
if (i+1!==length_of_params_nl){
append_str=append_str+",";
}

}
append_str=append_str+")";
if (used_to_be_js_isTableValue===true){
js_isTableValue=true;
}
return append_str;
     }
else if ((term(tree["name"],"and") || term(tree["name"],"or"))){
var left_str=Code_Generation_2_Javascript(sl,tree["node_list"][0]);
var right_str=Code_Generation_2_Javascript(sl,tree["node_list"][1]);
var judge_sign="&&";
if (term(tree["name"],"or")){
judge_sign="||";
}
return append(left_str,judge_sign+right_str);
     }
else if (term(tree["name"],"params")){
var append_string="";
var nl=tree["node_list"];
var i=0;
var length_of_nl=len(nl);
for (;i<length_of_nl;i=i+1){
if (term(nl[i]["name"],"=")){
console["log"]("Does not support = in params now \n");
}
var need_to_be_appended=Code_Generation_2_Javascript(sl,nl[i]);
if (term(need_to_be_appended,"null")){
continue;
}
append_string=append_string+need_to_be_appended;
if (i+1!==length_of_nl){
append_string=append_string+",";
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
var nl=tree["node_list"];
return Code_Generation_2_Javascript(sl,nl[0]);
     }
else if (ism_operator(tree["name"])){
var nl=tree["node_list"];
var left=nl[0];
var right=nl[1];
var left_str=Code_Generation_2_Javascript(sl,left);
var right_str=Code_Generation_2_Javascript(sl,right);
if (((stringIsDigit(left_str) || isString(left_str)) && (stringIsDigit(right_str) || isString(right_str)))){
var value=Walley_Calculation(left_str,right_str,tree["name"]);
return value;
}
var left_need_bracket=true;
var right_need_bracket=true;
if (((term(left["token_class"],"id") || term(left["token_class"],"string")) || term(left["token_class"],"num"))){
left_need_bracket=false;
}
if (((term(right["token_class"],"id") || term(right["token_class"],"string")) || term(right["token_class"],"num"))){
right_need_bracket=false;
}
var need_bracket=false;
if ((((term(tree["name"],"*") || term(tree["name"],"//")) || term(tree["name"],"^")) || term(tree["name"],"%"))){
need_bracket=true;
}
if (need_bracket){
if (left_need_bracket){
left_str="("+left_str+")";
}
if (right_need_bracket){
right_str="("+right_str+")";
}
if (term(tree["name"],"^")){
var append_str="Math.pow("+left_str+","+right_str+")";
return append_str;
}
else{
var append_str=left_str+tree["name"]+right_str;
return append_str;
}
}
else{
if (term(tree["name"],"^")){
return "Math.pow("+left_str+","+right_str+")";
}
else{
var append_str=left_str;
append_str=append_str+tree["name"];
append_str=append_str+right_str;
return append_str;
}
}
     }
else if (term(tree["name"],"expr")){
return Code_Generation_2_Javascript(sl,tree["node_list"][0]);
     }
else if (term(tree["name"],"return")){
var append_str="return ";
var nl=tree["node_list"];
append_str=append_str+Code_Generation_2_Javascript(sl,nl[0]);
append_str=append_str+";\n";
return append_str;
     }
else{
console["log"]("Code Generation Error..\n");
exit(0)
     }
 };
