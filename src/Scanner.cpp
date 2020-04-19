#include "Scanner.h"

Scanner::Scanner(Source* sourceArg)
:source(sourceArg)
{
}

int Scanner::getNextToken(Token* token)
{
    char ch = source->getChar();
    token->textPos=source->getPos();
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
        if(ch < ' ' || ch > '~') //if next character cant be escaped, return bad_escape 2
        {
            return 2;
        }
        token->value = ch;
        return 0;
    default:
        return 50;
    }
}