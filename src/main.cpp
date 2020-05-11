#include <iostream>
#include "Parser.h"
#include "Tree.h"

int main()
{
    std::string regexp = R"(ab+c|(a?|x))";
    Parser parser(regexp);
    parser.Parse();
    bool result = parser.getCorrect();

    if(result == false)
    {
        std::cout << "An error occured:" << std::endl;
        std::cout << parser.getErrorDesc() << std::endl;
        std::cout << "On position: " << parser.getErrorPos() << std::endl;
    }

    return 0;
}