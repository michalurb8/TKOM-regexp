#pragma once
#include "Scanner.h"
#include "Node.h"
#include <memory>
#include <optional>

typedef std::unique_ptr<Node> upNode;

class Parser
{
    std::string errorDesc;
    Scanner scanner;
    upNode ParseAlt();
    upNode ParseCon();
    upNode ParseElem();
    upNode ParseParen();
    bool ParseInSet();
    upNode ParseSet();
    upNode ParseSymbol();
    upNode ParseOp(upNode elem);

    bool valid;

public:
    Parser() = delete;
    Parser(std::string text);

    upNode Parse();
    void accept();

    bool getCorrect() const;
    unsigned int getErrorPos() const;
    const std::string& getErrorDesc() const;
};