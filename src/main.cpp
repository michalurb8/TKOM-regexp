#include "Regexp.h"
#include <iostream>

int main()
{
    Regexp reg;
    bool good = reg.build("a(a|f)*");
    if(!good) std::cout << reg.getErrorDesc();

    std::vector<Fragment> vec = reg.getAllMatchesLazy("aaaaaf");
    std::cout << "Lazy match:" << std::endl;
    for(auto i : vec)
    {
        std::cout << i.first << " " << i.second << " " << i.fragment << std::endl;
    }

    vec = reg.getAllMatchesGreedy("aaaaaf");
    std::cout << "Greedy match:" << std::endl;
    for(auto i : vec)
    {
        std::cout << i.first << " " << i.second << " " << i.fragment << std::endl;
    }

    good = reg.build("(a[ad*]|f*g)?|xx[^a-d]|b(ac)+");
    if(!good) std::cout << reg.getErrorDesc();

    std::cout << "Checking correct: " << (reg.check("a*") ? "matches" : "does not match") << std::endl;
    std::cout << "Checking incorrect: " << (reg.check("xxd") ? "matches" : "does not match") << std::endl;
    return 0;
}