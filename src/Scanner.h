#pragma once
#include "Token.h"
#include "Source.h"

class Scanner
{
    Source* source;
    Token current;

public:
    Scanner(Source* sourceArg);
    Token getNextToken();
    Token getCurrentToken();
};