// ast.h
#pragma once
#include <memory>

// Simple AST with polymorphic nodes, but NO accept() method.
// We use std::shared_ptr<Expr> as the handle.

struct Expr {
  virtual ~Expr() = default;
};
using ExprPtr = std::shared_ptr<Expr>;

// Number node
struct NumberNode : Expr {
  int value;
  explicit NumberNode(int v) : value(v) {}
};

// Binary op base (lhs, rhs)
struct BinaryNode : Expr {
  ExprPtr lhs;
  ExprPtr rhs;
  BinaryNode(ExprPtr l, ExprPtr r) : lhs(std::move(l)), rhs(std::move(r)) {}
};

// Add node
struct AddNode : BinaryNode {
  AddNode(ExprPtr l, ExprPtr r) : BinaryNode(std::move(l), std::move(r)) {}
};

// Mul node
struct MulNode : BinaryNode {
  MulNode(ExprPtr l, ExprPtr r) : BinaryNode(std::move(l), std::move(r)) {}
};

// Div node
struct DivNode : BinaryNode {
  DivNode(ExprPtr l, ExprPtr r) : BinaryNode(std::move(l), std::move(r)) {}
};

// Helper constructors for convenience
inline ExprPtr MakeNumber(int v) { return std::make_shared<NumberNode>(v); }
inline ExprPtr MakeAdd(ExprPtr l, ExprPtr r) { return std::make_shared<AddNode>(std::move(l), std::move(r)); }
inline ExprPtr MakeMul(ExprPtr l, ExprPtr r) { return std::make_shared<MulNode>(std::move(l), std::move(r)); }
inline ExprPtr MakeDiv(ExprPtr l, ExprPtr r) { return std::make_shared<DivNode>(std::move(l), std::move(r)); }
