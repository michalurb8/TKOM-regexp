#include <iostream>
#include "Source.h"
#include "Scanner.h"
#include "Token.h"

int main()
{
    std::string regexp = "[a\0a]";
    Source tekscik(regexp);
    Scanner lexer(&tekscik);

    Token a;
    Token* ptr = &a;

    ptr=ptr;

    return 0;
}