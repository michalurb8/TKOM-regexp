#include <iostream>
#include "Parser.h"
#include "Node.h"

int main()
{
    std::string regexp = R"(ab+c|(a?|x[a5-9]))";
    regexp = R"(b+|(a?(abc)|a*|wxyz|[a-c]*ab)c)";
    Parser parser(regexp);
    Node* temp;
    try
    {
        temp = parser.Parse(); //calls new
    }
    catch(const char* msg)
    {
        std::cout << msg << std::endl;
    };

    if(temp != nullptr)
    {
        printTree(temp);
        delete temp;
    }
    return 0;
}