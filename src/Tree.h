#pragma once
#include <vector>

struct Node
{
    enum nodeType {SYMBOL, REG, ALT, CON, PAREN, INTER, INSET, SET, OP, END, CARET};

    Node* parent;
    std::vector<Node*> children;
    char value;
    nodeType type;

    Node() = delete;
    Node(char valueArg, nodeType typeArg);
    Node(const Node& arg) = delete;
    Node operator=(const Node& arg) = delete;
    ~Node();

    void setParent(Node* parentArg);
    void setKid(Node* parentArg);
};

class Tree
{
    Node* root;
    Node* current;
    Node* getRoot() const;
    bool valid;

public:
    Tree();
    Tree(const Tree& arg) = delete;
    Tree operator=(const Tree& arg) = delete;
    ~Tree();

    void createSon(char valueArg, Node::nodeType typeArg);
    bool goUp();

    void reset();
    void reduce();

    void print();
};

void printNode(const Node* arg, int depth);
bool reduceNode(Node* arg);