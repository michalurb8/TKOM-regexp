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
    std::string errorDesc;
    std::vector<State> states;
    std::vector<Dtrans> transitions;
    Parser parser;

    unsigned int currState;
    bool accepted;

    bool step(char arg);
    bool acceptable();
    
public:
    Regexp(std::string text = "");
    void loadText(std::string text);
    bool build();
    std::string getErrorDesc();

    std::vector<unsigned int> getAllMatchesGreedy(std::string text);
    std::vector<unsigned int> getAllMatchesLazy(std::string text);
    bool check(std::string text);
};