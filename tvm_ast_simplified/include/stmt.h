#pragma once
#include "expr.h"
//#include "object.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
// ====== Stmt Base ======
struct BaseStmtNode : Object {
  virtual void print() const = 0;
  virtual void exec(std::unordered_map<std::string, double> &env) const = 0;
};

struct Stmt : ObjectRef {
  Stmt() = default;
  explicit Stmt(ObjectPtr<BaseStmtNode> n) : ObjectRef(std::move(n)) {}
  BaseStmtNode *get() const { return static_cast<BaseStmtNode *>(data.get()); }

  void print() const { get()->print(); }
  void exec(std::unordered_map<std::string, double> &env) const {
    get()->exec(env);
  }
};

// ====== Stmt Implementations ======
struct LetStmtNode : BaseStmtNode {
  std::string var;
  Expr value;
  LetStmtNode(std::string v, Expr val)
      : var(std::move(v)), value(std::move(val)) {}
  void print() const override {
    std::cout << "let " << var << " = ";
    value.print();
    std::cout << ";" << std::endl;
  }
  void exec(std::unordered_map<std::string, double> &env) const override {
    env[var] = value.eval(env);
  }
};

struct EvaluateNode : BaseStmtNode {
  Expr expr;
  explicit EvaluateNode(Expr e) : expr(std::move(e)) {}
  void print() const override {
    std::cout << "evaluate(";
    expr.print();
    std::cout << ");" << std::endl;
  }
  void exec(std::unordered_map<std::string, double> &env) const override {
    double r = expr.eval(env);
    std::cout << "=> " << r << std::endl;
  }
};

struct SeqStmtNode : BaseStmtNode {
  std::vector<Stmt> body;
  explicit SeqStmtNode(std::vector<Stmt> b) : body(std::move(b)) {}
  void print() const override {
    for (auto &s : body)
      s.print();
  }
  void exec(std::unordered_map<std::string, double> &env) const override {
    for (auto &s : body)
      s.exec(env);
  }
};

struct IfThenElseNode : BaseStmtNode {
  Expr cond;
  Stmt then_branch, else_branch;
  IfThenElseNode(Expr c, Stmt t, Stmt e)
      : cond(std::move(c)), then_branch(std::move(t)),
        else_branch(std::move(e)) {}
  void print() const override {
    std::cout << "if (";
    cond.print();
    std::cout << ") {" << std::endl;
    then_branch.print();
    std::cout << "} else {" << std::endl;
    else_branch.print();
    std::cout << "}" << std::endl;
  }
  void exec(std::unordered_map<std::string, double> &env) const override {
    if (cond.eval(env))
      then_branch.exec(env);
    else
      else_branch.exec(env);
  }
};
