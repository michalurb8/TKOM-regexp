#pragma once
#include <string>

struct Token
{
    char value;                 //token value stored as a string
    unsigned int textPos;       //token position in text, used for debugging
    bool escaped;

public:
    Token();

    char  getValue() const;
    unsigned int getTextPos() const;
};

void print(Token arg);