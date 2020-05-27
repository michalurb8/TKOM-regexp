#pragma once
#include <memory>
#include <vector>
#include <set>


struct Node
{
private:
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

protected:
    Node();

public:
    Node(const Node& arg) = delete;
    Node operator=(const Node& arg) = delete;
    ~Node();
};

typedef std::unique_ptr<Node> upNode;

struct SymbolNode : public Node
{
    char value;
    SymbolNode(char arg);
};

struct AltNode : public Node
{
    AltNode(upNode left, upNode right);
};

struct ConNode : public Node
{
    ConNode(upNode left, upNode right);
};

struct PlusNode : public Node
{
    PlusNode(upNode down);
};

struct OptionalNode : public Node
{
    OptionalNode(upNode down);
};

struct KleeneNode : public Node
{
    KleeneNode(upNode down);
};

struct SetNode : public Node
{
    std::set<char> chars;
    SetNode(/* jakis wektor */);
};

struct NegativeSetNode : public SetNode
{
    //to samo tylko odwrotnie 
};