#include <iostream>
#include <algorithm>
#include <cstring>
#include "Node.h"

Node::Node()
:value(0x03), type(Node::NONE), left(nullptr), right(nullptr), parent(nullptr)
{
}

Node::Node(char valueArg, nodeType typeArg)
:value(valueArg), type(typeArg), left(nullptr), right(nullptr), parent(nullptr)
{
}

Node::Node(Node* leftArg, Node* rightArg, char valueArg, nodeType typeArg)
:value(valueArg), type(typeArg), left(leftArg), right(rightArg)
{
    if(left) left->parent = this;
    if(right) right->parent = this;
}

Node::~Node()
{
    if(left) delete left;
    if(right) delete right;
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




NodeSet::NodeSet()
:caret(false), RBracket(false)
{
    value = 'S';
    type = Node::SET;
    for(short i = 0; i < 8; ++i) map[i] = 0;
}

void NodeSet::addChar(unsigned char arg)
{
    uint8_t ascii = arg;
    map[arg/16] = map[arg/16] | (1 << (15-arg%16));
}

void NodeSet::addChars(unsigned char beg, unsigned char end)
{
    uint8_t asciib = beg;
    uint8_t asciie = end;
    for(short i = asciib; i <= asciie; ++i)
    {
        map[i/16] = map[i/16] | (1 << (15-i%16));
    }
}

void printSet(const NodeSet* a)
{
    for(short i=0; i<8; ++i)
    {
        for(short j=15; j>=0; --j)
        {
            std::cout << (a->map[i] >> j)%2;
        }
        std::cout << std::endl;
    }
}