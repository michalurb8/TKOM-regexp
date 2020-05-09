#include "Parser.h"
#include <iostream>
Parser::Parser(std::string text)
:errorPos(-1), scanner(text)
{
}

bool Parser::Parse()
{
    scanner.getNextToken(); //load first token
    if(!ParseAlt()) return false;
    if(!checkEOT(scanner.getCurrentToken())) return false;
    std::cout << "eot" << std::endl;
    return true;
}

bool Parser::ParseAlt()
{
    if(!ParseCon()) return false;
    while(checkAlt(scanner.getCurrentToken()))
    {
        scanner.getNextToken();
        //parsing alternative sign here
        std::cout << '|' << std::endl;
        if(!ParseCon()) return false;
    }
   return true;
}

bool Parser::ParseCon()
{
    if(!ParseElem()) return false;
    while(ParseElem()){}
    return true;
}

bool Parser::ParseElem()
{
    if(checkSymbol(scanner.getCurrentToken()))
    {
        //parsing single symbol here TODO
        std::cout << scanner.getCurrentToken().value << std::endl;
        scanner.getNextToken();
    }
    else if(ParseParen()) {}
    else if(ParseSet()) {}
    else return false;
    if(checkOperator(scanner.getCurrentToken()))
    {
        //parsing operator here TODO
        std::cout << "op " << scanner.getCurrentToken().value << std::endl;
        scanner.getNextToken();
    }
    return true;
}

bool Parser::ParseParen()
{
    if(checkLParen(scanner.getCurrentToken()))
    {
        //parsing Lparen here TODO
        std::cout << "paren" << scanner.getCurrentToken().value << std::endl;
        scanner.getNextToken();
    }
    else return false;
    ParseAlt();
    if(checkRParen(scanner.getCurrentToken()))
    {
        std::cout << "paren" << scanner.getCurrentToken().value << std::endl;
        //parsing Rparen here TODO
        scanner.getNextToken();
    }
    else return false;
    return true;
}

bool Parser::ParseInter()
{
    if(checkInBrackets(scanner.getCurrentToken()))
    {
        std::cout << scanner.getCurrentToken().value << std::endl;
        //parsing first inbracket here TODO
        scanner.getNextToken();
    }
    else return false;
    if(checkInterval(scanner.getCurrentToken()))
    {
        std::cout << "interval" << scanner.getCurrentToken().value << std::endl;
        //parsing interval here TODO
        scanner.getNextToken();
        if(checkInBrackets(scanner.getCurrentToken()))
        {
            std::cout << scanner.getCurrentToken().value << std::endl;
            //parsing second inbracket here TODO
            scanner.getNextToken();
        }
        else return false;
    }
    return true;
}

bool Parser::ParseSet()
{

    if(checkLBracket(scanner.getCurrentToken()))
    {
        std::cout << "bracket" << scanner.getCurrentToken().value << std::endl;
        //parsing lB here TODO
        scanner.getNextToken();
    }
    else return false;
    if(checkCaret(scanner.getCurrentToken()))
    {
        std::cout << "caret" << scanner.getCurrentToken().value << std::endl;
        //parsing caret here TODO
        scanner.getNextToken();
    } //optional
    if(checkRBracket(scanner.getCurrentToken()))
    {
        std::cout << "rbrack" << scanner.getCurrentToken().value << std::endl;
        //parsing rbrack here TODO
        scanner.getNextToken();
    }
    else if(ParseInter()) {}
    else return false;
    while(ParseElem()){}
    if(checkRBracket(scanner.getCurrentToken()))
    {
        std::cout << "bracket" << scanner.getCurrentToken().value << std::endl;
        //parsing rB here TODO
        scanner.getNextToken();
    }
    else return false;
    return true;
}

unsigned int Parser::getErrorPos()
{
    return scanner.getCurrentToken().textPos;
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

bool checkLParen(Token arg)
{
    if(arg.value == '(' && arg.escaped == false) return true;
    return false;
}

bool checkRParen(Token arg)
{
    if(arg.value == ')' && arg.escaped == false) return true;
    return false;
}

bool checkLBracket(Token arg)
{
    if(arg.value == '[' && arg.escaped == false) return true;
    return false;
}

bool checkRBracket(Token arg)
{
    if(arg.value == ']' && arg.escaped == false) return true;
    return false;
}

bool checkAlt(Token arg)
{
    if(arg.value == '|' && arg.escaped == false) return true;
    return false;
}

bool checkCaret(Token arg)
{
    if(arg.value == '^' && arg.escaped == false) return true;
    return false;
}

bool checkInterval(Token arg)
{
    if(arg.value == '-' && arg.escaped == false) return true;
    return false;
}

bool checkEOT(Token arg)
{
    if(arg.value == 0x03) return true;
    return false;
}