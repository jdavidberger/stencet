#pragma once
#include <vector>
#include <iostream>

namespace templace {
  struct ViewContext;
  struct ViewModel;

  struct Expr {
    virtual ViewModel* Eval(ViewContext& ctx) = 0;
    virtual void write(std::ostream& stream) = 0;
  };
  
  std::ostream& operator <<(std::ostream&, Expr*);

  
  struct Variable : public Expr {
    std::vector<std::string> parts;
    virtual ViewModel* Eval(ViewContext& ctx);
    virtual void write(std::ostream& stream);
  };
  
  Expr* Parse(const std::string& exp);
}
