#pragma once
#include "Scanner.h"
#include "Node.h"
#include <memory>
#include <set>

class Parser
{
    Scanner scanner;
    upNode ParseAlt();
    upNode ParseCon();
    upNode ParseElem();
    upNode ParseParen();
    charRange ParseInSet();
    upNode ParseSet();
    upNode ParseSymbol();

public:
    Parser(std::string text = "");
    void setRegExp(std::string text);

    upNode Parse();
    void accept();

    unsigned int getErrorPos() const;
};