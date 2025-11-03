// #include <iostream>
// #include <memory>
// #include <string>
// #include <unordered_map>

// // ====== TVM-Like Core Object System ======
// struct Object {
//   virtual ~Object() = default;
// };

// template <typename T> using ObjectPtr = std::shared_ptr<T>;

// // Base smart reference wrapper (like TVM’s ObjectRef)
// struct ObjectRef {
//   ObjectPtr<Object> data;
//   ObjectRef() = default;
//   explicit ObjectRef(ObjectPtr<Object> n) : data(std::move(n)) {}
// };

// // ====== Base ExprNode ======
// struct BaseExprNode : Object {
//   virtual void print() const = 0;
//   virtual double eval(std::unordered_map<std::string, double> &env) const =
//   0;
// };

// // Expr handle (like tvm::PrimExpr)
// struct Expr : ObjectRef {
//   Expr() = default;
//   explicit Expr(ObjectPtr<BaseExprNode> n) : ObjectRef(std::move(n)) {}
//   const BaseExprNode *get() const {
//     return static_cast<BaseExprNode *>(data.get());
//   }
//   BaseExprNode *get_mutable() const {
//     return static_cast<BaseExprNode *>(data.get());
//   }

//   void print() const { get()->print(); }
//   double eval(std::unordered_map<std::string, double> &env) const {
//     return get()->eval(env);
//   }
// };

// // ====== ExprNode Implementations ======
// struct IntImmNode : BaseExprNode {
//   double value;
//   explicit IntImmNode(double v) : value(v) {}
//   void print() const override { std::cout << value; }
//   double eval(std::unordered_map<std::string, double> &) const override {
//     return value;
//   }
// };

// struct VarNode : BaseExprNode {
//   std::string name;
//   explicit VarNode(std::string n) : name(std::move(n)) {}
//   void print() const override { std::cout << name; }
//   double eval(std::unordered_map<std::string, double> &env) const override {
//     if (!env.count(name))
//       throw std::runtime_error("Undefined variable: " + name);
//     return env[name];
//   }
// };

// struct BinaryOpNode : BaseExprNode {
//   std::string op;
//   Expr a, b;
//   BinaryOpNode(std::string op, Expr lhs, Expr rhs)
//       : op(std::move(op)), a(std::move(lhs)), b(std::move(rhs)) {}
//   void print() const override {
//     std::cout << "(";
//     a.print();
//     std::cout << " " << op << " ";
//     b.print();
//     std::cout << ")";
//   }
//   double eval(std::unordered_map<std::string, double> &env) const override {
//     double x = a.eval(env), y = b.eval(env);
//     if (op == "+")
//       return x + y;
//     if (op == "-")
//       return x - y;
//     if (op == "*")
//       return x * y;
//     if (op == "/")
//       return y != 0 ? x / y : 0;
//     throw std::runtime_error("Unknown operator");
//   }
// };

// // ====== Helper Constructors (Like TVM Make Functions) ======
// inline Expr IntImm(double v) { return Expr(std::make_shared<IntImmNode>(v));
// } inline Expr Var(const std::string &n) {
//   return Expr(std::make_shared<VarNode>(n));
// }
// inline Expr Add(Expr a, Expr b) {
//   return Expr(std::make_shared<BinaryOpNode>("+", a, b));
// }
// inline Expr Sub(Expr a, Expr b) {
//   return Expr(std::make_shared<BinaryOpNode>("-", a, b));
// }
// inline Expr Mul(Expr a, Expr b) {
//   return Expr(std::make_shared<BinaryOpNode>("*", a, b));
// }
// inline Expr Div(Expr a, Expr b) {
//   return Expr(std::make_shared<BinaryOpNode>("/", a, b));
// }

// // ====== Operator Overloads (Like TVM PrimExpr) ======
// inline Expr operator+(Expr a, Expr b) { return Add(a, b); }
// inline Expr operator-(Expr a, Expr b) { return Sub(a, b); }
// inline Expr operator*(Expr a, Expr b) { return Mul(a, b); }
// inline Expr operator/(Expr a, Expr b) { return Div(a, b); }

// // ====== Example ======
// int main() {
//   // Build expression:  (x + 3) * (y - 2)
//   Expr x = Var("x");
//   Expr y = Var("y");
//   Expr expr = (x + IntImm(3)) * (y - IntImm(2));
//   // Expr expr2 = (x + IntImm(6)) / (y - IntImm(2));

//   std::cout << "=== TVM-Like AST Print ===" << std::endl;
//   expr.print();
//   std::cout << std::endl;

//   std::cout << "\n=== Evaluate ===" << std::endl;
//   std::unordered_map<std::string, double> env{{"x", 5}, {"y", 6}};
//   std::cout << "Result = " << expr.eval(env) << std::endl;

//   return 0;
// }
#include "expr.h"
// #include "object.h"
#include "stmt.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// ====== Helper Builders ====== // Part of Intrnisics
inline Expr IntImm(double v) { return Expr(std::make_shared<IntImmNode>(v)); }
inline Expr Var(const std::string &n) {
  return Expr(std::make_shared<VarNode>(n));
}
inline Expr Add(Expr a, Expr b) {
  return Expr(std::make_shared<BinaryOpNode>("+", a, b));
}
inline Expr Sub(Expr a, Expr b) {
  return Expr(std::make_shared<BinaryOpNode>("-", a, b));
}
inline Expr Mul(Expr a, Expr b) {
  return Expr(std::make_shared<BinaryOpNode>("*", a, b));
}
inline Expr Div(Expr a, Expr b) {
  return Expr(std::make_shared<BinaryOpNode>("/", a, b));
}

inline Expr operator+(Expr a, Expr b) { return Add(a, b); }
inline Expr operator-(Expr a, Expr b) { return Sub(a, b); }
inline Expr operator*(Expr a, Expr b) { return Mul(a, b); }
inline Expr operator/(Expr a, Expr b) { return Div(a, b); }

inline Stmt LetStmt(const std::string &v, Expr e) {
  return Stmt(std::make_shared<LetStmtNode>(v, e));
}
inline Stmt Evaluate(Expr e) { return Stmt(std::make_shared<EvaluateNode>(e)); }
inline Stmt Seq(const std::vector<Stmt> &s) {
  return Stmt(std::make_shared<SeqStmtNode>(s));
}
inline Stmt IfThenElse(Expr cond, Stmt t, Stmt e) {
  return Stmt(std::make_shared<IfThenElseNode>(cond, t, e));
}

// ====== Main Example ======
int main() {
  // Build this TIR-style IR:
  // let x = (5 + 3);
  // let y = (x * 2);
  // if (y > 10) {
  //    evaluate(y + 1);
  // } else {
  //    evaluate(y - 1);
  // }

  Expr five = IntImm(5);
  Expr three = IntImm(3);
  Expr two = IntImm(2);

  Expr xexpr = five + three;   // (5 + 3)
  Expr yexpr = Var("x") * two; // (x * 2)

  Stmt s1 = LetStmt("x", xexpr);
  Stmt s2 = LetStmt("y", yexpr);

  Expr cond = Var("y") - IntImm(10); // y - 10
  Stmt then_branch = Evaluate(Var("y") + IntImm(1));
  Stmt else_branch = Evaluate(Var("y") - IntImm(1));

  Stmt ifstmt = IfThenElse(cond, then_branch, else_branch);
  Stmt program = Seq({s1, s2, ifstmt});

  std::cout << "=== TIR-Like AST Print ===" << std::endl;
  program.print();

  std::cout << "\n=== Execute ===" << std::endl;
  std::unordered_map<std::string, double> env;
  program.exec(env);

  return 0;
}
