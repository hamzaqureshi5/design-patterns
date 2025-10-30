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


#include "ir_module.h"
#include "expr_visitor.h"

int main() {
    Expr ast =
        BinaryExpr(
            '+',
            NumberExpr(10),
            BinaryExpr('*', NumberExpr(2), NumberExpr(3))
        );

    IRModule mod(ast);

    ExprVisitor visitor;
    visitor.VisitExpr(mod->body);

    return 0;
}
