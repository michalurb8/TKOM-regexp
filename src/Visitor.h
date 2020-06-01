#pragma once
#include "Node.h"

struct Position
{
    unsigned int index;
    std::set<char> values;
    std::set<unsigned int> follow;
    bool negative;

    bool checkMatch(char arg)
    {
        if(negative)
        {
            if(values.count(arg)) return false;
            else return true;
        }
        if(values.count(arg)) return true;
        else return false;
    }
};

class Visitor //A visitor class for traversing Node tree structure
{
public:
    virtual void visit(struct SymbolNode* e) = 0;

    virtual void visit(struct AltNode *e) = 0;
    virtual void visit(struct ConNode *e) = 0;

    virtual void visit(struct KleeneNode *e) = 0;
    virtual void visit(struct OptionalNode *e) = 0;
    virtual void visit(struct PlusNode *e) = 0;

    virtual void visit(struct SetNode *e) = 0;
    virtual void visit(struct NegativeSetNode *e) = 0;
};


class DFSPrintVisitor : public Visitor //A visitor for printing tree contents
{
    void visit(struct SymbolNode* e);

    void visit(struct AltNode *e);
    void visit(struct ConNode *e);

    void visit(struct KleeneNode *e);
    void visit(struct OptionalNode *e);
    void visit(struct PlusNode *e);

    void visit(struct SetNode *e);
    void visit(struct NegativeSetNode *e);
};

class CalcPositionsVisitor : public Visitor //A visitor setting "follow", constructing a position vector
{
    std::vector<Position> positions;
    void visit(struct SymbolNode* e);

    void visit(struct AltNode *e);
    void visit(struct ConNode *e);

    void visit(struct KleeneNode *e);
    void visit(struct OptionalNode *e);
    void visit(struct PlusNode *e);

    void visit(struct SetNode *e);
    void visit(struct NegativeSetNode *e);
public:
    std::vector<Position> getPositions();
};