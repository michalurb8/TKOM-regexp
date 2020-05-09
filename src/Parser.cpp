#include "Parser.h"
#include <iostream> //to be removed

Parser::Parser(std::string text)
:errorDesc(""), scanner(text)
{
}

bool Parser::Parse()
{
    errorDesc="";
    scanner.getNextToken();
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
    else
    {
        errorDesc = "Missing )";
        return false;
    }
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
        else
        {
            errorDesc = "Current token does not match any set[] element";
            return false;
        }
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
    else
    {
        errorDesc = "Current token does not match any set[] element";
        return false;
    }
    while(ParseInter()){}
    if(checkRBracket(scanner.getCurrentToken()))
    {
        std::cout << "bracket" << scanner.getCurrentToken().value << std::endl;
        //parsing rB here TODO
        scanner.getNextToken();
    }
    else
    {
        errorDesc = "Current token does not match ] symbol";
        return false;
    }
    return true;
}

unsigned int Parser::getErrorPos() const
{
    return scanner.getCurrentToken().textPos;
}

const std::string& Parser::getErrorDesc() const
{
    return errorDesc;
}