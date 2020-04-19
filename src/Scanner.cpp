#include "Scanner.h"
#include <iostream>

Scanner::Scanner(Source* sourceArg)
:source(sourceArg)
{
}

int Scanner::getNextToken(Token* token)
{
    char ch = source->getChar();
    token->textPos = source->getPos() - 1;
    token->value = ch;
    switch(ch)
    {
    case 'a'...'z':
    case '0'...'9':
    case 'A'...'Z':
    case ' ': case '!': case '"': case '#': case '%': case '&': case '\'':
    case ',': case '-': case '/': case ':': case ';': case '<': case '=':
    case '>': case '@': case '_': case '`': case '~': case '{': case '}': case ']':
        token->type = Token::SYMBOL;
        return 0;
    case '*':
    case '+':
    case '?':
        token->type = Token::OPERATOR;
        return 0;
    case '^':
    case '$':
    case '.':
        token->type = Token::SPECIAL;
        return 0;
    case '(':
        token->type = Token::LPAREN;
        return 0;
    case ')':
        token->type = Token::RPAREN;
        return 0;
    case '|':
        token->type = Token::ALTER;
        return 0;
    case '\\':
        token->type = Token::ESC_SYMBOL;
        ch = source->getChar();
        if(ch < ' ' || ch > '~')        //if next character is not printable, return bad_escape 2
        {
            return 2;
        }
        token->value = ch;
        return 0;
    case '[':                           //start of set
        token->type = Token::SET;
        ch = source->getChar();
        if(ch == 3)
        {
            return 3;                   //return no matching bracket 3
        }
        if(ch == '^')                   //if ^ is first, add it check if ] is second
        {
            token->value += ch;
            ch = source->getChar();
            if(ch == 3)
            {
                return 3;                   //return no matching bracket 3
            }
            if(ch == ']')
            token->value += ch;
        }
        else token->value += ch;
        do
        {
            ch = source->getChar();
            if(ch == 3)
            {
                return 3;                   //return no matching bracket 3
            }
            token->value += ch;
        } while (ch != ']');
        return 0;
    case 3:                             //EOT character
        token->type = Token::EOT;
        return 0;
    }
    //if no character detected, return bad_character 1
    return 1;
}