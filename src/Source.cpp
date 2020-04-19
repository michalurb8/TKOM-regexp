#include <string>
#include "Source.h"

Source::Source(std::string textArg)
:text(textArg), currentPos(0)
{
    text+=(char)0x03;
    size = text.length();
}

char Source::peekChar() const
{
    if(currentPos<size)
    {
        return text[currentPos];
    }
    else
    {
        return 0x03; //EOT
    }
}

char Source::getChar()
{
    if(currentPos < size)
    {
        ++currentPos;
        return text[currentPos-1];
    }
    else
    {
        return 0x03; //EOT
    }
}

unsigned int Source::getPos() const
{
    return currentPos;
}