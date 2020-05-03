#include <string>
#include "Source.h"

Source::Source()
{
    size = 0;
    text = "";
}

Source::Source(std::string textArg)
:text(textArg), currentPos(0)
{
    size = text.length();
}

char Source::peekChar() const
{
    if(currentPos < size)
    {
        return text[currentPos];
    }
    else
    {
        return 0x03;
    }
}

char Source::getChar()
{
    char result;
    if(currentPos < size)
    {
        result = text[currentPos++];
    }
    else
    {
        result = 0x03;
    }
    return result;
}

unsigned int Source::getPos() const
{
    return currentPos;
}