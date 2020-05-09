#include "Token.h"
#include "Source.h"
#include "Scanner.h"
#include <iostream>

bool Assert(bool check, std::string message)
{
    if(!check) std::cout << "Test failed: " << message << std::endl;
    return check;
}

int main()
{
    Token temp;
    Scanner scanner(&source);

//to be refactored to boost tests
    source = Source("abc");
    Assert(source.getPos() == 0, "GET_POS_STARTS_AT_0");
    Assert(source.peekChar() == 'a', "PEEK_CHAR_WORKS");
    Assert(source.getPos() == 0, "GET_POS_STARTS_AT_0");
    Assert(source.getChar() == 'a', "GET_CHAR_WORKS_A");
    Assert(source.getPos() == 1, "GET_POS_WORKS");
    Assert(source.getChar() == 'b', "GET_CHAR_WORKS_B");
    Assert(source.getChar() == 'c', "GET_CHAR_WORKS_C");
    Assert(source.getChar() == 0x03, "GET_CHAR_WORKS_END_OF_TEXT");
    Assert(source.getChar() == 0x03, "GET_CHAR_WORKS_END_OF_TEXT_AGAIN");
    Assert(source.peekChar() == 0x03, "PEEK_CHAR_WORKS_END_OF_TEXT");
    Assert(source.getPos() == 3, "GET_POS_STAYS_AT_THE_END");

    source = Source("ab*()");
    Assert(scanner.getNextToken().getValue() == 'a', "GET_NEXT_VALUE_CORRECT_A");
    Assert(scanner.getCurrentToken().getValue() == 'a', "GET_CURRENT_VALUE_CORRECT");
    Assert(scanner.getNextToken().getValue() == 'b', "GET_NEXT_VALUE_CORRECT_B");
    Assert(scanner.getNextToken().getValue() == '*', "GET_*_VALUE_CORRECT");
    Assert(scanner.getNextToken().getTextPos() == 3, "GET_(_POS_CORRECT");
    Assert(scanner.getNextToken().getTextPos() == 4, "GET_)_POS_CORRECT");
    Assert(scanner.getNextToken().getTextPos() == 5, "GET_EOT_POS_CORRECT");
    Assert(scanner.getNextToken().getTextPos() == 5, "GET_EOT_POS_CORRECT_AGAIN");
    Assert(scanner.getNextToken().getValue() == 0x03, "GET_EOT_VALUE_CORRECT");

    std::cout << "ALL TESTS COMPLETED" << std::endl;
}