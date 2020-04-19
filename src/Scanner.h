#pragma once
#include "Token.h"
#include "Source.h"

class Scanner
{
    Source* source;

public:
    Scanner(Source* sourceArg);
    int getNextToken(Token* token);
};