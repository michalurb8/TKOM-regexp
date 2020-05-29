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






void SetFollowVisitor::visit(struct SymbolNode* e)
{
    std::cout << "currently in " << e->value << " : ";
    for(auto i : e->follow) std::cout << i << " ";
    std::cout << std::endl;
}

void SetFollowVisitor::visit(struct AltNode *e)
{
    e->left->follow = e->follow;    
    e->right->follow = e->follow;    
}

void SetFollowVisitor::visit(struct ConNode *e)
{
    if(e->right->nullable)
    {
        e->left->follow = e->right->first;
        for(auto i : e->follow) e->left->follow.push_back(i);
    }
    else
    {
        e->left->follow = e->right->first;
    }
    e->right->follow = e->follow;    
}

void SetFollowVisitor::visit(struct KleeneNode *e)
{
    e->left->follow = e->follow;
    for(auto i : e->left->first) e->left->follow.push_back(i);
}

void SetFollowVisitor::visit(struct OptionalNode *e)
{
    e->left->follow = e->follow;
}

void SetFollowVisitor::visit(struct PlusNode *e)
{
    e->left->follow = e->follow;
    for(auto i : e->left->first) e->left->follow.push_back(i);
}

void SetFollowVisitor::visit(struct SetNode *e)
{
}

void SetFollowVisitor::visit(struct NegativeSetNode *e)
{
}