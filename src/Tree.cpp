#include <iostream>
#include <algorithm>
#include "Tree.h"

Node::Node(char valueArg, nodeType typeArg)
:value(valueArg), type(typeArg)
{
    children.clear();
}

Node::~Node()
{
    for(auto ch : children)
    {
        delete ch;
        ch = nullptr;
    }
    children.clear();
}

void Node::setParent(Node* parentArg)
{
    this->parent = parentArg;
}

void Node::setKid(Node* kidArg)
{
    this->children.push_back(kidArg);
}



Tree::Tree()
{
    root = new Node('*', Node::REG);
    root->setParent(root);
    current = root;
}

Tree::~Tree()
{
    delete root;
}

void Tree::createSon(char valueArg, Node::nodeType typeArg)
{
    Node* son = new Node(valueArg, typeArg);
    son->setParent(current);
    current->setKid(son);
    current = son;
}

Node* Tree::getRoot() const
{
    return root;
}

bool Tree::goUp()
{
    if(current == root)
    {
        return false;
    }
    else
    {
        current = current->parent;
        return true;
    }
}

void Tree::reset()
{
    current = root;
    for(auto ch : root->children)
    {
        delete ch;
    }
    root->children.clear();
}

void Tree::print()
{
    printNode(root, 0);
}

void Tree::reduce()
{
    current = root;
    reduceNode(root);
}



void printNode(const Node* arg, int depth)
{
    for(int i=0; i<depth; ++i)  std::cout << "   ";
    std::cout << arg->value << std::endl;
    for(auto ch : arg->children)
    {
        printNode(ch, depth + 1);
    }
}

bool reduceNode(Node* arg)
{
    if(arg->children.size() != 1)
    {
        bool repeat = false;
        do
        {
            for(auto ch : arg->children)
            {
                repeat = reduceNode(ch);
                if(repeat) break;
            }
        }
        while(repeat);
        return false;
    }
    if(arg->parent == arg)
    {
        return false;
    }
    auto position = std::find(arg->parent->children.begin(), arg->parent->children.end(), arg);
    *position = arg->children[0];

    arg->children[0]->parent = arg->parent;

    arg->children.clear();
    delete arg;
    arg = nullptr;
    return true;
}