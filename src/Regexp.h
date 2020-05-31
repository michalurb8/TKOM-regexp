#pragma once

#include <string>

#include <vector>
#include <set>

#include "Position.h"
#include "Parser.h"

struct Dtrans
{
    unsigned int currentState;
    char input;
    unsigned int nextState;
};

struct State
{
    std::set<unsigned int> nextPos;
    bool acceptable;
};

class Regexp
{
    std::vector<State> states;
    std::vector<Dtrans> transitions;
    Parser parser;
    
public:
    Regexp(std::string text = "");
    void loadText(std::string text);
    bool build();
    bool checkAcceptable(unsigned int a);
};