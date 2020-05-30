#pragma once
#include "Node.h"

class Visitor
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


class DFSPrintVisitor : public Visitor
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

class SetFollowVisitor : public Visitor
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