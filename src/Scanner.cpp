#include "Scanner.h"

Scanner::Scanner(std::string text)
:source(text)
{
}

Token Scanner::getNextToken()
{
    current.textPos = source.getPos();
    char ch = source.getChar();
    if(ch == '\\')
    {
        ch = source.peekChar();
        if(ch == 0x03)
        {
            current.escaped = false;
            current.value = '\\';
        }
        else
        {
            current.escaped = true;
            ch = source.getChar();
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

Token Scanner::getCurrentToken() const
{
    return current;
}