#include <string>
#include "Source.h"

Source::Source()
{
    size = 0;
    text = "";
    currentPos = 0;
}
Source::Source(std::string textArg)
:text(textArg), currentPos(0)
{
    size = text.length();
}
Source::Source(const Source& arg)
:text(arg.text), currentPos(arg.currentPos), size(arg.size)
{
}
Source Source::operator=(const Source&arg)
{
    text = arg.text;
    currentPos = arg.currentPos;
    size = arg.size;
}
Source::~Source()
{
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

void Source::reset()
{
    currentPos = 0;
}