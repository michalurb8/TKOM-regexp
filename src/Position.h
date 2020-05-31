#pragma once
#include <set>


struct Position
{
    unsigned int index;
    std::set<char> values;
    std::set<unsigned int> follow;
    bool negative;

    bool checkMatch(char arg)
    {
        if(negative)
        {
            if(values.count(arg)) return false;
            else return true;
        }
        if(values.count(arg)) return true;
        else return false;
    }
};