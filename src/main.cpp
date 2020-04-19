#include <iostream>
#include "Source.h"
#include "Scanner.h"
#include "Token.h"

int main()
{
    Source tekscik("aBcE5");
    Scanner lexer(&tekscik);

    Token a;
    Token* ptr = &a;
    std::cout << lexer.getNextToken(ptr) << std::endl;
    std::cout << lexer.getNextToken(ptr) << std::endl;
    std::cout << lexer.getNextToken(ptr) << std::endl;
    std::cout << lexer.getNextToken(ptr) << std::endl;
    std::cout << lexer.getNextToken(ptr) << std::endl;
//    a.Print();
    return 0;
}