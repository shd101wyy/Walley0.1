String.prototype.trim = function() {
     // body...
     return this.replace(/^\s+|\s+$/g,'');
};

console.log("|%s|","  hello   world    ".trim());