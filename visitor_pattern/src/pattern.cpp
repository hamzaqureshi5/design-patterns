
#include <iostream>
#include <memory>
#include <string>

// Forward declarations
class NumberExpr;
class AddExpr;
class MulExpr;
class DivExpr;

// --------------------------------------------
// Visitor Interface
// --------------------------------------------
class ExprVisitor {
public:
  virtual void visit(NumberExpr *e) = 0;
  virtual void visit(AddExpr *e) = 0;
  virtual void visit(MulExpr *e) = 0;
  virtual void visit(DivExpr *e) = 0;
  virtual ~ExprVisitor() = default;
};

// --------------------------------------------
// Base Expression Node
// --------------------------------------------
class Expr {
public:
  virtual void accept(ExprVisitor *v) = 0;
  virtual ~Expr() = default;
};

// --------------------------------------------
// Concrete Expression Nodes
// --------------------------------------------
class NumberExpr : public Expr {
public:
  int value;
  NumberExpr(int v) : value(v) {}
  void accept(ExprVisitor *v) override { v->visit(this); }
};

class AddExpr : public Expr {
public:
  std::unique_ptr<Expr> lhs, rhs;
  AddExpr(Expr *l, Expr *r) : lhs(l), rhs(r) {}
  void accept(ExprVisitor *v) override { v->visit(this); }
};

class MulExpr : public Expr {
public:
  std::unique_ptr<Expr> lhs, rhs;
  MulExpr(Expr *l, Expr *r) : lhs(l), rhs(r) {}
  void accept(ExprVisitor *v) override { v->visit(this); }
};

class DivExpr : public Expr {
public:
  std::unique_ptr<Expr> lhs, rhs;
  DivExpr(Expr *l, Expr *r) : lhs(l), rhs(r) {}
  void accept(ExprVisitor *v) override { v->visit(this); }
};

// --------------------------------------------
// Concrete Visitor 1 — Evaluator
// --------------------------------------------
class EvalVisitor : public ExprVisitor {
public:
  int result = 0;

  void visit(NumberExpr *e) override { result = e->value; }

  void visit(AddExpr *e) override {
    EvalVisitor leftEval, rightEval;
    e->lhs->accept(&leftEval);
    e->rhs->accept(&rightEval);
    result = leftEval.result + rightEval.result;
  }

  void visit(MulExpr *e) override {
    EvalVisitor leftEval, rightEval;
    e->lhs->accept(&leftEval);
    e->rhs->accept(&rightEval);
    result = leftEval.result * rightEval.result;
  }

  void visit(DivExpr *e) override {
    EvalVisitor leftEval, rightEval;
    e->lhs->accept(&leftEval);
    e->rhs->accept(&rightEval);
    result = leftEval.result / rightEval.result;
  }
};

// --------------------------------------------
// Concrete Visitor 2 — Pretty Printer
// --------------------------------------------
class PrintVisitor : public ExprVisitor {
public:
  std::string result;

  void visit(NumberExpr *e) override { result = std::to_string(e->value); }

  void visit(AddExpr *e) override {
    PrintVisitor leftPrint, rightPrint;
    e->lhs->accept(&leftPrint);
    e->rhs->accept(&rightPrint);
    result = "(" + leftPrint.result + " + " + rightPrint.result + ")";
  }

  void visit(MulExpr *e) override {
    PrintVisitor leftPrint, rightPrint;
    e->lhs->accept(&leftPrint);
    e->rhs->accept(&rightPrint);
    result = "(" + leftPrint.result + " * " + rightPrint.result + ")";
  }

  void visit(DivExpr *e) override {
    PrintVisitor leftPrint, rightPrint;
    e->lhs->accept(&leftPrint);
    e->rhs->accept(&rightPrint);
    result = "(" + leftPrint.result + " / " + rightPrint.result + ")";
  }
};



// --------------------------------------------
// Main
// --------------------------------------------
// int main() {
//   // Represents: (3 + 4) * 5
//   auto expr = std::make_unique<MulExpr>(
//       new AddExpr(new NumberExpr(3), new NumberExpr(4)),
//       new DivExpr(new NumberExpr(15), new NumberExpr(5)));

//   PrintVisitor printer;
//   EvalVisitor evaluator;

//   expr->accept(&printer);
//   expr->accept(&evaluator);

//   std::cout << "Expression: " << printer.result << std::endl;
//   std::cout << "Value: " << evaluator.result << std::endl;

//   return 0;
// }
