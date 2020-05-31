#include <iostream>
#include "Parser.h"
#include "Node.h"
#include "Visitor.h"
#include "Position.h"
#include <memory>

int main()
{
    std::string regexp = R"(ab+c|(a?|x[a5-9]))";
    regexp = R"(a+|(b?(c)|d*|ef|[]gh-m]*j)k)";

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

    auto x = temp->getFirst();
    std::cout << "first: ";
    for(auto r : x) std::cout << r << " ";
    std::cout << std::endl;
    GetPositionsVisitor b;
    temp->accept(b);
    auto c = b.getPositions();
    for(auto d : c)
    {
        std::cout << "position: " << d.index << " values: ";
        for(auto e:d.values) std::cout << e << " ";
        std::cout << " follow: ";
        for(auto f:d.follow) std::cout << f << " ";
        std::cout << " negative: " << d.negative << std::endl;
    }

    return 0;
}