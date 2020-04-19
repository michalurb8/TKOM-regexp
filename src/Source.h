#pragma once
#include <string>

class Source
{
    std::string text;
    unsigned int currentPos;
    unsigned int size;

public:
    char peekChar();
    char getChar();
    Source(std::string textArg);
    Source() = delete;
    unsigned int getPos();
};