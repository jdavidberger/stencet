/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#include <stencet/filter.h>
#include <stencet/filters/capfirst.h>
#include <stencet/variant.h>
#include <string.h>

namespace stencet {
  CapFirstFilter::CapFirstFilter(const Filter::Arg& x){
    assert(x == 0);
  }

  ViewModel* CapFirstFilter::Eval(const ViewModel* target, ViewContext& ctx) {
    std::string buffer;
    target->asString(buffer);
    
    if(buffer.size() > 0 && buffer[0] >= 'a' && buffer[0] <= 'z')
      buffer[0] += 'A' - 'a';
    
    Variant* rtn = Variant::Create(buffer);
    return rtn;
  }

}


