#pragma once
#include <string>

struct Token
{
    enum token_type
    {
        SYMBOL,                 //any symbol to be recognized, e.g. a, c, %, * "\"
        ESC_SYMBOL,             //any symbol to be recognized, e.g. a, c, %, * "\"
        LPAREN,                 //opening parenthesis (
        RPAREN,                 //closing parenthesis )
        SPECIAL,                //special character, one of ., $, ^
        OPERATOR,               //operator, one of *, +, ?
        ALTER,                  //alternative |
        SET,                    //set token, e.g. [asd-xf]
        EOT,                    //end of text token

        NOT_ASSINGED            //for debugging
    };
    token_type type;            //token type
    std::string value;                 //if a token has a value, it is a character
    unsigned int textPos;       //token position in text, for debugging

public:
    Token();

    void print() const;
    token_type getType() const;
    std::string  getValue() const;
    unsigned int getTextPos() const;
};