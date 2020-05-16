#pragma once
#include <vector>

struct Node
{
    enum nodeType {SYMBOL, REG, ALT, CON, PAREN, INTER, INSET, SET, KLEENE, OPTIONAL, PLUS, END, CARET};

    Node* parent;
    Node* left;
    Node* right;

    char value;
    nodeType type;

    Node() = delete;
    Node(char valueArg, nodeType typeArg);
    Node(Node* left, Node* right, char valueArg, nodeType typeArg);
    Node(const Node& arg) = delete;
    Node operator=(const Node& arg) = delete;
    ~Node();

    //void setParent(Node* parentArg);
    //void setLeft(Node* leftArg);
    //void setRight(Node* rightArg);
};

void printNode(const Node* arg, int depth);
void printTree(const Node* arg);




struct NodeSet : public Node
{
    uint8_t map[16];
    void addChar(unsigned char arg);
    void addChars(unsigned char beg, unsigned  char end);
    void setZero();
    NodeSet(char valueArg, nodeType typeArg);
};