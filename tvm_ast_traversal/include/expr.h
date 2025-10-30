#pragma once
#include "object.h"
#include <string>

class ExprNode : public Object {
public:
    virtual ~ExprNode() = default;
};

class Expr : public ObjectRef<ExprNode> {
public:
    using ObjectRef<ExprNode>::ObjectRef;
};




class NumberExprNode : public ExprNode {
public:
  double value;
  explicit NumberExprNode(double v) : value(v) {}
};

class NumberExpr : public Expr {
public:
  explicit NumberExpr(double v) : Expr(new NumberExprNode(v)) {}
};
class BinaryExprNode : public ExprNode {
public:
  char op;
  Expr lhs;
  Expr rhs;

  BinaryExprNode(char op, Expr lhs, Expr rhs) : op(op), lhs(lhs), rhs(rhs) {}
};

class BinaryExpr : public Expr {
public:
  BinaryExpr(char op, Expr lhs, Expr rhs)
      : Expr(new BinaryExprNode(op, lhs, rhs)) {}
};
