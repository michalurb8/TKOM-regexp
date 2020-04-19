#include "Token.h"
#include "Source.h"
#include "Scanner.h"
#include <iostream>

bool Assert(bool check, std::string message)
{
    if(!check) std::cout << "ERROR in test: " << message << std::endl;
    return check;
}

int main()
{
    Token temp;
    Assert(temp.getValue()=="", "DEFAULT_TOKEN_VALUE_EMPTY");
    Assert(temp.getType()==Token::NOT_ASSINGED, "DEFAULT_TOKEN_TYPE_NOT_ASSIGNED");

    Source source("abc");
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
    Scanner scanner(&source);
    Assert(scanner.getCurrToken(&temp) == false, "GET_CURRENT_ERROR_WHEN_NO_CURRENT");
    Assert(temp.getType() == Token::NOT_ASSINGED, "EMPTY_TOKEN_IF_NO_CURRENT");
    Assert(scanner.getNextToken(&temp) == Scanner::SUCCESS, "GET_NEXT_WORKS_A");
    Assert(temp.getType() == Token::SYMBOL, "GET_NEXT_TYPE_CORRECT");
    Assert(temp.getValue() == "a", "GET_NEXT_VALUE_CORRECT");
    Assert(scanner.getCurrToken(&temp) == true, "GET_CURRENT_WORKS_IF_EXISTS");
    Assert(temp.getType() == Token::SYMBOL, "GET_CURRENT_TYPE_CORRECT");
    Assert(temp.getValue() == "a", "GET_CURRENT_VALUE_CORRECT");
    Assert(scanner.getNextToken(&temp) == Scanner::SUCCESS, "GET_NEXT_WORKS_B");
    Assert(scanner.getNextToken(&temp) == Scanner::SUCCESS, "GET_NEXT_WORKS_*");
    Assert(temp.getType() == Token::OPERATOR, "GET_*_TYPE_CORRECT");
    Assert(temp.getValue() == "*", "GET_*_VALUE_CORRECT");
    Assert(temp.getTextPos() == 2, "GET_*_POS_CORRECT");
    Assert(scanner.getNextToken(&temp) == Scanner::SUCCESS, "GET_NEXT_WORKS_(");
    Assert(scanner.getNextToken(&temp) == Scanner::SUCCESS, "GET_NEXT_WORKS_)");
    Assert(scanner.getNextToken(&temp) == Scanner::SUCCESS, "GET_NEXT_WORKS_EOT");
    Assert(temp.getType() == Token::EOT, "GET_EOT_TYPE_CORRECT");

    source = Source("[^]]a[");
    Assert(scanner.getNextToken(&temp) == Scanner::SUCCESS, "GET_NEXT_WORKS_SET");
    Assert(temp.getType() == Token::SET, "GET_SET_TYPE_CORRECT");
    Assert(temp.getValue() == "[^]]", "GET_SET_VALUE_CORRECT");
    Assert(temp.getTextPos() == 0, "GET_SET_POS_CORRECT");
    Assert(scanner.getNextToken(&temp) == Scanner::SUCCESS, "GET_NEXT_WORKS_AFTER_SET");
    Assert(temp.getType() == Token::SYMBOL, "GET_TYPE_CORRECT");
    Assert(temp.getValue() == "a", "GET_VALUE_CORRECT");
    Assert(temp.getTextPos() == 4, "GET_SET_POS_CORRECT");
    Assert(scanner.getNextToken(&temp) == Scanner::MISSING_BRACKET, "GET_NEXT_ERROR_NO_RPAREN");

    std::cout << "ALL TESTS COMPLETED" << std::endl;
}