#pragma once
#include <memory>
#include <vector>
#include <set>
#include "Visitor.h"

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
    bool nullable;
    std::vector<char> first;
    std::vector<char> last;
    std::vector<char> follow;
    virtual void accept(class Visitor &v) = 0;
};
typedef std::unique_ptr<Node> upNode;

struct SymbolNode : public Node
{
    void accept(class Visitor& v);
    char value;
    SymbolNode(char arg);
};

struct AltNode : public Node
{
    void accept(class Visitor& v);
    AltNode(upNode leftArg, upNode rightArg);
};

struct ConNode : public Node
{
    void accept(class Visitor& v);
    ConNode(upNode leftArg, upNode rightArg);
};

struct PlusNode : public Node
{
    void accept(class Visitor& v);
    PlusNode(upNode down);
};

struct OptionalNode : public Node
{
    void accept(class Visitor& v);
    OptionalNode(upNode down);
};

struct KleeneNode : public Node
{
    void accept(class Visitor& v);
    KleeneNode(upNode down);
};

struct SetNode : public Node
{
    void accept(class Visitor& v);
    std::set<char> chars;
    SetNode(const std::vector<charRange>& ranges);
};

struct NegativeSetNode : public Node
{
    void accept(class Visitor& v);
    std::set<char> chars;
    NegativeSetNode(const std::vector<charRange>& ranges);
};