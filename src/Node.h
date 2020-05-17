#pragma once
#include <vector>

struct Node
{
protected:
    Node* left;
    Node* right;
    Node* parent;
    Node();
public:
    enum nodeType {SYMBOL, NONE, ALT, CON, PAREN, INTER, INSET, SET, KLEENE, OPTIONAL, PLUS, END, CARET};

    char value;
    nodeType type;

    Node(char valueArg, nodeType typeArg);
    Node(Node* left, Node* right, char valueArg, nodeType typeArg);
    Node(const Node& arg) = delete;
    Node operator=(const Node& arg) = delete;
    ~Node();

friend void printNode(const Node* arg, int depth);

};

struct NodeSet : public Node
{
    uint16_t map[8];
    NodeSet(char valueArg, nodeType typeArg);
    void addChar(unsigned char arg);
    void addChars(unsigned char beg, unsigned  char end);
};

void printNode(const Node* arg, int depth);
void printNode(const NodeSet* a);
void printTree(const Node* arg);