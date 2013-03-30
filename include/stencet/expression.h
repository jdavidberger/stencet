/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

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
    virtual ~Expr();
  };
  std::ostream& operator <<(std::ostream&, Expr*);
  
  struct Variable : public Expr {
    std::vector<std::string> parts;
    virtual const ViewModel* Eval(ViewContext& ctx);
    virtual void write(std::ostream& stream);
  };
  
  struct FilterExpr : public Expr {    
    Expr* target = 0;    
    Filter* filter = 0; 
    ~FilterExpr();
    
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
    ~InfixOperatorExpr();
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
  
  Expr* parseAtom(const char*& b);
  Expr* Parse(const std::string& exp);
}
