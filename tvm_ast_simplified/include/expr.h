// // ast.h
// #pragma once
// #include <memory>
// #include <string>
// #include <vector>

// // -----------------------------
// // Expr (Arithmetic-only)
// // -----------------------------
// struct Expr {
//     virtual ~Expr() = default;
// };
// using ExprPtr = std::shared_ptr<Expr>;

// // Number literal
// struct NumberNode : Expr {
//     double value;
//     explicit NumberNode(double v) : value(v) {}
// };

// // Variable reference
// struct VarNode : Expr {
//     std::string name;
//     explicit VarNode(std::string n) : name(std::move(n)) {}
// };

// // Binary operation base
// struct BinaryNode : Expr {
//     ExprPtr lhs;
//     ExprPtr rhs;
//     BinaryNode(ExprPtr l, ExprPtr r) : lhs(std::move(l)), rhs(std::move(r)) {}
// };

// // Add
// struct AddNode : BinaryNode {
//     AddNode(ExprPtr l, ExprPtr r) : BinaryNode(std::move(l), std::move(r)) {}
// };

// // Sub
// struct SubNode : BinaryNode {
//     SubNode(ExprPtr l, ExprPtr r) : BinaryNode(std::move(l), std::move(r)) {}
// };

// // Mul
// struct MulNode : BinaryNode {
//     MulNode(ExprPtr l, ExprPtr r) : BinaryNode(std::move(l), std::move(r)) {}
// };

// // Div
// struct DivNode : BinaryNode {
//     DivNode(ExprPtr l, ExprPtr r) : BinaryNode(std::move(l), std::move(r)) {}
// };

// // Helper constructors for expressions
// inline ExprPtr Num(double v) { return std::make_shared<NumberNode>(v); }
// inline ExprPtr Var(const std::string& name) { return std::make_shared<VarNode>(name); }
// inline ExprPtr Add(ExprPtr a, ExprPtr b) { return std::make_shared<AddNode>(a, b); }
// inline ExprPtr Sub(ExprPtr a, ExprPtr b) { return std::make_shared<SubNode>(a, b); }
// inline ExprPtr Mul(ExprPtr a, ExprPtr b) { return std::make_shared<MulNode>(a, b); }
// inline ExprPtr Div(ExprPtr a, ExprPtr b) { return std::make_shared<DivNode>(a, b); }

// // -----------------------------
// // Stmt (Imperative constructs)
// // -----------------------------
// struct Stmt {
//     virtual ~Stmt() = default;
// };
// using StmtPtr = std::shared_ptr<Stmt>;

// // Expression statement: evaluate an expression, discard result (but may have side-effects in extensions)
// struct ExprStmtNode : Stmt {
//     ExprPtr expr;
//     explicit ExprStmtNode(ExprPtr e) : expr(std::move(e)) {}
// };

// // Assignment: var = expr
// struct AssignNode : Stmt {
//     std::string var;
//     ExprPtr value;
//     AssignNode(std::string v, ExprPtr val) : var(std::move(v)), value(std::move(val)) {}
// };

// // Let statement (introduce a new variable binding for the body): let var = value in body
// struct LetStmtNode : Stmt {
//     std::string var;
//     ExprPtr value;
//     StmtPtr body;
//     LetStmtNode(std::string v, ExprPtr val, StmtPtr b)
//         : var(std::move(v)), value(std::move(val)), body(std::move(b)) {}
// };

// // Sequence (block) of statements
// struct SeqNode : Stmt {
//     std::vector<StmtPtr> stmts;
//     explicit SeqNode(std::vector<StmtPtr> s) : stmts(std::move(s)) {}
// };

// // If statement (no else = empty)
// struct IfNode : Stmt {
//     ExprPtr cond;
//     StmtPtr then_case;
//     StmtPtr else_case; // can be null
//     IfNode(ExprPtr c, StmtPtr t, StmtPtr e = nullptr)
//         : cond(std::move(c)), then_case(std::move(t)), else_case(std::move(e)) {}
// };

// // For loop: for var = begin; var < end; ++var { body }
// struct ForNode : Stmt {
//     std::string var;
//     ExprPtr begin;
//     ExprPtr end;
//     StmtPtr body;
//     ForNode(std::string v, ExprPtr b, ExprPtr e, StmtPtr bd)
//         : var(std::move(v)), begin(std::move(b)), end(std::move(e)), body(std::move(bd)) {}
// };

// // Helper constructors for statements
// inline StmtPtr MakeExprStmt(ExprPtr e) { return std::make_shared<ExprStmtNode>(e); }
// inline StmtPtr MakeAssign(const std::string& v, ExprPtr e) { return std::make_shared<AssignNode>(v, e); }
// inline StmtPtr MakeLet(const std::string& v, ExprPtr e, StmtPtr body) { return std::make_shared<LetStmtNode>(v, e, body); }
// inline StmtPtr MakeSeq(std::vector<StmtPtr> s) { return std::make_shared<SeqNode>(std::move(s)); }
// inline StmtPtr MakeIf(ExprPtr c, StmtPtr t, StmtPtr e = nullptr) { return std::make_shared<IfNode>(c, t, e); }
// inline StmtPtr MakeFor(const std::string& v, ExprPtr b, ExprPtr e, StmtPtr body) { return std::make_shared<ForNode>(v, b, e, body); }
#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "object.h"
// ====== Expr Base ======
struct BaseExprNode : Object {
  virtual void print() const = 0;
  virtual double eval(std::unordered_map<std::string, double> &env) const = 0;
};

struct Expr : ObjectRef {
  Expr() = default;
  explicit Expr(ObjectPtr<BaseExprNode> n) : ObjectRef(std::move(n)) {}
  BaseExprNode *get() const { return static_cast<BaseExprNode *>(data.get()); }

  void print() const { get()->print(); }
  double eval(std::unordered_map<std::string, double> &env) const {
    return get()->eval(env);
  }
};


// ====== Expr Implementations ======
struct IntImmNode : BaseExprNode {
  double value;
  explicit IntImmNode(double v) : value(v) {}
  void print() const override { std::cout << value; }
  double eval(std::unordered_map<std::string, double> &) const override {
    return value;
  }
};

struct VarNode : BaseExprNode {
  std::string name;
  explicit VarNode(std::string n) : name(std::move(n)) {}
  void print() const override { std::cout << name; }
  double eval(std::unordered_map<std::string, double> &env) const override {
    if (!env.count(name))
      throw std::runtime_error("Undefined var: " + name);
    return env[name];
  }
};

struct BinaryOpNode : BaseExprNode {
  std::string op;
  Expr a, b;
  BinaryOpNode(std::string o, Expr l, Expr r)
      : op(std::move(o)), a(std::move(l)), b(std::move(r)) {}
  void print() const override {
    std::cout << "(";
    a.print();
    std::cout << " " << op << " ";
    b.print();
    std::cout << ")";
  }
  double eval(std::unordered_map<std::string, double> &env) const override {
    double x = a.eval(env), y = b.eval(env);
    if (op == "+")
      return x + y;
    if (op == "-")
      return x - y;
    if (op == "*")
      return x * y;
    if (op == "/")
      return y != 0 ? x / y : 0;
    throw std::runtime_error("Unknown op");
  }
};

