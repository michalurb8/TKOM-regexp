#pragma once
#include <ostream>
#include <vector>

struct Node
{
    Node* parent;
    std::vector<Node*> children;
    bool valid;
    char value;

    Node();
    Node(Node* parentArg);
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

public:
    Tree();
    Tree(Node* rootArg);
    Tree(const Tree& arg) = delete;
    Tree operator=(const Tree& arg) = delete;
    ~Tree();

    void addSon();
    Node* getRoot() const;
    bool backUp();

    friend void print(const Tree& arg);
};

void print(const Node* arg, int depth);

void print(const Tree& arg);