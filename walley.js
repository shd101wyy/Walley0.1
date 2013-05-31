function isalpha(e) {
    return /^[ a-z]+$/i.test(e)
}
function isdigit(e) {
    return !isNaN(parseFloat(e)) && isFinite(e);
}
none = null;
String.prototype.find = function (e, t) {
    if (typeof t == "undefined") {
        t = 0
    }
    return this.indexOf(e, t)
};
String.prototype.tolower = function () {
    return this.toLowerCase()
};
String.prototype.toupper = function () {
    return this.toUpperCase()
};
String.prototype.reverse = function () {
    return this.split("").reverse().join()
};
Math["cot"] = function (e) {
    return 1 / Math.tan(e)
};
Math["sec"] = function (e) {
    return 1 / Math.cos(e)
};
Math["csc"] = function (e) {
    return 1 / Math.sin(e)
};
Object.prototype.slice = function (e, t) {
    var n = {};
    var r = 0;
    for (var i = e; i < t; i++) {
        n[r] = this[i];
        r++
    }
    return n
};
Object.prototype.append = function (e) {
    var t = "-1";
    for (var n in this) {
        if (!isNaN(n)) {
            if (n > t) {
                t = n
            }
        }
    }
    if (t != "-1") {
        t = parseInt(t) + 1
    } else {
        t = "0"
    }
    this[t] = e
}
INCOMPLETE_STATEMENT = false;
Walley_Print_Error = function (input_str, error_message, error_start_index) {
    console["log"]("Error.. %s\n", error_message);
    console["log"]("%s\n", input_str);
    var empty = "";
    var i = 0;
    for (; i < error_start_index; i = i + 1) {
        empty = empty + " ";

    };
    empty = empty + "^";
    console["log"]("%s\n", empty);
};
Token_init = function () {
    var Token = {};
    Token["TOKEN_CLASS"] = "";
    Token["TOKEN_STRING"] = "";
    Token["TOKEN_START"] = -1;
    Token["TOKEN_END"] = -1;
    return Token;
};
TOKEN_print = function (token) {
    console["log"](token["TOKEN_CLASS"] + ":" + "|" + token["TOKEN_STRING"] + "|" + token["TOKEN_START"] + "|" + token["TOKEN_END"]);
};
TL_toString = function (tl) {
    var return_string = "";
    for (i in tl) {
        v = (tl)[i];
        return_string = return_string + v["TOKEN_STRING"];
    }
};
TL_addToken = function (tl, add_token) {
    var temp_token = Token_init();
    temp_token["TOKEN_CLASS"] = add_token["TOKEN_CLASS"];
    temp_token["TOKEN_STRING"] = add_token["TOKEN_STRING"];
    temp_token["TOKEN_START"] = add_token["TOKEN_START"];
    temp_token["TOKEN_END"] = add_token["TOKEN_END"];
    tl["append"](temp_token);
};
TL_indexOfTokenThatHasTokenString = function (tl, token_string) {
    var output = -1;
    var i = 0;
    for (i = 0; i < tl["length"]; i = i + 1) {
        if (tl[i]["TOKEN_STRING"] === token_string) {
            return i;
        }

    };
    return -1;
};
TL_indexOfTokenThatHasTokenClass = function (tl, token_string) {
    var output = -1;
    var i = 0;
    for (i = 0; i < tl["length"]; i = i + 1) {
        if (tl[i]["TOKEN_CLASS"] === token_string) {
            return i;
        }

    };
    return -1;
};
match = function (input_str, index, match_string) {
    var length_of_input_str = input_str["length"];
    var length_of_match_str = match_string["length"];
    if (length_of_input_str < index + length_of_match_str) {
        return false;
    }
    var i = 0;
    var match = true;
    for (; i < length_of_match_str; i = i + 1) {
        if (input_str[index + i] !== match_string[i]) {
            match = false;
            break;
        }

    };
    if (match === true) {
        return true;
    } else {
        return false;
    }
};
term = function (input_str1, input_str2) {
    if (input_str1 === input_str2) {
        return true;
    } else {
        return false;
    }
};
LIST_indexOfFinalBracket = function (input_str, index_of_first_bracket) {
    var count = 0;
    var in_string = false;
    var length_of_input_str = input_str["length"];
    var i = index_of_first_bracket;
    for (; i < length_of_input_str; i = i + 1) {
        if (((in_string === false && input_str[i] === "\"") && input_str[i - 1] !== "\\")) {
            in_string = true;
            continue;
        }
        if (((in_string === true && input_str[i] === "\"") && input_str[i - 1] !== "\\")) {
            in_string = false;
            continue;
        }
        if (in_string === false) {
            if (input_str[i] === "[") {
                count = count + 1;
                continue;
            }
            if (input_str[i] === "]") {
                count = count - 1;
                if (count === 0) {
                    return i;
                } else {
                    continue;
                }
            }
        }

    };
    return -1;
};
indexOfFinalDoubleQuote = function (input_str, first_index) {
    var first_char = input_str[first_index];
    var i = first_index + 1;
    var length = input_str["length"];
    if (first_char === "\"") {
        for (; i < length; i = i + 1) {
            if ((input_str[i] === "\"" && input_str[i - 1] !== "\\")) {
                return i;
            }
            if ((input_str[i] === "\"" && input_str[i - 1] === "\\")) {
                if (input_str[i - 2] === "\\") {
                    return i;
                }
            }

        }
    }
    return -1;
};
Walley_Analyze_Token_Class = function (input_str, i) {
    console.log("-------> "+input_str[i]);
    var return_obj = {};
    var length = input_str["length"];
    if (match(input_str, i, "**")) {
        end_index = i + 2;
        return_obj[0] = end_index;
        return_obj[1] = "m_operator";
        return return_obj;
    }
    if ((((((match(input_str, i, "+") || match(input_str, i, "-")) || match(input_str, i, "*")) || match(input_str, i, "/")) || match(input_str, i, "^")) || match(input_str, i, "%"))) {
        end_index = i + 1;
        return_obj[0] = end_index;
        return_obj[1] = "m_operator";
        return return_obj;
    }
    if ((match(input_str, i, ",") || match(input_str, i, ":"))) {
        end_index = i + 1;
        return_obj[0] = end_index;
        return_obj[1] = "punctuation";
        return return_obj;
    }
    if ((((match(input_str, i, "==") || match(input_str, i, ">=")) || match(input_str, i, "<=")) || match(input_str, i, "!="))) {
        end_index = i + 2;
        return_obj[0] = end_index;
        return_obj[1] = "judge_sign";
        return return_obj;
    }
    if ((input_str[i] === ">" || input_str[i] === "<")) {
        end_index = i + 1;
        return_obj[0] = end_index;
        return_obj[1] = "judge_sign";
        return return_obj;
    }
    if (((match(input_str, i, "and") || match(input_str, i, "not")) && ((length <= i + 3 || input_str[i + 3] === " ") || input_str[i + 3] === "\n"))) {
        end_index = i + 3;
        return_obj[0] = end_index;
        return_obj[1] = "relation";
        return return_obj;
    }
    if ((match(input_str, i, "or") && ((length <= i + 2 || input_str[i + 2] === " ") || input_str[i + 2] === "\n"))) {
        end_index = i + 2;
        return_obj[0] = end_index;
        return_obj[1] = "relation";
        return return_obj;
    }
    if (((i <= length - 2 && input_str[i] === "#") && input_str[i + 1] === "~")) {
        end_index = i + 2;
        return_obj[0] = end_index;
        return_obj[1] = "l_annotation";
        return return_obj;
    }
    if ((i <= length - 2 && (input_str[i] === "~" && input_str[i + 1] === "#"))) {
        end_index = i + 2;
        return_obj[0] = end_index;
        return_obj[1] = "r_annotation";
    }
    if (((i <= length - 2 && match(input_str, i, "if")) && ((length <= i + 2 || input_str[i + 2] === " ") || input_str[i + 2] === "\n"))) {
        end_index = i + 2;
        return_obj[0] = end_index;
        return_obj[1] = "keyword";
        return return_obj;
    }
    if (((match(input_str, i, "for") || match(input_str, i, "def")) && ((length <= i + 3 || input_str[i + 3] === " ") || input_str[i + 3] === "\n"))) {
        end_index = i + 3;
        return_obj[0] = end_index;
        return_obj[1] = "keyword";
        return return_obj;
    }
    if ((((match(input_str, i, "elif") || match(input_str, i, "else")) || match(input_str, i, "case")) && ((length <= i + 4 || input_str[i + 4] === " ") || input_str[i + 4] === "\n"))) {
        end_index = i + 4;
        return_obj[0] = end_index;
        return_obj[1] = "keyword";
        return return_obj;
    }
    if (((match(input_str, i, "while") || match(input_str, i, "class")) && ((length <= i + 5 || input_str[i + 5] === " ") || input_str[i + 5] === "\n"))) {
        end_index = i + 5;
        return_obj[0] = end_index;
        return_obj[1] = "keyword";
        return return_obj;
    }
    if ((match(input_str, i, "then") && ((length <= i + 4 || input_str[i + 4] === " ") || input_str[i + 4] === "\n"))) {
        end_index = i + 4;
        return_obj[0] = end_index;
        return_obj[1] = "then";
        return return_obj;
    }
    if ((match(input_str, i, "end") && ((length <= i + 3 || input_str[i + 3] === " ") || input_str[i + 3] === "\n"))) {
        end_index = i + 3;
        return_obj[0] = end_index;
        return_obj[1] = "end";
        return return_obj;
    }
    if (((match(input_str, i, "return") && i + 6 < length) && input_str[i + 6] === " ")) {
        end_index = i + 6;
        return_obj[0] = end_index;
        return_obj[1] = "return";
        return return_obj;
    }
    if ((match(input_str, i, "local") && ((length <= i + 5 || input_str[i + 5] === " ") || input_str[i + 5] === "\n"))) {
        end_index = i + 5;
        return_obj[0] = end_index;
        return_obj[1] = "local";
        return return_obj;
    }
    if (match(input_str, i, "switch")) {
        end_index = i + 6;
        return_obj[0] = end_index;
        return_obj[1] = "keyword";
        return return_obj;
    }
    if (input_str[i] === "=") {
        end_index = i + 1;
        return_obj[0] = end_index;
        return_obj[1] = "assignment_operator";
        return return_obj;
    }
    if (input_str[i] === "#") {
        end_index = i + 1;
        return_obj[0] = end_index;
        return_obj[1] = "annotation";
        return return_obj;
    }
    if ((((input_str[i] === "(" || input_str[i] === ")") || input_str[i] === "{") || input_str[i] === "}")) {
        end_index = i + 1;
        var output = input_str[i];
        return_obj[0] = end_index;
        return_obj[1] = output;
        return return_obj;
    }
    if (input_str[i] === "[") {
        var index_of_final = LIST_indexOfFinalBracket(input_str, i);
        if (index_of_final === -1) {
            INCOMPLETE_STATEMENT = true;
        }
        end_index = index_of_final + 1;
        return_obj[0] = end_index;
        return_obj[1] = "list_table";
        return return_obj;
    }
    if (input_str[i] === "\"") {
        var index_of_right_dq = indexOfFinalDoubleQuote(input_str, i);
        if (index_of_right_dq === -1) {
            console["log"]("incomplete str\n");
            exit(0)
        } else {
            end_index = index_of_right_dq + 1;
            return_obj[0] = end_index;
            return_obj[1] = "string";
            return return_obj;
        }
    }
    if (isdigit(input_str[i]) === true) {
        var a = i + 1;
        var find_dot = false;
        var index_of_first_dot = -1;
        for (; a < length; a = a + 1) {
            if ((input_str[a] === "." && find_dot === false)) {
                find_dot = true;
                index_of_first_dot = a;
                continue;
            }
            if ((input_str[a] === "." && find_dot === true)) {
                if (isdigit(input_str[a + 1])) {
                    Walley_Print_Error(input_str, "invalide number", a)
                } else {
                    end_index = a;
                    return_obj[0] = end_index;
                    return_obj[1] = "num";
                    return return_obj;
                }
            }
            if (isdigit(input_str[a]) === false) {
                break;
            }

        }
        if ((find_dot === true && isdigit(input_str[index_of_first_dot + 1]) === false)) {
            end_index = index_of_first_dot;
            return_obj[0] = end_index;
            return_obj[1] = "num";
            return return_obj;
        }
        if ((a !== length && isalpha(input_str[a]))) {
            Walley_Print_Error(input_str, "Invalid Syntax", a)
        }
        end_index = a;
        return_obj[0] = end_index;
        return_obj[1] = "num";
        return return_obj;
    }
    if (((input_str[i] === " " || input_str[i] === "\n") || input_str[i] === "\t")) {
        var a = i + 1;
        for (; a < length; a = a + 1) {
            if (((input_str[a] !== " " && input_str[a] !== "\n") && input_str[a] !== "\t")) {
                break;
            }

        }
        console.log("IT IS EMPTY");

        end_index = a;
        return_obj[0] = end_index;
        return_obj[1] = "white_space";
        return return_obj;
    }
    if (((isalpha(input_str[i]) || input_str[i] === "_") || input_str[i] === "$")) {
        var a = i + 1;
        for (; a < length; a = a + 1) {
            if ((((isalpha(input_str[a]) || input_str[a] === "_") || input_str[a] === "$") || isdigit(input_str[a]))) {
                continue;
            } else {
                break;
            }

        }
        end_index = a;
        return_obj[0] = end_index;
        return_obj[1] = "id";
        return return_obj;
    }
    if (input_str[i] === ".") {
        var a = i + 1;
        end_index = a;
        return_obj[0] = end_index;
        return_obj[1] = "dot";
        return return_obj;
    }
    Walley_Print_Error(input_str, "Can not analyze this input", i);
    exit(0);
};
Walley_Lexical_Analyzie = function (input_str) {
    var i = 0;
    var length = input_str["length"];
    var tl = {};
    var end_index = 0;
    for (; i < length; i = i + 1) {
        var output_data = Walley_Analyze_Token_Class(input_str, i, end_index);
        end_index = output_data[0];
        var token_class = output_data[1];
        if (INCOMPLETE_STATEMENT === true) {
            break;
        }
        if (token_class === "white_space") {
            i = end_index - 1;
            continue;
        }
        if (token_class === "annotation") {
            for (i = end_index; i < length; i = i + 1) {
                if (input_str[i] === "\n") {
                    break;
                }

            }
            continue;
        }
        if (token_class === "l_annotation") {
            i = end_index;
            var count = 0;
            var find_right_annotation = false;
            for (; i < length - 1; i = i + 1) {
                if (input_str[i] === "\"") {
                    count = count + 1;
                    continue;
                }
                if (((count % 2 === 0 && input_str[i] === "~") && input_str[i + 1] === "#")) {
                    i = i + 1;
                    find_right_annotation = true;
                    break;
                }

            }
            if (find_right_annotation === false) {
                INCOMPLETE_STATEMENT = true;
                return tl;
            }
            continue;
        }
        temp_token = Token_init();
        temp_token["TOKEN_START"] = i;
        temp_token["TOKEN_END"] = end_index;
        temp_token["TOKEN_CLASS"] = token_class;
        var token_string = "";
        token_string = input_str.slice(i, end_index);
        temp_token["TOKEN_STRING"] = token_string;
        tl["append"](temp_token);
        i = end_index - 1;

    };
    return tl;
};


//x=" Hello"
//console.log(x);
//console.log(x[0]);
//console.log(isdigit("  "));

var tl=Walley_Lexical_Analyzie("def x() then x=12 end")
console.log(tl)












