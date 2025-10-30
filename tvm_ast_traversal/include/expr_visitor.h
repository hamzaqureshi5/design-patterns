#pragma once
#include "expr.h"
#include <iostream>

class ExprVisitor {
public:
    virtual void VisitExpr(const Expr& expr) {
        auto* n = expr.data.ptr;

        if (auto* num = dynamic_cast<NumberExprNode*>(n))
            return VisitExpr_(num);

        if (auto* bin = dynamic_cast<BinaryExprNode*>(n))
            return VisitExpr_(bin);

        std::cerr << "Unknown ExprNode\n";
    }

protected:
    virtual void VisitExpr_(NumberExprNode* op) {
        std::cout << "Number: " << op->value << "\n";
    }

    virtual void VisitExpr_(BinaryExprNode* op) {
        std::cout << "Binary(" << op->op << ")\n";
        VisitExpr(op->lhs);
        VisitExpr(op->rhs);
    }
};
