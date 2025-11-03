#pragma once
#include <memory>
#include <string>
#include <vector>

//------------------------------------
// Expr Base
//------------------------------------
struct Expr {
    virtual ~Expr() = default;
};
using ExprPtr = std::shared_ptr<Expr>;

// Number
struct NumberNode : Expr {
    double value;
    explicit NumberNode(double v) : value(v) {}
};

// Variable
struct VarNode : Expr {
    std::string name;
    explicit VarNode(std::string n) : name(std::move(n)) {}
};

// Binary base
struct BinaryNode : Expr {
    ExprPtr lhs, rhs;
    BinaryNode(ExprPtr l, ExprPtr r) : lhs(std::move(l)), rhs(std::move(r)) {}
};

// Operators
struct AddNode : BinaryNode { using BinaryNode::BinaryNode; };
struct SubNode : BinaryNode { using BinaryNode::BinaryNode; };
struct MulNode : BinaryNode { using BinaryNode::BinaryNode; };
struct DivNode : BinaryNode { using BinaryNode::BinaryNode; };

//------------------------------------
// Stmt Base
//------------------------------------
struct Stmt {
    virtual ~Stmt() = default;
};
using StmtPtr = std::shared_ptr<Stmt>;

// Expression statement:  e;
struct ExprStmtNode : Stmt {
    ExprPtr expr;
    explicit ExprStmtNode(ExprPtr e) : expr(std::move(e)) {}
};

// Assignment: x = expr;
struct AssignStmtNode : Stmt {
    std::string name;
    ExprPtr expr;
    AssignStmtNode(std::string n, ExprPtr e)
        : name(std::move(n)), expr(std::move(e)) {}
};

//------------------------------------
// Helpers
//------------------------------------
inline ExprPtr Number(double v) { return std::make_shared<NumberNode>(v); }
inline ExprPtr Var(const std::string& n) { return std::make_shared<VarNode>(n); }

inline ExprPtr Add(ExprPtr a, ExprPtr b) { return std::make_shared<AddNode>(a, b); }
inline ExprPtr Sub(ExprPtr a, ExprPtr b) { return std::make_shared<SubNode>(a, b); }
inline ExprPtr Mul(ExprPtr a, ExprPtr b) { return std::make_shared<MulNode>(a, b); }
inline ExprPtr Div(ExprPtr a, ExprPtr b) { return std::make_shared<DivNode>(a, b); }

inline StmtPtr ExprStmt(ExprPtr e) { return std::make_shared<ExprStmtNode>(e); }
inline StmtPtr Assign(const std::string& n, ExprPtr e) {
    return std::make_shared<AssignStmtNode>(n, e);
}
