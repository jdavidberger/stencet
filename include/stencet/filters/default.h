#pragma once
#include <stencet/filter.h>
#include <string.h>

namespace stencet {
  struct DefaultFilter : public Filter {
    Expr* _default;
    DefaultFilter(const Filter::Arg&);
    virtual const ViewModel* Eval(const ViewModel* target, ViewContext& ctx);
  };
}
