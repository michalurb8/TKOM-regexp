#include "Regexp.h"
#include "Visitor.h"
#include <iostream>

Regexp::Regexp(std::string text)
:parser(text), currState(0), accepted(false)
{
}

void Regexp::loadText(std::string text)
{
    parser.setRegExp(text);
}

std::string Regexp::getErrorDesc()
{
    return errorDesc;
}

bool Regexp::build()
{
    states.clear();
    transitions.clear();

    std::unique_ptr<Node> root;
    try
    {
        root = parser.Parse();
    }
    catch(const char* e)
    {
        errorDesc =  "Error: " + std::string(e) + '\n';
        errorDesc += "Error position: " + std::to_string(parser.getErrorPos()) + '\n';
        return false;
    }
    
    auto first = root->getFirst();

    CalcPositionsVisitor v;
    root->accept(v);
    auto positions = v.getPositions();
    unsigned int endPosition = positions.size()-1;

    bool isFirstAcceptable = first.count(endPosition);
    states.push_back({first, isFirstAcceptable});

    for(unsigned int stateInd = 0; stateInd < states.size(); ++stateInd) //for every state
    {
        for(char ch =' '; ch <= '~'; ++ch) //check for every printable character 32 - 126
        {
            std::set<unsigned int> newState;
            bool addState = false;
            for(auto posInd : states[stateInd].nextPos)
            {
                if(positions[posInd].checkMatch(ch) == true)
                {
                    addState = true;
                    for(auto followElem : positions[posInd].follow)
                    {
                        newState.insert(followElem);
                    }
                }
            }
            if(!addState) continue;
            unsigned int nextState = 0;
            for(unsigned int ind = 0; ind < states.size(); ++ind)
            {
                if(states[ind].nextPos == newState)
                {
                    nextState = ind;
                    addState = false;
                    break;
                }
            }
            if(addState)
            {
                states.push_back({newState, newState.count(endPosition)});
                nextState = states.size()-1;
            }
            transitions.push_back({stateInd, ch, nextState});
        }
    }
    return true;
}

bool Regexp::step(char arg)
{
    for(auto t : transitions)
    {
        if(t.currentState == this->currState && t.input == arg)
        {
            this->currState = t.nextState;
            return true;
        }
    }
    return false;
}

std::vector<unsigned int> Regexp::getAllMatchesGreedy(std::string text)
{
    unsigned int len = text.length();
    std::vector<unsigned int> result;
    for(unsigned int ind = 0; ind < len; ++ind)
    {
        currState = 0;
        unsigned int candidate;
        bool matched = false;
        for(unsigned int inner = ind; inner < len; ++inner)
        {
            if(!step(text[inner])) break;
            if(acceptable())
            {
                candidate = ind;
                matched = true;
            }
        }
        if(matched) result.push_back(candidate);
    }
    return result;
}

bool Regexp::acceptable()
{
    return states[currState].acceptable;
}

bool Regexp::check(std::string text)
{
    currState = 0;
    for(char a : text)
    {
        if(!step(a)) return false;
    }
    return acceptable();
}