#pragma once
#include "Scanner.h"
#include "Source.h"
#include "Token.h"
class Parser
{
    unsigned int errorPos;
    Scanner scanner;
    bool ParseAlt();
    bool ParseCon();
    bool ParseElem();
    bool ParseParen();
    bool ParseInter();
    bool ParseSet();

public:
    Parser() = delete;
    Parser(std::string text);
    bool Parse();
    unsigned int getErrorPos();
};

bool checkOperator(Token arg);
bool checkSymbol(Token arg);
bool checkInBrackets(Token arg);
bool checkAlt(Token arg);
bool checkLParen(Token arg);
bool checkRParen(Token arg);
bool checkLBracket(Token arg);
bool checkRBracket(Token arg);
bool checkCaret(Token arg);
bool checkInterval(Token arg);
bool checkEOT(Token arg);