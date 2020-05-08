#include "Scanner.h"

Scanner::Scanner(Source* sourceArg)
:source(sourceArg)
{
}

Token Scanner::getNextToken()
{
    current.textPos = source->getPos();
    char ch = source->getChar();
    if(ch == '\\')
    {
        current.escaped = true;
        ch = source->peekChar();
        if(ch == 0x03)
        {
            current.value = '\\';
        }
        else
        {
            ch = source->getChar();
            current.value = ch;
        }
    }
    else
    {
        current.value = ch;
        current.escaped = false;
    }
    return getCurrentToken();
}

Token Scanner::getCurrentToken()
{
    return current;
}