#pragma once
#include <string>

class Source
{
    std::string text;
    unsigned int currentPos;
    unsigned int size;

public:
    Source();
    Source(std::string textArg);
    Source(const Source& arg);
    Source operator=(const Source&arg);
    ~Source();

    char peekChar() const;
    char getChar();
    unsigned int getPos() const;
    void reset();
};