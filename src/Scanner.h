#pragma once
#include "Token.h"
#include "Source.h"

class Scanner
{
    Source* source;
    Token current;

public:
    enum returnCode
    {
        SUCCESS, BAD_ESCAPE, BAD_CHARACTER, MISSING_BRACKET
    };
    Scanner(Source* sourceArg);
    returnCode getNextToken(Token* token);
    bool getCurrToken(Token* token) const;
};