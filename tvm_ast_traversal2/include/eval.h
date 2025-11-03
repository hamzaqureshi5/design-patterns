#pragma once
#include "ast.h"
#include <unordered_map>
#include <string>

struct EvalContext {
    EvalContext();   // <-- ADD THIS
    std::vector<std::unordered_map<std::string,double>> scopes;

    void push_scope();
    void pop_scope();
    void set_var(const std::string& name, double value);
    void assign_var(const std::string& name, double value);
    double get_var(const std::string& name) const;
};

double EvalExpr(const ExprPtr& e, EvalContext& ctx);
void ExecStmt(const StmtPtr& s, EvalContext& ctx);
