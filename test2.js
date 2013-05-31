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

x={}
x[0]=12
x[1]=15
console.log(len(x));