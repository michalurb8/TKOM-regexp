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
    //any basic character to be recognized e.g. a, b, c, }
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
    //escaped character
        current.type = Token::ESC_SYMBOL;
        ch = source->getChar();
        if(ch < ' ' || ch > '~')        //if escaped character is not printable, return BAD_ESCAPE
        {
            *token = Token();
            code = BAD_ESCAPE;
            break;
        }
        current.value = ch;             //if it is printable, set token value to it
        break;
    case '[':                           //start of set
        current.type = Token::SET;
        ch = source->getChar();
        if(ch == 0x03)
        {
            *token = Token();
            code = MISSING_BRACKET;     //return MISSING_BRACKET if found EOT before ]
            break;
        }
        if(ch == '^')                   //if ^ is first, add it before anything and take the next
        {
            current.value += ch;
            ch = source->getChar();
            if(ch == 0x03)
            {
                *token = Token();
                code = MISSING_BRACKET;     //return MISSING_BRACKET if found EOT before ]
                break;
            }
        }
        current.value += ch;                //add the first element to the set (including ])
        do                                  //add characters to token value until ]
        {
            ch = source->getChar();
            if(ch == 0x03)
            {
                *token = Token();
                code = MISSING_BRACKET; //return MISSING_BRACKET if found EOT before ]
                break;                 
            }
            current.value += ch;
        } while (ch != ']');
        break;
    case 0x03:                          //EOT character
        current.type = Token::EOT;
        break;
    default:
        *token = Token();
        code = BAD_CHARACTER;           //if other character detected, return BAD_CHARACTER
    }
    *token = current;        //set the argument token to the current one stored as a member
    return code;
}

bool Scanner::getCurrToken(Token* token) const
{
    *token = current; 
    if(token->type == Token::NOT_ASSINGED) return false;
    return true;
}