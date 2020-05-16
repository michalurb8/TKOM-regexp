#pragma once
#include "Scanner.h"
#include "Node.h"

class Parser
{
    std::string errorDesc;
    Scanner scanner;
    Node* ParseAlt();
    Node* ParseCon();
    Node* ParseElem();
    Node* ParseParen();
    void ParseInter();
    Node* ParseSet();
    Node* ParseSymbol();
    Node* ParseOp(Node* arg);

    bool valid;

public:
    Parser() = delete;
    Parser(std::string text);

    Node* Parse();
    void accept();

    bool getCorrect() const;
    unsigned int getErrorPos() const;
    const std::string& getErrorDesc() const;
};