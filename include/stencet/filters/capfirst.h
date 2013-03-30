/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

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
