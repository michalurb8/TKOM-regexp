#include "Parser.h"
#include <iostream>
Parser::Parser(Scanner* arg)
:scanner(arg), errorPos(-1)
{
}

bool Parser::Parse()
{
    std::cout << "REG" << std::endl;
    scanner->getNextToken(); //load first token
    return ParseAlt();
}

bool Parser::ParseAlt()
{
    std::cout << "ALT" << std::endl;
    if(!ParseCon()) return false;
    Token checkLoop = scanner->getCurrentToken();
    while(checkLoop.value == '|' && checkLoop.escaped == false)
    {
        std::cout << "alt" << std::endl;
        //parsing alternative here
        scanner->getNextToken();
        if(!ParseCon()) return false;
        checkLoop = scanner->getCurrentToken();
    }
    return true;
}

bool Parser::ParseCon()
{
    std::cout << "CON" << std::endl;
    if(!ParseElem()) return false;
    while(ParseElem()){}
    return true;
}

bool Parser::ParseElem()
{
    std::cout << "ELE" << std::endl;
    if(checkSymbol(scanner->getCurrentToken()))
    {
        std::cout << "symb" << std::endl;
        //parsing single symbol here TODO
        scanner->getNextToken();
    }
    else if(ParseParen()) {}
    else if(ParseSet()) {}
    else return false;
    if(checkOperator(scanner->getCurrentToken()))
    {
        std::cout << "operator" << std::endl;
        //parsing operator here TODO
        scanner->getNextToken();
    }
    return true;
}

bool Parser::ParseParen()
{
    std::cout << "PAREN" << std::endl;
    if(scanner->getCurrentToken().value == '(' && scanner->getCurrentToken().escaped == false)
    {
        std::cout << "lparen" << std::endl;
        //parsing Lparen here TODO
        scanner->getNextToken();
    }
    else return false;
    ParseAlt();
    if(scanner->getCurrentToken().value == ')' && scanner->getCurrentToken().escaped == false)
    {
        std::cout << "rparen" << std::endl;
        //parsing Rparen here TODO
        scanner->getNextToken();
    }
    else return false;
    return true;
}

bool Parser::ParseInter()
{
    std::cout << "INTER" << std::endl;
    if(checkInBrackets(scanner->getCurrentToken()))
    {
        //parsing first inbracket here TODO
        scanner->getNextToken();
    }
    else return false;
    if(scanner->getCurrentToken().value == '-' && scanner->getCurrentToken().escaped == false)
    {
        //parsing Rparen here TODO
        scanner->getNextToken();
    }
    else return false;
    if(checkInBrackets(scanner->getCurrentToken()))
    {
        //parsing second inbracket here TODO
        scanner->getNextToken();
    }
    return true;
}

bool Parser::ParseSet()
{
    std::cout << "SET" << std::endl;
    return false;
}

unsigned int Parser::getErrorPos()
{
    return scanner->getCurrentToken().textPos;
}

bool checkOperator(Token arg)
{
    if(arg.escaped == true) return false;
    if(arg.value == 0x03) return false;
    if(arg.value == '*') return true;
    if(arg.value == '+') return true;
    if(arg.value == '?') return true;
    return false;
}


bool checkSymbol(Token arg)
{
    if(arg.escaped == true) return true;
    switch(arg.value)
    {
        case '(': case ')': case '[': case ']':
        case '*': case '+': case '?':
        case '-':
        case '|':
        case 0x03:
        return false;
    }
    return true;
}

bool checkInBrackets(Token arg)
{
    if(arg.escaped == true) return true;
    if(arg.value == 0x03) return false;
    if(arg.value == '-') return false;
    if(arg.value == ']') return false;
    return true;
}