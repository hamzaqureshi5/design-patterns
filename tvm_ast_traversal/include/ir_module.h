#pragma once
#include "expr.h"

class IRModuleNode : public Object {
public:
  Expr body;
  explicit IRModuleNode(Expr body) : body(body) {}
};

class IRModule : public ObjectRef<IRModuleNode> {
public:
  explicit IRModule(Expr body)
      : ObjectRef<IRModuleNode>(new IRModuleNode(body)) {}
};
