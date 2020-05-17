#include <iostream>
#include <algorithm>
#include "Node.h"

Node::Node()
:left(nullptr), right(nullptr), parent(nullptr), value('E'), type(Node::NONE) 
{
}

Node::Node(char valueArg, nodeType typeArg)
:left(nullptr), right(nullptr), parent(nullptr), value(valueArg), type(typeArg) 
{
}

Node::Node(Node* leftArg, Node* rightArg, char valueArg, nodeType typeArg)
:left(leftArg), right(rightArg), parent(nullptr), value(valueArg), type(typeArg) 
{
    if(left) left->parent = this;
    if(right) right->parent = this;
}

Node::~Node()
{
    if(left) delete left;
    if(right) delete right;
}





NodeSet::NodeSet()
:caret(false), RBracket(false)
{
    value = 'S';
    type = Node::SET;
    for(short i = 0; i < 8; ++i) map[i] = 0;
}

void NodeSet::addChar(unsigned char arg)
{
    map[arg/16] = map[arg/16] | (1 << (15-arg%16));
}

void NodeSet::addChars(unsigned char beg, unsigned char end)
{
    for(short i = beg; i <= end; ++i)
    {
        map[i/16] = map[i/16] | (1 << (15-i%16));
    }
}





void printSet(const NodeSet* a)
{
    std::cout << "[";
    for(short i=2; i<8; ++i)
    {
        for(short j=15; j>=0; --j)
        {
            if((a->map[i] >> j)%2) std::cout << (unsigned char)(15+i*16-j);
        }
    }
    std::cout << "]" << std::endl;
}

void printNode(const Node* arg, int depth)
{
    for(int i=0; i<depth; ++i)  std::cout << "   ";

    if(arg->type == Node::SET) printSet((NodeSet*)arg);
    else std::cout << arg->value << std::endl;

    if(arg->left)
        printNode(arg->left, depth + 1);
    if(arg->right)
        printNode(arg->right, depth + 1);
}

void printTree(const Node* arg)
{
    printNode(arg, 0);
}