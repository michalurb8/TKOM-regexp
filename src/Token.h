#pragma once
#include <string>

struct Token
{
    enum token_type
    {
        SYMBOL,                 //any regexp symbol to be recognized, e.g. a, c, %, o
        ESC_SYMBOL,             //any escaped symbol to be recognized, e.g. "\*"
        LPAREN,                 //left parenthesis (
        RPAREN,                 //right parenthesis )
        SPECIAL,                //special character, one of ., $, ^
        OPERATOR,               //operator, one of *, +, ?
        ALTER,                  //alternative |
        SET,                    //set token, e.g. [asd-xf]
        EOT,                    //end of text token

        NOT_ASSINGED            //for debugging
    };
    token_type type;            //token type
    std::string value;          //token value stored as a string
    unsigned int textPos;       //token position in text, used for debugging

public:
    Token();

    void print() const;         //used for debugging

    token_type getType() const;
    std::string  getValue() const;
    unsigned int getTextPos() const;
};