#include "Regexp.h"
#include <iostream>

int main()
{
    Regexp reg;
    reg.build("[a]");
    return 0;




    bool good = reg.build("(a|f)*");
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
    reg.build("(a|f*g)?|xx|b(ac)+");
    std::cout << "Checking correct: " << (reg.check("a*") ? "matches" : "does not match") << std::endl;
    std::cout << "Checking incorrect: " << (reg.check("xxd") ? "matches" : "does not match") << std::endl;
    return 0;
}