// // printer.cpp
// #include "printer.h"
// #include <sstream>

// std::string PrintExpr(const ExprPtr& e) {
//     if (!e) return "null";
//     if (auto n = dynamic_cast<NumberNode*>(e.get())) {
//         return std::to_string(n->value);
//     }
//     if (auto v = dynamic_cast<VarNode*>(e.get())) {
//         return v->name;
//     }
//     if (auto a = dynamic_cast<AddNode*>(e.get())) {
//         return "(" + PrintExpr(a->lhs) + " + " + PrintExpr(a->rhs) + ")";
//     }
//     if (auto s = dynamic_cast<SubNode*>(e.get())) {
//         return "(" + PrintExpr(s->lhs) + " - " + PrintExpr(s->rhs) + ")";
//     }
//     if (auto m = dynamic_cast<MulNode*>(e.get())) {
//         return "(" + PrintExpr(m->lhs) + " * " + PrintExpr(m->rhs) + ")";
//     }
//     if (auto d = dynamic_cast<DivNode*>(e.get())) {
//         return "(" + PrintExpr(d->lhs) + " / " + PrintExpr(d->rhs) + ")";
//     }
//     return "<?>"; 
// }

// std::string PrintStmt(const StmtPtr& s) {
//     if (!s) return "null";
//     if (auto es = dynamic_cast<ExprStmtNode*>(s.get())) {
//         return PrintExpr(es->expr) + ";";
//     }
//     if (auto as = dynamic_cast<AssignNode*>(s.get())) {
//         return as->var + " = " + PrintExpr(as->value) + ";";
//     }
//     if (auto ls = dynamic_cast<LetStmtNode*>(s.get())) {
//         return "let " + ls->var + " = " + PrintExpr(ls->value) + " in " + PrintStmt(ls->body);
//     }
//     if (auto seq = dynamic_cast<SeqNode*>(s.get())) {
//         std::string out = "{ ";
//         for (const auto &st : seq->stmts) out += PrintStmt(st) + " ";
//         out += "}";
//         return out;
//     }
//     if (auto iff = dynamic_cast<IfNode*>(s.get())) {
//         std::string out = "if (" + PrintExpr(iff->cond) + ") " + PrintStmt(iff->then_case);
//         if (iff->else_case) out += " else " + PrintStmt(iff->else_case);
//         return out;
//     }
//     if (auto f = dynamic_cast<ForNode*>(s.get())) {
//         return "for (" + f->var + " = " + PrintExpr(f->begin) + "; " + f->var + " < " + PrintExpr(f->end) + ") " + PrintStmt(f->body);
//     }
//     return "<?>;";
// }
