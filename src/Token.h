#pragma once

struct Token
{
    enum token_type
    {
        SYMBOL,                 //any symbol to be recognized, e.g. a, c, %, * "\"
        O_BRACKET,              //opening bracket [
        C_BRACKET,              //closing bracket ]
        O_PAREN,                //opening parenthesis (
        C_PAREN,                //closing parenthesis )
        SPECIAL,                //special character, one of ., $, ^
        OPERATOR,               //operator, one of *, +, ?
        ALTER,                  //alternative |

        //tokens only found inside brackets, e.g. [ab-x99]8]
        EXCEPT,                 //exception character ^
        INTERVAL                //interval character -
    };
    token_type type;        //token type
    char value;             //if a token has a value, it is a character
    int textPos;            //token position in text, for debugging

    Token(token_type typeArg, char valueArg, int textPosArg);
};