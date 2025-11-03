// #include "eval.h"
// #include <stdexcept>
// #include <iostream>

// //-----------------------------------------
// // EvalContext
// //-----------------------------------------
// EvalContext::EvalContext() {
//     scopes.emplace_back();
// }

// void EvalContext::push_scope() {
//     scopes.emplace_back();
// }

// void EvalContext::pop_scope() {
//     if (scopes.empty())
//         throw std::runtime_error("pop_scope on empty stack");
//     scopes.pop_back();
// }

// void EvalContext::set_var(const std::string& name, double value) {
//     if (scopes.empty()) push_scope();
//     scopes.back()[name] = value;
// }

// void EvalContext::assign_var(const std::string& name, double value) {
//     for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
//         if (it->count(name)) {
//             (*it)[name] = value;
//             return;
//         }
//     }
//     throw std::runtime_error("variable not found: " + name);
// }

// double EvalContext::get_var(const std::string& name) const {
//     for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
//         auto f = it->find(name);
//         if (f != it->end())
//             return f->second;
//     }
//     throw std::runtime_error("variable not found: " + name);
// }

// //-----------------------------------------
// // EvalExpr
// //-----------------------------------------
// double EvalExpr(const ExprPtr& e, EvalContext& ctx) {
//     if (auto n = dynamic_cast<NumberNode*>(e.get())) {
//         return n->value;
//     }
//     if (auto v = dynamic_cast<VarNode*>(e.get())) {
//         return ctx.get_var(v->name);
//     }
//     if (auto a = dynamic_cast<AddNode*>(e.get())) {
//         return EvalExpr(a->lhs, ctx) + EvalExpr(a->rhs, ctx);
//     }
//     if (auto s = dynamic_cast<SubNode*>(e.get())) {
//         return EvalExpr(s->lhs, ctx) - EvalExpr(s->rhs, ctx);
//     }
//     if (auto m = dynamic_cast<MulNode*>(e.get())) {
//         return EvalExpr(m->lhs, ctx) * EvalExpr(m->rhs, ctx);
//     }
//     if (auto d = dynamic_cast<DivNode*>(e.get())) {
//         return EvalExpr(d->lhs, ctx) / EvalExpr(d->rhs, ctx);
//     }

//     throw std::runtime_error("unknown Expr node");
// }

// //-----------------------------------------
// // ExecStmt
// //-----------------------------------------
// void ExecStmt(const StmtPtr& s, EvalContext& ctx) {

//     // Expression statement: e;
//     if (auto es = dynamic_cast<ExprStmtNode*>(s.get())) {
//         EvalExpr(es->expr, ctx);
//         return;
//     }

//     // Assignment: x = expr;
//     if (auto as = dynamic_cast<AssignStmtNode*>(s.get())) {
//         double v = EvalExpr(as->expr, ctx);
//         ctx.assign_var(as->name, v);
//         return;
//     }

//     throw std::runtime_error("unknown Stmt node");
// }
