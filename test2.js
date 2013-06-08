none=null;
//new written function for javascript
function isalpha(input_char){
   //return /^[ a-z]+$/i.test(input_char); including space
   return /^[a-z]+$/i.test(input_char);
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

// OBJECT FUNCTIONS
Object.prototype.slice=function(start,end) {
        var return_obj={};
        var a=0;
        for (var i=start;i<end;i++){
            return_obj[a]=this[i];
            a++;
        }
        return return_obj;
    };

Object.prototype.append= function(e) {
        var t=this.maxn()+1
        this[t] = e;
    };

// get largest index
// eg [1,2,3] largest index is 2 
// only return continuous integer index
// eg [0:1,1:2,15:2] because 15 is not after 1
//                   so only return 1
// if no integer index then return -1
Object.prototype.maxn=function(){
        var t=0
        if (this[0]==undefined){
            return -1
        }
        while(this[t]!=undefined){
            t=t+1
        }
        return t-1
    };


// insert insert_obj at pos
Object.prototype.insert=function(insert_obj, pos){
        // default position is the largest integer index
        if (pos==undefined){
            pos=table.maxn(this)+1
            this[pos] = insert_obj
        }
        else{
            this[pos]=insert_obj
        }
    };

// remove element at position
Object.prototype.remove=function(pos){
        if (pos==undefined){
            pos=table.maxn(obj)
        }
        delete(this[pos])
    };

// get the length of table
// [0:1,hi:2] -> length 2
Object.prototype.length=function(){
        return Object.keys(this).length
    }


// len like python
function len(obj){
    if(typeof(obj)=='string'){
        return obj.length
    }
    else if(typeof(obj)=='object'){
        return Object.keys(obj).length
    }
    else{
        console.log("Error..\nfunctin len() only support table or string\n");
    }
}
// WALLEY function
WALLEY={}
WALLEY.convertObjectToArray=function(obj){
    if(typeof(obj)=="string"){
        return obj
    }
    // table
    else{
        var arr=[]
        for(var i in obj){
            if (obj.hasOwnProperty(i)){
            	console.log("i---> "+i)
                if (isdigit(i)){
                    arr[i] = obj[i];
                }else{
                  arr.push(obj[i]);
                }
            }
        }

        return arr
    }
}



x={0:1,1:2,2:3};
x=WALLEY.convertObjectToArray(x).slice(0,3);
console.log(x)
for(i in x){
	if((x).hasOwnProperty(i)){
		v=(x)[i];
		console["log"](i);
		console.log(v)
	}
};
