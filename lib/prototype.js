none=null;
//new written function for javascript
function isalpha(input_char){
   return /^[ a-z]+$/i.test(input_char);
}
//javascript : isdigit
function isdigit(e) {
    return !isNaN(parseFloat(e)) && isFinite(e);
}
// String
// find
String.prototype.find=function(find_str, start){
    if(typeof(start)=='undefined'){start=0};
    return this.indexOf(find_str,start);
}
// tolower
String.prototype.tolower=function(){
    return this.toLowerCase();
}
// toupper
String.prototype.toupper=function(){
    return this.toUpperCase();
}
// reverse
String.prototype.reverse=function(){
    return this.split("").reverse().join("");
}

// Math

Math["cot"]=function(num){
    return 1/Math.tan(num);
}
Math["sec"]=function(num){
    return 1/Math.cos(num);
}
Math["csc"]=function(num){
    return 1/Math.sin(num);
}

// Array
/*
Array.prototype.append=function(obj){
    this.push(obj);
}

Array.prototype.insert=function(insert_value,at_index){
    if(typeof(at_index)=="undefined"){return this.push(insert_value);};
    this.splice(insert_value,0,at_index);
}

Array.prototype.remove=function(remove_at_index){
    this.splice(remove_at_index,1);
}*/

// Object
Object.prototype.slice=function(start,end){
    var return_obj={};
    var a=0;
    for (var i=start;i<end;i++){
        return_obj[a]=this[i];
        a++;
    }
    return return_obj;
}

// index is the largest int +1
Object.prototype.append=function(append_obj){
    var largest="-1";
    for (var i in this){
        // is number
        if(!isNaN(i)){
            if(i>largest){
                largest=i;
            }
        }
    }
    if (largest!="-1") {largest=parseInt(largest)+1;}
    else{largest="0";}
    this[largest]=append_obj;

}

