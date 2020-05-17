#include <iostream>
#include "Parser.h"
#include "Node.h"


int main()
{
    std::string regexp = R"(ab+c|(a?|x))";
    regexp = R"([e-\-]?)";
    Parser parser(regexp);
    Node* temp;
    try
    {
        temp = parser.Parse();
    }
    catch(const char* msg)
    {
        std::cout << msg << std::endl;
    };

    if(temp != nullptr) printTree(temp);
    delete temp;

    return 0;
}