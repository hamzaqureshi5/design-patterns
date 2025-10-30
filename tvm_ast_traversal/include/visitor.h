// // visitor.h
// #pragma once
// #include "ast.h"
// #include <functional>
// #include <iostream>
// #include <string>
// #include <typeindex>
// #include <typeinfo>
// #include <unordered_map>
// #include <utility>

// // Functor-style visitor base.
// // R = return type of Visit (e.g., int or std::string)
// template <typename R>
// class Functor {
//  public:
//   Functor() = default;
//   virtual ~Functor() = default;

//   // Dispatch entry point: call this with an ExprPtr to visit.
//   R Visit(const ExprPtr &expr) {
//     if (!expr) {
//       throw std::runtime_error("Visit: null node");
//     }
//     std::type_index ti(typeid(*expr));
//     auto it = table_.find(ti);
//     if (it == table_.end()) {
//       // default fallback: no handler registered
//       throw std::runtime_error(std::string("No handler registered for ") + ti.name());
//     }
//     // Call the stored wrapper which knows how to cast Expr* -> Concrete*
//     return it->second(expr.get());
//   }

//  protected:
//   // Register a handler for concrete node type T.
//   // Handler should be a member function of Derived with signature: R (DerivedVisitor::*)(T*)
//   template <typename T, typename Derived>
//   void Register(Derived *self, R (Derived::*memfun)(T *)) {
//     // Wrap member function into std::function<R(Expr*)> with proper cast
//     std::function<R(Expr *)> wrapper = [self, memfun](Expr *basePtr) -> R {
//       T *concrete = dynamic_cast<T *>(basePtr);
//       if (!concrete) {
//         throw std::runtime_error("Bad cast in visitor wrapper");
//       }
//       return (self->*memfun)(concrete);
//     };
//     table_.emplace(std::type_index(typeid(T)), std::move(wrapper));
//   }

//  private:
//   // Map runtime type_index -> wrapper(Expr*) -> R
//   std::unordered_map<std::type_index, std::function<R(Expr *)>> table_;
// };

// // -----------------------------
// // EvalVisitor: computes integer value
// // -----------------------------
// class EvalVisitor : public Functor<int> {
//  public:
//   EvalVisitor() {
//     // Register handlers: map concrete node types -> member functions
//     Register<NumberNode>(this, &EvalVisitor::VisitNumber);
//     Register<AddNode>(this, &EvalVisitor::VisitAdd);
//     Register<MulNode>(this, &EvalVisitor::VisitMul);
//     Register<DivNode>(this, &EvalVisitor::VisitDiv);
//   }

//   int VisitNumber(NumberNode *n) {
//     return n->value;
//   }

//   int VisitAdd(AddNode *n) {
//     int l = Visit(n->lhs);
//     int r = Visit(n->rhs);
//     return l + r;
//   }

//   int VisitMul(MulNode *n) {
//     int l = Visit(n->lhs);
//     int r = Visit(n->rhs);
//     return l * r;
//   }

//   int VisitDiv(DivNode *n) {
//     int l = Visit(n->lhs);
//     int r = Visit(n->rhs);
//     // integer division, same as your example
//     return l / r;
//   }
// };

// // -----------------------------
// // PrintVisitor: pretty-print expression to string
// // -----------------------------
// class PrintVisitor : public Functor<std::string> {
//  public:
//   PrintVisitor() {
//     Register<NumberNode>(this, &PrintVisitor::VisitNumber);
//     Register<AddNode>(this, &PrintVisitor::VisitAdd);
//     Register<MulNode>(this, &PrintVisitor::VisitMul);
//     Register<DivNode>(this, &PrintVisitor::VisitDiv);
//   }

//   std::string VisitNumber(NumberNode *n) {
//     return std::to_string(n->value);
//   }

//   std::string VisitAdd(AddNode *n) {
//     std::string ls = Visit(n->lhs);
//     std::string rs = Visit(n->rhs);
//     return "(" + ls + " + " + rs + ")";
//   }

//   std::string VisitMul(MulNode *n) {
//     std::string ls = Visit(n->lhs);
//     std::string rs = Visit(n->rhs);
//     return "(" + ls + " * " + rs + ")";
//   }

//   std::string VisitDiv(DivNode *n) {
//     std::string ls = Visit(n->lhs);
//     std::string rs = Visit(n->rhs);
//     return "(" + ls + " / " + rs + ")";
//   }
// };
