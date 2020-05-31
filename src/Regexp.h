#pragma once

#include <string>
#include <vector>
#include <set>

#include "Parser.h"

struct Fragment
{
    unsigned int first, second;
    std::string fragment;
};

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
    Regexp();
    bool build(std::string);
    std::string getErrorDesc();

    bool check(std::string text);
    std::vector<Fragment> getAllMatchesGreedy(std::string text);
    std::vector<Fragment> getAllMatchesLazy(std::string text);
};