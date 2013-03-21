#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "filter.h"
#include "variant.h"

namespace stencet {
  struct ViewContext;
  struct ViewModel;

  struct Expr {
    virtual const ViewModel* Eval(ViewContext& ctx) = 0;
    virtual void write(std::ostream& stream) = 0;
  };
  std::ostream& operator <<(std::ostream&, Expr*);
  
  struct Variable : public Expr {
    std::vector<std::string> parts;
    virtual const ViewModel* Eval(ViewContext& ctx);
    virtual void write(std::ostream& stream);
  };
  
  struct FilterExpr : public Expr {    
    Expr* target;
    Filter* filter = 0;
        
    virtual const ViewModel* Eval(ViewContext& ctx);
    virtual void write(std::ostream& stream);
  };

  namespace InfixOps {
    enum t {
      NONE = -1,
      EQ,  // ==
      NEQ, // != 
      AND, // &&
      OR,  // ||
      LEQ, // <=
      GEQ, // >=
      GT,  // >
      LT,  // <
      XOR  // ^
    };
  }
  struct InfixOperatorExpr : public Expr {
    Expr *right = 0;
    Expr *left = 0;
    InfixOps::t op;
    virtual const ViewModel* Eval(ViewContext& ctx);
    virtual void write(std::ostream& stream);
  };
  struct LiteralExpr : public Expr {
    Variant value;
    virtual const ViewModel* Eval(ViewContext& ctx);
    virtual void write(std::ostream& stream);
  };

  Expr* Parse(const std::string& exp);
}
