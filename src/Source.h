#pragma once
#include <string>

class Source
{
    std::string text;
    unsigned int currentPos;
    unsigned int size;

public:
    char peekChar() const;
    char getChar();
    Source(std::string textArg);
    Source();
    unsigned int getPos() const;
};