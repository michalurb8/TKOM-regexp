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
        return (values.count(arg) != negative);
    }
};