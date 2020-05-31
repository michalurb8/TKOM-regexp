#include "Visitor.h"
#include <iostream>

void DFSPrintVisitor::visit(struct SymbolNode* e)
{
    std::cout << "SYM: " << e->value << " position: " << e->posNum;
    std::cout << " first: ";
    for(auto i : e->first) std::cout << i << " ";
    std::cout << " last: ";
    for(auto i : e->last) std::cout << i << " ";
    std::cout << " follow: ";
    for(auto i : e->follow) std::cout << i << " ";
    std::cout << std::endl;
}

void DFSPrintVisitor::visit(struct AltNode *e)
{
    std::cout << "ALT";
    std::cout << " first: ";
    for(auto i : e->first) std::cout << i << " ";
    std::cout << " last: ";
    for(auto i : e->last) std::cout << i << " ";
    std::cout << std::endl;
}

void DFSPrintVisitor::visit(struct ConNode *e)
{
    std::cout << "CON";
    std::cout << " first: ";
    for(auto i : e->first) std::cout << i << " ";
    std::cout << " last: ";
    for(auto i : e->last) std::cout << i << " ";
    std::cout << std::endl;
}

void DFSPrintVisitor::visit(struct KleeneNode *e)
{
    std::cout << "*";
    std::cout << " first: ";
    for(auto i : e->first) std::cout << i << " ";
    std::cout << " last: ";
    for(auto i : e->last) std::cout << i << " ";
    std::cout << std::endl;
}

void DFSPrintVisitor::visit(struct OptionalNode *e)
{
    std::cout << "?";
    std::cout << " first: ";
    for(auto i : e->first) std::cout << i << " ";
    std::cout << " last: ";
    for(auto i : e->last) std::cout << i << " ";
    std::cout << std::endl;
}

void DFSPrintVisitor::visit(struct PlusNode *e)
{
    std::cout << "+";
    std::cout << " first: ";
    for(auto i : e->first) std::cout << i << " ";
    std::cout << " last: ";
    for(auto i : e->last) std::cout << i << " ";
    std::cout << std::endl;
}

void DFSPrintVisitor::visit(struct SetNode *e)
{
    std::cout << "[]" << " position: " << e->posNum;
    std::cout << " first: ";
    for(auto i : e->first) std::cout << i << " ";
    std::cout << " last: ";
    for(auto i : e->last) std::cout << i << " ";
    std::cout << " follow: ";
    for(auto i : e->follow) std::cout << i << " ";
    std::cout << std::endl;
}

void DFSPrintVisitor::visit(struct NegativeSetNode *e)
{
    std::cout << "[^]" << " position: " << e->posNum;
    std::cout << " first: ";
    for(auto i : e->first) std::cout << i << " ";
    std::cout << " last: ";
    for(auto i : e->last) std::cout << i << " ";
    std::cout << " follow: ";
    for(auto i : e->follow) std::cout << i << " ";
    std::cout << std::endl;
}





void GetPositionsVisitor::visit(struct SymbolNode* e)
{
    std::set<char> values;
    values.insert(e->value);
    positions.push_back({e->posNum, values, e->follow, false});
}

void GetPositionsVisitor::visit(struct AltNode *e)
{
    e->left->follow = e->follow;    
    e->right->follow = e->follow;    
}

void GetPositionsVisitor::visit(struct ConNode *e)
{
    if(e->right->nullable)
    {
        e->left->follow = e->right->first;
        for(auto i : e->follow) e->left->follow.insert(i);
    }
    else
    {
        e->left->follow = e->right->first;
    }
    e->right->follow = e->follow;    
}

void GetPositionsVisitor::visit(struct KleeneNode *e)
{
    e->left->follow = e->follow;
    for(auto i : e->left->first) e->left->follow.insert(i);
}

void GetPositionsVisitor::visit(struct OptionalNode *e)
{
    e->left->follow = e->follow;
}

void GetPositionsVisitor::visit(struct PlusNode *e)
{
    e->left->follow = e->follow;
    for(auto i : e->left->first) e->left->follow.insert(i);
}

void GetPositionsVisitor::visit(struct SetNode *e)
{
    positions.push_back({e->posNum, e->chars, e->follow, false});
}

void GetPositionsVisitor::visit(struct NegativeSetNode *e)
{
    positions.push_back({e->posNum, e->chars, e->follow, true});
}





std::vector<Position> GetPositionsVisitor::getPositions()
{
    return positions;
}