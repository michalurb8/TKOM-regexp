#pragma once
#include "Scanner.h"
#include "Tree.h"

class Parser
{
    std::string errorDesc;
    Scanner scanner;
    bool ParseAlt();
    bool ParseCon();
    bool ParseElem();
    bool ParseParen();
    bool ParseInter();
    bool ParseSet();

    Tree result;

public:
    Parser() = delete;
    Parser(std::string text);
    bool Parse();
    unsigned int getErrorPos() const;
    const std::string& getErrorDesc() const;
};