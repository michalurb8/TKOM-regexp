#include <algorithm>
#include "Node.h"

Node::Node()
{
    
}

SymbolNode::SymbolNode(char arg)
{
    value = arg;
}

AltNode::AltNode(upNode left, upNode right)
{
    this->left = std::move(left);
    this->right = std::move(right);
}

ConNode::ConNode(upNode left, upNode right)
{
    this->left = std::move(left);
    this->right = std::move(right);
}

PlusNode::PlusNode(upNode down)
{
    this->left = std::move(down);
    this->right = nullptr;
}

OptionalNode::OptionalNode(upNode down)
{
    this->left = std::move(down);
    this->right = nullptr;
}

KleeneNode::KleeneNode(upNode down)
{
    this->left = std::move(down);
    this->right = nullptr;
}

SetNode::SetNode(const std::vector<charRange>& ranges)
{
    for(auto elem : ranges)
    {
        for(char curr = elem.first; curr <= elem.second; ++curr)
        {
            chars.insert(curr);
        }
    }
}

NegativeSetNode::NegativeSetNode(const std::vector<charRange>& ranges)
{
    for(auto elem : ranges)
    {
        for(char curr = elem.first; curr <= elem.second; ++curr)
        {
            chars.insert(curr);
        }
    }
}








//all derived classes must accept the visitor:
void SymbolNode::accept(Visitor& v)
{
    v.visit(this);
}

void AltNode::accept(Visitor& v)
{
    v.visit(this);
    if(left) left->accept(v);
    if(right) right->accept(v);
}

void ConNode::accept(Visitor& v)
{
    v.visit(this);
    if(left) left->accept(v);
    if(right) right->accept(v);
}

void KleeneNode::accept(Visitor& v)
{
    if(left) left->accept(v);
    v.visit(this);
}

void OptionalNode::accept(Visitor& v)
{
    if(left) left->accept(v);
    v.visit(this);
}

void PlusNode::accept(Visitor& v)
{
    if(left) left->accept(v);
    v.visit(this);
}

void SetNode::accept(Visitor& v)
{
    v.visit(this);
}

void NegativeSetNode::accept(Visitor& v)
{
    v.visit(this);
}