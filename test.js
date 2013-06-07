var myObj = {
    1: [1, 2, 3],
    2: [4, 5, 6]
};

var array = $.map(myObj, function(k, v) {
    return [k];
});


console.log(array);