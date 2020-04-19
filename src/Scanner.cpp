#include "Scanner.h"

Scanner::Scanner(Source* sourceArg)
:source(sourceArg)
{
}

Scanner::returnCode Scanner::getNextToken(Token* token)
{
    char ch = source->getChar();
    returnCode code = SUCCESS;
    current.textPos = source->getPos() - 1;
    current.value = ch;
    switch(ch)
    {
    case 'a'...'z':
    case '0'...'9':
    case 'A'...'Z':
    case ' ': case '!': case '"': case '#': case '%': case '&': case '\'':
    case ',': case '-': case '/': case ':': case ';': case '<': case '=':
    case '>': case '@': case '_': case '`': case '~': case '{': case '}': case ']':
        current.type = Token::SYMBOL;
        break;
    case '*':
    case '+':
    case '?':
        current.type = Token::OPERATOR;
        break;
    case '^':
    case '$':
    case '.':
        current.type = Token::SPECIAL;
        break;
    case '(':
        current.type = Token::LPAREN;
        break;
    case ')':
        current.type = Token::RPAREN;
        break;
    case '|':
        current.type = Token::ALTER;
        break;
    case '\\':
        current.type = Token::ESC_SYMBOL;
        ch = source->getChar();
        if(ch < ' ' || ch > '~')        //if next character is not printable, return bad_escape 2
        {
            *token = Token();
            code = BAD_ESCAPE;
            break;
        }
        current.value = ch;
        break;
    case '[':                           //start of set
        current.type = Token::SET;
        ch = source->getChar();
        if(ch == 3)
        {
            *token = Token();
            code = MISSING_BRACKET;             //return no matching bracket 3
            break;
        }
        if(ch == '^')                   //if ^ is first, add it, then check if ] is second
        {
            current.value += ch;
            ch = source->getChar();
            if(ch == 3)
            {
                *token = Token();
                code = MISSING_BRACKET;         //return no matching bracket 3
                break;                 
            }
            if(ch == ']')
            current.value += ch;
        }
        else current.value += ch;
        do
        {
            ch = source->getChar();
            if(ch == 3)
            {
                *token = Token();
                code = MISSING_BRACKET;         //return no matching bracket 3
                break;                 
            }
            current.value += ch;
        } while (ch != ']');
        break;
    case 3:                             //EOT character
        current.type = Token::EOT;
        break;
    default:
        *token = Token();
        code = BAD_CHARACTER;                 //if no character detected, return bad_character 1
        break;
    }
    *token = current;
    return code;
}

bool Scanner::getCurrToken(Token* token)
{
    *token = current; 
    if(token->type == Token::NOT_ASSINGED) return false;
    return true;
}