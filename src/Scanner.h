#pragma once
#include "Token.h"
#include "Source.h"

class Scanner
{
    Source source;
    Token current;

public:
    Scanner() = delete;
    Scanner(std::string text);

    Token getNextToken();
    Token getCurrentToken() const;
};