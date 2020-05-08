#include "Token.h"
#include <iostream>

Token::Token()
:value(0x03), textPos(-1), escaped(false)
{
}

char Token::getValue() const
{
    return value;
}
unsigned int Token::getTextPos() const
{
    return textPos;
}

void print(Token arg)
{
    std::cout
    << "Value: '" << arg.value
    << "', int value: " << (int)arg.value
    << ", position: " << arg.textPos
    << ", escaped: " << (arg.escaped ? "yes" : "no")
    << std::endl;
}