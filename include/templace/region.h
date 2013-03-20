#pragma once
#include <iostream>
#include <templace/viewModel.h>
#include <templace/mscanf.h>
#include <vector>
#include <functional>
#include <string>
#include "expression.h"

namespace templace {   
  struct Region {
    virtual void render(std::ostream& out, ViewContext& vm) const = 0;
  };

  struct VariableRegion : public Region {
    Expr* expression; 
    VariableRegion(const std::string& name);
    virtual void render(std::ostream& out, ViewContext& vm) const;
  };

  struct LiteralRegion : public Region {
    std::string data; 
    LiteralRegion(const std::string&);
    LiteralRegion();
    virtual void render(std::ostream& out, ViewContext& vm) const;
  };

}
