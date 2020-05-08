#include "Token.h"
#include <iostream>

Token::Token()
:value(0x03), textPos(-1), escaped(false)
{
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