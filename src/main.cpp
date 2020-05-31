#include "Regexp.h"
#include <memory>
#include <iostream>

int main()
{
    Regexp reg("a*bc");
    reg.build();
    auto vec = reg.getAllMatchesGreedy("abcabbbcaabcaabcbacbccab");
    for(auto i : vec)
    {
        std::cout << i << std::endl;
    }
    return 0;
}