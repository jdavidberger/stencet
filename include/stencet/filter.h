#pragma once
#include <vector>
#include <iostream>
#include <stencet/factory.h>
#include <stencet/viewModel.h>

namespace stencet {
  struct Expr;
  struct Filter {
    using Arg = Expr*;
    virtual const ViewModel* Eval(const ViewModel* target, ViewContext& ctx) = 0;
  };

  typedef Factory<Filter, Filter::Arg > FilterFactory;
}
