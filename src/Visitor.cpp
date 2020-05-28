#include "Visitor.h"
#include <iostream>

void PrintVisitor::visit(struct SymbolNode* e)
{
    std::cout << "SYMBOL: " << e->value << std::endl;
}

void PrintVisitor::visit(struct AltNode *e)
{
    std::cout << "ALT" << std::endl;
}

void PrintVisitor::visit(struct ConNode *e)
{
    std::cout << "CON" << std::endl;
}

void PrintVisitor::visit(struct KleeneNode *e)
{
    std::cout << "*" << std::endl;
}

void PrintVisitor::visit(struct OptionalNode *e)
{
    std::cout << "?" << std::endl;
}

void PrintVisitor::visit(struct PlusNode *e)
{
    std::cout << "+" << std::endl;
}

void PrintVisitor::visit(struct SetNode *e)
{
    std::cout << "[]" << std::endl;
}

void PrintVisitor::visit(struct NegativeSetNode *e)
{
    std::cout << "[^]" << std::endl;
}