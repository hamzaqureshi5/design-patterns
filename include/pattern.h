
#include <iostream>
#include <string>
#include <memory>

// Forward declarations
class NumberExpr;
class AddExpr;
class MulExpr;

// --------------------------------------------
// Visitor Interface
// --------------------------------------------
class ExprVisitor {
public:
    virtual void visit(NumberExpr* e) = 0;
    virtual void visit(AddExpr* e) = 0;
    virtual void visit(MulExpr* e) = 0;
    virtual ~ExprVisitor() = default;
};

// --------------------------------------------
// Base Expression Node
// --------------------------------------------
class Expr {
public:
    virtual void accept(ExprVisitor* v) = 0;
    virtual ~Expr() = default;
};

// --------------------------------------------
// Concrete Expression Nodes
// --------------------------------------------
class NumberExpr : public Expr {
public:
    int value;
    NumberExpr(int v) : value(v) {}
    void accept(ExprVisitor* v) override { v->visit(this); }
};

class AddExpr : public Expr {
public:
    std::unique_ptr<Expr> lhs, rhs;
    AddExpr(Expr* l, Expr* r) : lhs(l), rhs(r) {}
    void accept(ExprVisitor* v) override { v->visit(this); }
};

class MulExpr : public Expr {
public:
    std::unique_ptr<Expr> lhs, rhs;
    MulExpr(Expr* l, Expr* r) : lhs(l), rhs(r) {}
    void accept(ExprVisitor* v) override { v->visit(this); }
};

// --------------------------------------------
// Concrete Visitor 1 — Evaluator
// --------------------------------------------
class EvalVisitor : public ExprVisitor {
public:
    int result = 0;

    void visit(NumberExpr* e) override {
        result = e->value;
    }

    void visit(AddExpr* e) override {
        EvalVisitor leftEval, rightEval;
        e->lhs->accept(&leftEval);
        e->rhs->accept(&rightEval);
        result = leftEval.result + rightEval.result;
    }

    void visit(MulExpr* e) override {
        EvalVisitor leftEval, rightEval;
        e->lhs->accept(&leftEval);
        e->rhs->accept(&rightEval);
        result = leftEval.result * rightEval.result;
    }
};

// --------------------------------------------
// Concrete Visitor 2 — Pretty Printer
// --------------------------------------------
class PrintVisitor : public ExprVisitor {
public:
    std::string result;

    void visit(NumberExpr* e) override {
        result = std::to_string(e->value);
    }

    void visit(AddExpr* e) override {
        PrintVisitor leftPrint, rightPrint;
        e->lhs->accept(&leftPrint);
        e->rhs->accept(&rightPrint);
        result = "(" + leftPrint.result + " + " + rightPrint.result + ")";
    }

    void visit(MulExpr* e) override {
        PrintVisitor leftPrint, rightPrint;
        e->lhs->accept(&leftPrint);
        e->rhs->accept(&rightPrint);
        result = "(" + leftPrint.result + " * " + rightPrint.result + ")";
    }
};

