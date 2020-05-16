#include <iostream>
#include "Parser.h"
#include "Node.h"


int main()
{
    Node* a = new NodeSet('a', Node::PAREN);
    NodeSet* b = (NodeSet*)a;
    b->addChar('a');
    b->addChars('c', 'o');
    b->addChar('q');
    printNode(b);


    return 0;
    std::string regexp = R"(ab+c|(a?|x))";
    Parser parser(regexp);
    Node* temp;
    try
    {
        temp = parser.Parse();
    } catch(const char * msg) {
        std::cout << msg << std::endl;
    };
    bool result = parser.getCorrect();

    if(temp != nullptr) printTree(temp);

    if(result == false)
    {
        std::cout << "An error occured:" << std::endl;
        std::cout << parser.getErrorDesc() << std::endl;
        std::cout << "On position: " << parser.getErrorPos() << std::endl;
    }

    return 0;
}