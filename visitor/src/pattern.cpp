// #include <iostream>
// #include <vector>
// #include <memory> // For std::shared_ptr

// // Forward declarations
// class ConcreteElementA;
// class ConcreteElementB;

// // Visitor Interface
// class Visitor {
// public:
//     virtual void visit(ConcreteElementA& element) = 0;
//     virtual void visit(ConcreteElementB& element) = 0;
//     virtual ~Visitor() = default;
// };

// // Element Interface
// class Element {
// public:
//     virtual void accept(Visitor& visitor) = 0;
//     virtual ~Element() = default;
// };

// // Concrete Element A
// class ConcreteElementA : public Element {
// public:
//     void accept(Visitor& visitor) override {
//         visitor.visit(*this);
//     }
//     std::string operationA() const {
//         return "Operation A from ConcreteElementA";
//     }
// };

// // Concrete Element B
// class ConcreteElementB : public Element {
// public:
//     void accept(Visitor& visitor) override {
//         visitor.visit(*this);
//     }
//     std::string operationB() const {
//         return "Operation B from ConcreteElementB";
//     }
// };

// // Concrete Visitor 1: Performs a specific operation on elements
// class ConcreteVisitor1 : public Visitor {
// public:
//     void visit(ConcreteElementA& element) override {
//         std::cout << "ConcreteVisitor1 visiting ConcreteElementA: " << element.operationA() << std::endl;
//     }
//     void visit(ConcreteElementB& element) override {
//         std::cout << "ConcreteVisitor1 visiting ConcreteElementB: " << element.operationB() << std::endl;
//     }
// };

// // Concrete Visitor 2: Performs another specific operation on elements
// class ConcreteVisitor2 : public Visitor {
// public:
//     void visit(ConcreteElementA& element) override {
//         std::cout << "ConcreteVisitor2 performing a different action on ConcreteElementA." << std::endl;
//     }
//     void visit(ConcreteElementB& element) override {
//         std::cout << "ConcreteVisitor2 performing a different action on ConcreteElementB." << std::endl;
//     }
// };

// int main() {
//     std::vector<std::shared_ptr<Element>> elements;
//     elements.push_back(std::make_shared<ConcreteElementA>());
//     elements.push_back(std::make_shared<ConcreteElementB>());
//     elements.push_back(std::make_shared<ConcreteElementA>());

//     ConcreteVisitor1 visitor1;
//     ConcreteVisitor2 visitor2;

//     std::cout << "Applying ConcreteVisitor1:" << std::endl;
//     for (const auto& element : elements) {
//         element->accept(visitor1);
//     }

//     std::cout << "\nApplying ConcreteVisitor2:" << std::endl;
//     for (const auto& element : elements) {
//         element->accept(visitor2);
//     }

//     return 0;
// }

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

// --------------------------------------------
// Main
// --------------------------------------------
int main() {
    // Represents: (3 + 4) * 5
    auto expr = std::make_unique<MulExpr>(
        new AddExpr(new NumberExpr(3), new NumberExpr(4)),
        new NumberExpr(5)
    );

    PrintVisitor printer;
    EvalVisitor evaluator;

    expr->accept(&printer);
    expr->accept(&evaluator);

    std::cout << "Expression: " << printer.result << std::endl;
    std::cout << "Value: " << evaluator.result << std::endl;

    return 0;
}
