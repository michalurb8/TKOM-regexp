#pragma once
#include <string>

class Source
{
    std::string text;
    unsigned int currentPos;
    unsigned int size;

public:
    Source(std::string textArg = "");

    char peekChar() const;
    char getChar();
    unsigned int getPos() const;
    void reset();
};