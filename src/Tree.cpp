#include <iostream>
#include "Tree.h"

Node::Node()
:parent(nullptr), valid(false), value(0)
{
    children.clear();
}

Node::Node(Node* parentArg)
:parent(parentArg), valid(false), value(0)
{
    children.clear();
}

Node::~Node()
{
    for(auto ch : children)
    {
        std::cout << "deleting all children of " << this->value << ": " << ch->value << std::endl;
        delete ch;
    }
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
    root = new Node();
    root->setParent(root);
    current = root;
    root->value = 'a';
}

Tree::~Tree()
{
    std::cout << "deleting root" << std::endl;
    delete root;
}

void Tree::addSon()
{
    Node* son = new Node();
    son->setParent(current);
    current->setKid(son);
    son->value = current->value + 1;
    current = son;
}

Node* Tree::getRoot() const
{
    return root;
}

bool Tree::backUp()
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






void print(const Node* arg, int depth)
{
    for(int i=0; i<depth; ++i)
    std::cout << " ";
    std::cout << arg->value << std::endl;
    for(auto ch : arg->children)
    {
        print(ch, depth + 1);
    }
}

void print(const Tree& arg)
{
    print(arg.getRoot(), 0);
}