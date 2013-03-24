#pragma once
#include <stencet/filter.h>
#include <string.h>

namespace stencet {
  /** \page capfirstFilter Capfirst 
      Capitalizes the first letter in a given string:
      ~~~~~~~
      {{ 'word' | capfirst }}
      ~~~~~~~

      would display 'Word', for instance. 
   */
  struct CapFirstFilter : public Filter {
    CapFirstFilter(const Filter::Arg&);
    virtual ViewModel* Eval(const ViewModel* target, ViewContext& ctx);
  };
}
