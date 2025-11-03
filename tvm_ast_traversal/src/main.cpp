// // main.cpp
// #include "ast.h"
// #include "visitor.h"
// #include <iostream>

// int main() {
//   // Build expression: (3 + 4) * (15 / 5)
//   ExprPtr expr = MakeMul(MakeAdd(MakeNumber(100), MakeNumber(4)),
//                          MakeDiv(MakeNumber(15), MakeNumber(5)));

//   // Print expression
//   PrintVisitor printer;
//   std::string printed = printer.Visit(expr);
//   std::cout << "Expression: " << printed << "\n";

//   // Evaluate
//   EvalVisitor evaluator;
//   int value = evaluator.Visit(expr);
//   std::cout << "Value: " << value << "\n";

//   return 0;
// }

#include "expr_visitor.h"
#include "ir_module.h"

int main() {
  Expr ast1 = BinaryExpr('+', NumberExpr(10),
                         BinaryExpr('*', NumberExpr(2), NumberExpr(3)));
  Expr ast2 = BinaryExpr('+', NumberExpr(10),
                         BinaryExpr('/', NumberExpr(2), NumberExpr(3)));

  Expr f = BinaryExpr('+', ast1, ast2);

  IRModule mod(f);

  ExprVisitor visitor;
  visitor.VisitExpr(mod->body);

  return 0;
}
