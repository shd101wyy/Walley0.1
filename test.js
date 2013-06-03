function isalpha(e){return/^[a-z]+$/i.test(e)}function isdigit(e){return!isNaN(parseFloat(e))&&isFinite(e)}function len(e){if(typeof e=="string"){return e.length}else if(typeof e=="object"){return Object.keys(e).length}else{console.log("Error..\nfunctin len() only support table or string\n")}}none=null;String.prototype.find=function(e,t){if(typeof t=="undefined"){t=0}return this.indexOf(e,t)};String.prototype.tolower=function(){return this.toLowerCase()};String.prototype.toupper=function(){return this.toUpperCase()};String.prototype.reverse=function(){return this.split("").reverse().join("")};String.prototype.trim=function(){return this.replace(/^\s+|\s+$/g,"")};Math["cot"]=function(e){return 1/Math.tan(e)};Math["sec"]=function(e){return 1/Math.cos(e)};Math["csc"]=function(e){return 1/Math.sin(e)};Object.prototype.slice=function(e,t){var n={};var r=0;for(var i=e;i<t;i++){n[r]=this[i];r++}return n};Object.prototype.append=function(e){var t=-1;for(var n in this){if(isdigit(n)){n=parseInt(n);if(n>t){t=n}}}if(t!==-1){t=t+1}else{t=0}this[t]=e};Object.prototype.length=function(){return Object.keys(this).length}
Walley_Calculation=function(value1,value2,sign){
     if ((value1[0]!=="\"" && value2[0]!=="\"")){
return eval(value1+sign+value2);
     }
else{
var value1IsString=false;
var value2IsString=false;
if (value1[0]==="\""){
value1=value1.slice(1,len(value1)-1);
value1IsString=true;
}
if (value2[0]==="\""){
value2=value2.slice(1,len(value2)-1);
value2IsString=true;
}
if (sign[0]==="+"){
var output_str="\""+value1+value2+"\"";
return output_str;
}
else if (sign[0]==="*"){
if ((value1IsString===true && value2IsString===true)){
console["log"]("Error.. Can not multiply two string %s and %s\n",value1,value2);
exit(0)
}
else{
var num=0;
var mult_str="";
if (value1IsString===true){
mult_str=value1;
num=parseInt(value2);
}
else{
mult_str=value2;
num=parseInt(value1);
}
var output_str="\"";
var i=0;
for (;i<num;i=i+1){
output_str=output_str+mult_str;

}
output_str=output_str+"\"";
return output_str;
}
}
else{
console["log"]("Error.. Sign %s can not be used for string calculation for %s and %s\n",sign,value1,value2);
exit(0)
}
     }
 };
