none=null;String.prototype.find=function(e,t){if(typeof t=="undefined"){t=0}return this.indexOf(e,t)};String.prototype.tolower=function(){return this.toLowerCase()};String.prototype.toupper=function(){return this.toUpperCase()};String.prototype.reverse=function(){return this.split().reverse().join()};Math["cot"]=function(e){return 1/Math.tan(e)};Math["sec"]=function(e){return 1/Math.cos(e)};Math["csc"]=function(e){return 1/Math.sin(e)};Object.prototype.slice=function(e,t){var n={};var r=0;for(var i=e;i<t;i++){n[r]=this[i];r++}return n};Object.prototype.append=function(e){var t="-1";for(var n in this){if(!isNaN(n)){if(n>t){t=n}}}if(t!="-1"){t=parseInt(t)+1}else{t="0"}this[t]=e}
if (4<x || x<5){
x=12;
}
else if (x<5){
x=15;
}
;
