#include "Regexp.h"
#include "Visitor.h"
#include <iostream> //TODO delete


void Regexp::loadText(std::string text)
{
    parser.setRegExp(text);
}

Regexp::Regexp(std::string text)
:parser(text)
{
}

bool Regexp::build()
{
    states.clear();
    transitions.clear();

    std::cout << "building: " << std::endl;//TODO delete
    std::unique_ptr<Node> root;
    try
    {
        root = parser.Parse();
    }
    catch(const char* e)
    {
        std::cout << "Error: " << e << std::endl << "Error position: " << parser.getErrorPos() << std::endl;
        return false;
    }
    

    auto first = root->getFirst();

    CalcPositionsVisitor v;
    root->accept(v);
    auto positions = v.getPositions();
    unsigned int endPosition = positions.size()-1;
    std::cout << "endposition: " << endPosition << std::endl;//TODO delete
    std::cout << "endpos follow size: " << positions[endPosition].follow.size() << std::endl;//TODO delete

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
    std::cout << "states: " << std::endl;
    for(unsigned int s = 0; s < states.size(); ++s)
    {
        std::cout << "State " << s << " size " << states[s].nextPos.size() << " values: ";
        for(auto n : states[s].nextPos) std::cout << n << " ";
        std::cout << "acceptable " << states[s].acceptable << std::endl;
    }
    std::cout << "transitions: " << std::endl;
    for(auto t : transitions)
    {
        std::cout << "Transition:" << t.currentState << " " << t.input << " " << t.nextState << std::endl;
    }
    return true;
}