#include "Token.h"
#include <iostream>

Token::Token()
:value(0x03), textPos(-1), escaped(false)
{
}

bool checkOperator(const Token& arg)
{
    if(arg.escaped == true) return false;
    if(arg.value == 0x03) return false;
    if(arg.value == '*') return true;
    if(arg.value == '+') return true;
    if(arg.value == '?') return true;
    return false;
}


bool checkSymbol(const Token& arg)
{
    if(arg.escaped == true) return true;
    switch(arg.value)
    {
        case '(': case '[': case ')':
        case '*': case '+': case '?':
        case '|':
        case 0x03:
        return false;
    }
    return true;
}

bool checkInSet(const Token& arg)
{
    if(arg.escaped == true) return true;
    if(arg.value == 0x03) return false;
    if(arg.value == '-') return false;
    if(arg.value == ']') return false;
    return true;
}

bool checkLParen(const Token& arg)
{
    if(arg.value == '(' && arg.escaped == false) return true;
    return false;
}

bool checkRParen(const Token& arg)
{
    if(arg.value == ')' && arg.escaped == false) return true;
    return false;
}

bool checkLBracket(const Token& arg)
{
    if(arg.value == '[' && arg.escaped == false) return true;
    return false;
}

bool checkRBracket(const Token& arg)
{
    if(arg.value == ']' && arg.escaped == false) return true;
    return false;
}

bool checkAlt(const Token& arg)
{
    if(arg.value == '|' && arg.escaped == false) return true;
    return false;
}

bool checkCaret(const Token& arg)
{
    if(arg.value == '^' && arg.escaped == false) return true;
    return false;
}

bool checkDash(const Token& arg)
{
    if(arg.value == '-' && arg.escaped == false) return true;
    return false;
}

bool checkDot(const Token& arg)
{
    if(arg.value == '.' && arg.escaped == false) return true;
    return false;
}

bool checkEOT(const Token& arg)
{
    if(arg.value == 0x03) return true;
    return false;
}