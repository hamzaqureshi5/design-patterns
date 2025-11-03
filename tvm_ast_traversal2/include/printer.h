// printer.h
#pragma once
#include "ast.h"
#include <string>

std::string PrintExpr(const ExprPtr& e);
std::string PrintStmt(const StmtPtr& s);
