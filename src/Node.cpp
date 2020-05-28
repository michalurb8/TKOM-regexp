#include <iostream>
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
    this->left = std::move(left);
    this->right = nullptr;
}

OptionalNode::OptionalNode(upNode down)
{
    this->left = std::move(left);
    this->right = nullptr;
}

KleeneNode::KleeneNode(upNode down)
{
    this->left = std::move(left);
    this->right = nullptr;
}

SetNode::SetNode(const std::vector<charRange>& ranges)
{
    std::cout << "values in range: ";
    for(auto elem : ranges)
    {
        for(char curr = elem.first; curr <= elem.second; ++curr)
        {
            std::cout << curr;
            chars.insert(curr);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}

NegativeSetNode::NegativeSetNode(const std::vector<charRange>& ranges)
{
    std::cout << "Values out of range: ";
    for(auto elem : ranges)
    {
        for(char curr = elem.first; curr <= elem.second; ++curr)
        {
            std::cout << curr;
            chars.insert(curr);
        }
        std::cout << " ";
    }
    std::cout << std::endl;
}