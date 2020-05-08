#pragma once
#include "Scanner.h"
#include "Token.h"
class Parser
{
    unsigned int errorPos;
    Scanner* scanner;
    bool ParseAlt();
    bool ParseCon();
    bool ParseElem();
    bool ParseParen();
    bool ParseInter();
    bool ParseSet();

public:
    Parser(Scanner* arg);
    bool Parse();
    unsigned int getErrorPos();
};

bool checkOperator(Token arg);
bool checkSymbol(Token arg);
bool checkInBrackets(Token arg);