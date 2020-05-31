#pragma once
#include <memory>
#include <set>
#include <vector>
#include "Visitor.h"

struct charRange
{
    char first, second;
};



struct Node
{
protected:
    Node();

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    bool nullable;
    std::set<unsigned int> first;
    std::set<unsigned int> last;
    std::set<unsigned int> follow;

    static unsigned int nextPos;
public:
    static void reset();

    virtual void accept(class Visitor &v) = 0;

    std::set<unsigned int> getFirst();

    friend class GetPositionsVisitor;
    friend class DFSPrintVisitor;

    friend class AltNode;
    friend class ConNode;
    friend class KleeneNode;
    friend class OptionalNode;
    friend class PlusNode;
};
typedef std::unique_ptr<Node> upNode;

struct SymbolNode : public Node
{
    unsigned int posNum;
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
    unsigned int posNum;
    void accept(class Visitor& v);
    std::set<char> chars;
    SetNode(const std::vector<charRange>& ranges);
};

struct NegativeSetNode : public Node
{
    unsigned int posNum;
    void accept(class Visitor& v);
    std::set<char> chars;
    NegativeSetNode(const std::vector<charRange>& ranges);
};