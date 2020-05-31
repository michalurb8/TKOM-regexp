#include <algorithm>
#include "Node.h"

unsigned int Node::nextPos;

Node::Node()
{
}

SymbolNode::SymbolNode(char arg)
{
    posNum = Node::nextPos++;
    value = arg;
    //set nullable
    nullable = false;
    //set first
    this->first.insert(posNum);
    //set last
    this->last.insert(posNum);
}

AltNode::AltNode(upNode leftArg, upNode rightArg)
{
    this->left = std::move(leftArg);
    this->right = std::move(rightArg);
    //set nullable
    if(left->nullable || right->nullable) nullable = true;
    else nullable = false;
    //set first
    for(auto i : left->first) this->first.insert(i);
    for(auto i : right->first) this->first.insert(i);
    //set last
    for(auto i : left->last) this->last.insert(i);
    for(auto i : right->last) this->last.insert(i);
}

ConNode::ConNode(upNode leftArg, upNode rightArg)
{
    this->left = std::move(leftArg);
    this->right = std::move(rightArg);
    //set nullable
    if(left->nullable && right->nullable) nullable = true;
    else nullable = false;
    //set first
    if(left->nullable)
    {
        for(auto i : left->first) this->first.insert(i);
        for(auto i : right->first) this->first.insert(i);
    }
    else this->first = left->first;
    //set last
    if(right->nullable)
    {
        for(auto i : left->last) this->last.insert(i);
        for(auto i : right->last) this->last.insert(i);
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
    posNum = Node::nextPos++;
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
    this->first.insert(posNum);
    //set last
    this->last.insert(posNum);
}

NegativeSetNode::NegativeSetNode(const std::vector<charRange>& ranges)
{
    posNum = Node::nextPos++;
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
    this->first.insert(posNum);
    //set last
    this->last.insert(posNum);
}

void Node::reset()
{
    nextPos = 0;
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
    v.visit(this);
    if(left) left->accept(v);
}

void OptionalNode::accept(Visitor& v)
{
    v.visit(this);
    if(left) left->accept(v);
}

void PlusNode::accept(Visitor& v)
{
    v.visit(this);
    if(left) left->accept(v);
}

void SetNode::accept(Visitor& v)
{
    v.visit(this);
}

void NegativeSetNode::accept(Visitor& v)
{
    v.visit(this);
}





std::set<unsigned int> Node::getFirst()
{
    return first;
}