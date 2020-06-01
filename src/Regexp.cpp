#include "Regexp.h"
#include "Visitor.h"

Regexp::Regexp()
:currState(0), valid(false)
{
}

std::string Regexp::getErrorDesc()
{
    if(errorDesc == "") return "No errors";
    return errorDesc;
}

bool Regexp::build(std::string text)
{
    parser = Parser(text);
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
    valid = true;
    return true;
}

bool Regexp::step(char arg)
{
    if(valid == false) return false;
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

std::vector<Fragment> Regexp::getAllMatchesLazy(std::string text)
{
    std::vector<Fragment> result;
    if(valid == false) return result;
    unsigned int len = text.length();
    for(unsigned int ind = 0; ind < len; ++ind)
    {
        currState = 0;
        if(acceptable())
        {
            result.push_back({ind, ind, ""});
        }
        else
        {
            for(unsigned int inner = ind; inner < len; ++inner)
            {
                if(!step(text[inner])) break;
                if(acceptable())
                {
                    result.push_back({ind, inner+1, text.substr(ind, inner-ind+1)});
                    break;
                }
            }
        }
    }
    return result;
}

std::vector<Fragment> Regexp::getAllMatchesGreedy(std::string text)
{
    std::vector<Fragment> result;
    if(valid == false) return result;
    unsigned int len = text.length();
    for(unsigned int ind = 0; ind < len; ++ind)
    {
        currState = 0;
        unsigned int candidate;
        bool matched = false;
        if(acceptable())
        {
            candidate = ind;
            matched = true;
        }
        for(unsigned int inner = ind; inner < len; ++inner)
        {
            if(!step(text[inner])) break;
            if(acceptable())
            {
                candidate = inner + 1;
                matched = true;
            }
        }
        if(matched) result.push_back({ind, candidate, text.substr(ind, candidate-ind)});
    }
    return result;
}

bool Regexp::acceptable()
{
    if(valid == false) return false;
    return states[currState].acceptable;
}

bool Regexp::check(std::string text)
{
    if(valid == false) return false;
    currState = 0;
    for(char a : text)
    {
        if(!step(a)) return false;
    }
    return acceptable();
}