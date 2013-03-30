/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once
#include <stencet/filter.h>
#include <string.h>

namespace stencet {
  /** \page defaultFilter Default 
      Use a default value if the given expression isn't defined or is empty. 
      
      ~~~~~~~
      {{ '' | default:'Hello world' }}
      ~~~~~~~

      would render as 'Hello World'; but

      ~~~~~~~
      {{ '42' | default:'Hello world' }}
      ~~~~~~~

      would render as '42'. 
   */
  struct DefaultFilter : public Filter {
    Expr* _default = 0;
    ~DefaultFilter();

    DefaultFilter(const Filter::Arg&);
    virtual const ViewModel* Eval(const ViewModel* target, ViewContext& ctx);
  };
}
