#include "Parser.h"
#include <iostream>

Parser::Parser(std::string text)
:errorDesc(""), scanner(text), valid(true)
{
}

void Parser::Parse() //Reg -> Alt, $;
{
    result.reset();
    errorDesc = "";
    scanner.getNextToken();
    valid = true;

    //Parsing ALT:
    if(ParseAlt()) {}
    else
    {
        errorDesc = "Empty expression";
        valid = false;
        return;
    }
    //Parsing $:
    if(checkEOT(scanner.getCurrentToken()))
    {
        result.createSon('$', Node::END);
        result.goUp();
    }
    else
    {
        errorDesc = "Expecting EOT";
        valid = false;
        return;
    }
    result.print(); //For now parse just prints the tree structure
}

bool Parser::ParseAlt() //Alt -> Con, {"|", Con};
{
    result.createSon('|', Node::ALT);
    //Parsing CON:
    if(ParseCon()) {}
    else
    {
            errorDesc = "Expecting a concatenation";
            valid = false;
            return false;
    }
    //Checking if next token |, if so, parsing CON again:
    while(checkAlt(scanner.getCurrentToken()))
    {
        scanner.getNextToken();
        if(ParseCon()) {}
        else
        {
            errorDesc = "Cannot match the symbol after |";
            valid = false;
            return false;
        }
    }
    result.goUp();
    return true;
}

bool Parser::ParseCon() //Con -> Elem, {Elem};
{
    result.createSon('*', Node::CON);
    if(ParseElem()) {}
    else
    {
        errorDesc = "Expecting an element";
        valid = false;
        return false;
    }
    while(ParseElem()){}
    result.goUp();
    return true;
}

bool Parser::ParseElem() //Elem -> (symbol, Paren, Set), [op];
{
    //Trying to parse symbol:
    if(checkSymbol(scanner.getCurrentToken()))
    {
        result.createSon(scanner.getCurrentToken().value, Node::SYMBOL);
        result.goUp();
        scanner.getNextToken();
    }
    //Trying to parse Paren:
    else if(ParseParen()) {}
    //Trying to parse Set:
    else if(ParseSet()) {}
    else return false;
    //Checking if can parse operator:
    if(checkOperator(scanner.getCurrentToken())) //optional
    {
        result.createSon(scanner.getCurrentToken().value, Node::OP);
        result.goUp();
        scanner.getNextToken();
    }
    return true;
}

bool Parser::ParseParen() //Paren -> "(", Alt, ")";
{
    //Checking if can parse (:
    if(checkLParen(scanner.getCurrentToken()))
    {
        scanner.getNextToken();
    }
    else return false;
    //Parsing ALT:
    if(ParseAlt()) {}
    else
    {
        errorDesc = "Nothing between ()";
        valid = false;
        return false;
    }
    //Parsing ):
    if(checkRParen(scanner.getCurrentToken()))
    {
        scanner.getNextToken();
    }
    else
    {
        errorDesc = "Missing )";
        valid = false;
        return false;
    }

    return true;
}

bool Parser::ParseInter() //Inter -> inset, ["-", inset];
{
    //Parsing first element of interval:
    if(checkInBrackets(scanner.getCurrentToken()))
    {
        result.createSon('I', Node::INTER);
        result.createSon(scanner.getCurrentToken().value, Node::INSET);
        result.goUp();
        scanner.getNextToken();
    }
    else return false;
    //Checking if it is a set (- sign):
    if(checkInterval(scanner.getCurrentToken()))
    {
        scanner.getNextToken();
        //if so, parsing second element:
        if(checkInBrackets(scanner.getCurrentToken()))
        {
            result.createSon(scanner.getCurrentToken().value, Node::INSET);
            result.goUp();
            scanner.getNextToken();
        }
        else
        {
            errorDesc = "Current token does not match any set[] element";
            valid = false;
            return false;
        }
    }
    result.goUp();
    return true;
}

bool Parser::ParseSet() //Set -> "[", ["^"], ("]" | Inter), {Inter}, "]";
{
    //trying to parse first bracket:
    if(checkLBracket(scanner.getCurrentToken()))
    {
        result.createSon('[', Node::SET);
        scanner.getNextToken();
    }
    else return false;
    //trying to parse caret (optional):
    if(checkCaret(scanner.getCurrentToken()))
    {
        result.createSon('^', Node::CARET);
        result.goUp();
        scanner.getNextToken();
    }
    //trying to parse right bracket as an element
    if(checkRBracket(scanner.getCurrentToken()))
    {
        result.createSon(']', Node::INSET);
        result.goUp();
        scanner.getNextToken();
    }
    //otherwise parsing a set symbol
    else if(ParseInter()) {}
    else
    {
        errorDesc = "Current token does not match any set[] element";
        valid = false;
        return false;
    }
    //Parsing set symbols in a loop
    while(ParseInter()){}
    //Parsing the right bracket
    if(checkRBracket(scanner.getCurrentToken()))
    {
        scanner.getNextToken();
    }
    else
    {
        errorDesc = "Current token does not match ] symbol";
        valid = false;
        return false;
    }
    result.goUp();
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

bool Parser::getCorrect() const
{
    return valid;
}

//parsing according to the following grammar:
/*
    Reg -> Alt, $;
    Alt -> Con, {"|", Con};
    Con -> Elem, {Elem};
    Elem -> (symbol, Paren, Set), [op];
    Paren -> "(", Alt, ")";
    Set -> "[", ["^"], ("]" | Inter), {Inter}, "]";
    Inter -> inset, ["-", inset];

    symbol -> ?all escaped? + "]" + "." + "^" + "$" + "-";
    inset -> ?all? - "-" - "]";
    op -> "*", "+", "?";
*/