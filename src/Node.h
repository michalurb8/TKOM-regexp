#pragma once
#include <vector>

struct Node
{
    enum nodeType {SYMBOL, NONE, ALT, CON, PAREN, INTER, INSET, SET, KLEENE, OPTIONAL, PLUS, END, CARET};

    char value;
    nodeType type;

    Node* left;
    Node* right;
    Node* parent;

    Node(char valueArg, nodeType typeArg);
    Node(Node* left, Node* right, char valueArg, nodeType typeArg);
    Node(const Node& arg) = delete;
    Node operator=(const Node& arg) = delete;
    ~Node();

protected:
    Node();
};

struct NodeSet : public Node
{
    NodeSet(char valueArg, nodeType typeArg);
    uint16_t map[8];
    void addChar(unsigned char arg);
    void addChars(unsigned char beg, unsigned  char end);
};

void printNode(const Node* arg, int depth);
void printNode(const NodeSet* a);
void printTree(const Node* arg);