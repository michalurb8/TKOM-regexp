#include <iostream>
#include <algorithm>
#include "Node.h"

Node::Node(char valueArg, nodeType typeArg)
:value(valueArg), type(typeArg), left(nullptr), right(nullptr)
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
    std::cout << arg->value << std::endl;
    if(arg->left)
        printNode(arg->left, depth + 1);
    if(arg->right)
        printNode(arg->right, depth + 1);
}

void printTree(const Node* arg)
{
    printNode(arg, 0);
}







NodeSet::NodeSet(char valueArg, nodeType typeArg)
{

}

void NodeSet::setZero()
{
    for(short i = 0; i < 16; ++i) map[i] = 0;
}

void NodeSet::addChar(unsigned char arg)
{
    uint8_t ascii = arg;
    map[arg/16] = map[arg/16] | (1 >> arg%8);
}

void NodeSet::addChars(unsigned char beg, unsigned char end)
{

    uint8_t asciib = beg;
    uint8_t asciie = end;
}