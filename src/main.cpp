#include "Regexp.h"
#include <memory>
#include <iostream>

int main()
{
    Regexp reg("a*c");
    reg.build();
    auto vec = reg.getAllMatchesGreedy("abcabbbcaabcaabcbacbccab");
    for(auto i : vec)
    {
        std::cout << i.first << " " << i.second << " " << i.fragment << std::endl;
    }
    return 0;
}