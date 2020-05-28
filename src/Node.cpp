#include <algorithm>
#include "Node.h"

Node::Node()
{
}

SymbolNode::SymbolNode(char arg)
{
    value = arg;
    //set nullable, first, last:
    nullable = false;
    first.push_back(arg);
    last.push_back(arg);
}

AltNode::AltNode(upNode leftArg, upNode rightArg)
{
    this->left = std::move(leftArg);
    this->right = std::move(rightArg);
    //set nullable
    if(left->nullable)
    if(left->nullable || right->nullable) nullable = true;
    //set first
    for(auto i : left->first) this->first.push_back(i);
    for(auto i : right->first) this->first.push_back(i);
    //set last
    for(auto i : left->last) this->last.push_back(i);
    for(auto i : right->last) this->last.push_back(i);
}

ConNode::ConNode(upNode leftArg, upNode rightArg)
{
    this->left = std::move(leftArg);
    this->right = std::move(rightArg);
    //set nullable
    if(left->nullable && right->nullable) nullable = true;
    //set first
    if(left->nullable)
    {
        for(auto i : left->first) this->first.push_back(i);
        for(auto i : right->first) this->first.push_back(i);
    }
    else this->first = left->first;
    //set last
    if(right->nullable)
    {
        for(auto i : left->last) this->last.push_back(i);
        for(auto i : right->last) this->last.push_back(i);
    }
    else this->last = right->last;
}

PlusNode::PlusNode(upNode down)
{
    this->left = std::move(down);
    this->right = nullptr;
    //set nullable
    this->nullable = false;
    //set first
    this->first = left->first;
    //set last
    this->last = left->last;
}

OptionalNode::OptionalNode(upNode down)
{
    this->left = std::move(down);
    this->right = nullptr;
    //set nullable
    this->nullable = true;
    //set first
    this->first = left->first;
    //set last
    this->last = left->last;
}

KleeneNode::KleeneNode(upNode down)
{
    this->left = std::move(down);
    this->right = nullptr;
    //set nullable
    this->nullable = true;
    //set first
    this->first = left->first;
    //set last
    this->last = left->last;
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
    //set nullable
    this->nullable = false;
    //set first
    for(auto i : chars) this->first.push_back(i);
    //set last
    this->last = this->first;
}

NegativeSetNode::NegativeSetNode(const std::vector<charRange>& ranges)
{
    throw "not yet pls";
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