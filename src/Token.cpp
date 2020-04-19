#include "Token.h"
#include <iostream> //TODO TEMPORARY

Token::Token(token_type typeArg, char valueArg, int textPosArg)
:type(typeArg), value(valueArg), textPos(textPosArg)
{
}

Token::Token()
{
    type = NOT_ASSINGED;
    value = '\0';
    textPos = -1;
}

void Token::Print()
{
    std::cout << "type: '" << type << "' value: '" << value << "' position: " << textPos << std::endl;
}