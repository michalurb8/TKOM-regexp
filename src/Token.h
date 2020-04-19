#pragma once

struct Token
{
    enum token_type
    {
        SYMBOL,                 //any symbol to be recognized, e.g. a, c, %, * "\"
        ESC_SYMBOL,                 //any symbol to be recognized, e.g. a, c, %, * "\"
        LPAREN,                 //opening parenthesis (
        RPAREN,                 //closing parenthesis )
        SPECIAL,                //special character, one of ., $, ^
        OPERATOR,               //operator, one of *, +, ?
        ALTER,                  //alternative |
        SET,                    //set token, e.g. [asd-xf]

        NOT_ASSINGED            //for debugging
    };
    token_type type;            //token type
    char value;                 //if a token has a value, it is a character
    unsigned int textPos;       //token position in text, for debugging

public:
    Token(token_type typeArg, char valueArg, int textPosArg);
    Token();

    void Print();
};