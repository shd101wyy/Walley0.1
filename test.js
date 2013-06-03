exports["Code_Generation"=function(input_str){
INCOMPLETE_STATEMENT=false;
var tl=Walley_Lexical_Analyzie(input_str);
var tree=parser(tl);
var sl={};
var output=Code_Generation_2_Javascript(sl,tree);
if (output!==""){
sl["append"](output);
}
var output_str="";
var length=len(sl);
for (i=0;i<length;i=i+1){
output_str=output_str+sl[i;

};
exports["INCOMPLETE_STATEMENT"=INCOMPLETE_STATEMENT;
return output_str;
 };
