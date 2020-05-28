#include <iostream>
#include "Parser.h"
#include "Node.h"
#include "Visitor.h"
#include <memory>

int main()
{
    std::string regexp = R"(ab+c|(a?|x[a5-9]))";
    regexp = R"(b+|(a?(c)|a*|wz|[^]za-c]*b)c)";

    Parser parser(regexp);
    std::unique_ptr<Node> temp;
    try
    {
        temp = parser.Parse();
    }
    catch(const char* msg)
    {
        std::cout << "ERROR: " << msg << std::endl;
        std::cout << "on pos: " << parser.getErrorPos() << std::endl;
    };

    PrintVisitor a;
    temp->accept(a);

    return 0;
}