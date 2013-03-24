#pragma once
#include <vector>
#include <iostream>
#include <stencet/factory.h>
#include <stencet/viewContext.h>

namespace stencet {
  struct Expr;
  struct Filter {
    using Arg = Expr*;
    virtual const ViewModel* Eval(const ViewModel* target, ViewContext& ctx) = 0;
    virtual ~Filter();
    virtual void write(std::ostream& stream) const;
  };
  std::ostream& operator <<(std::ostream&, const Filter&);
  typedef Factory<Filter, Filter::Arg > FilterFactory;
}
