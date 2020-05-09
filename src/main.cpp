#include <iostream>
#include "Parser.h"

int main()
{
    std::string regexp = R"(a*b|b*c(a))";
    Parser parser(regexp);

    std::cout << (parser.Parse() ? "success" : "fail") << std::endl;

    return 0;
}