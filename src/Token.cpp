#include "Token.h"
#include <iostream>

Token::Token()
{
    type = NOT_ASSINGED;
    value = "";
    textPos = -1;
}

void Token::print() const
{
    std::cout << "type: '" << type << "' value: '" << value << "' position: " << textPos << std::endl;
}

Token::token_type Token::getType() const
{
    return type;
}
std::string Token::getValue() const
{
    return value;
}
unsigned int Token::getTextPos() const
{
    return textPos;
}