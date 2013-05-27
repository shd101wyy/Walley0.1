String.prototype.find=function(e,t){if(typeof t=="undefined"){t=0}return this.indexOf(e,t)};String.prototype.tolower=function(){return this.toLowerCase()};String.prototype.toupper=function(){return this.toUpperCase()};String.prototype.reverse=function(){return this.split().reverse().join()};Math["cot"]=function(e){return 1/Math.tan(e)};Math["sec"]=function(e){return 1/Math.cos(e)};Math["csc"]=function(e){return 1/Math.sin(e)};Array.prototype.append=function(e){this.push(e)};Array.prototype.insert=function(e,t){if(typeof t=="undefined"){return this.push(e)}this.splice(e,0,t)};Array.prototype.remove=function(e){this.splice(e,1)}
Token={};
Token["init"]=function(){
     self={};
     self["TOKEN_CLASS"]="";
     self["TOKEN_STRING"]="";
     self["TOKEN_START"]=-1;
     self["TOKEN_END"]=-1;
     return self;
 };
TOKEN_print=function(token){
     console["log"](token+token["TOKEN_CLASS"]+":"+"|"+token["TOKEN_STRING"]+"|"+token["TOKEN_START"]+"|")
 };
