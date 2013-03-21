#pragma once
#include <stencet/filter.h>
#include <string.h>

namespace stencet {
  struct CapFirstFilter : public Filter {
    CapFirstFilter(const Filter::Arg&);
    virtual ViewModel* Eval(const ViewModel* target, ViewContext& ctx);
  };
}
