none=null;function isalpha(input_char){return/^[a-z]+$/i.test(input_char)}function isdigit(e){return!isNaN(parseFloat(e))&&isFinite(e)}String.prototype.find=function(find_str,start){if(typeof start=="undefined"){start=0}return this.indexOf(find_str,start)};String.prototype.tolower=function(){return this.toLowerCase()};String.prototype.toupper=function(){return this.toUpperCase()};String.prototype.reverse=function(){return this.split("").reverse().join("")};String.prototype.trim=function(){return this.replace(/^s+|s+$/g,"")};Math["cot"]=function(num){return 1/Math.tan(num)};Math["sec"]=function(num){return 1/Math.cos(num)};Math["csc"]=function(num){return 1/Math.sin(num)};Object.prototype.slice=function(start,end){var return_obj={};var a=0;for(var i=start;i<end;i++){return_obj[a]=this[i];a++}return return_obj};Object.prototype.append=function(e){var t=this.maxn()+1;this[t]=e};Object.prototype.maxn=function(){var t=0;if(this[0]==undefined){return-1}while(this[t]!=undefined){t=t+1}return t-1};Object.prototype.insert=function(insert_obj,pos){if(pos==undefined){pos=table.maxn(this)+1;this[pos]=insert_obj}else{this[pos]=insert_obj}};Object.prototype.remove=function(pos){if(pos==undefined){pos=table.maxn(obj)}delete this[pos]};Object.prototype.length=function(){return Object.keys(this).length};function len(obj){if(typeof obj=="string"){return obj.length}else if(typeof obj=="object"){return Object.keys(obj).length}else{console.log("Error..\nfunctin len() only support table or string\n")}}
if (x===-2){
x=12
}
else if (x===5 ){
x=16
}
else{
x=5 
}
