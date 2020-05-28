#pragma once
#include <memory>
#include <vector>
#include <set>

struct charRange
{
    char first, second;
};



struct Node
{
protected:
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
    Node();

public:
    Node(const Node& arg) = delete;
    Node operator=(const Node& arg) = delete;
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
    SetNode(const std::vector<charRange>& ranges);
};

struct NegativeSetNode : public Node
{
    std::set<char> chars;
    NegativeSetNode(const std::vector<charRange>& ranges);
};