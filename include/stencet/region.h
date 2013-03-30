/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once
#include <iostream>
#include <stencet/viewModel.h>
#include <stencet/mscanf.h>
#include <vector>
#include <functional>
#include <string>
#include "expression.h"

namespace stencet {   
  struct Region {
    virtual void render(std::ostream& out, ViewContext& vm) const = 0;
    virtual ~Region();
  };

  struct VariableRegion : public Region {
    Expr* expression = 0;
    ~VariableRegion();

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
