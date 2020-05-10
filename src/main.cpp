#include <iostream>
#include "Parser.h"
#include "Tree.h"

int main()
{
    Tree a;
    print(a);
    /*
    std::string regexp = R"(a*b|b*c(a))";
    Parser parser(regexp);
    std::cout << (parser.Parse() ? "success" : "fail") << std::endl;
    */

    return 0;
}