/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#include <stencet/filter.h>
#include <stencet/filters/default.h>
#include <stencet/variant.h>
#include <string.h>
#include <stencet/expression.h>
namespace stencet {
  DefaultFilter::~DefaultFilter(){
    delete _default;
  }

  DefaultFilter::DefaultFilter(const Filter::Arg& arg){
    assert(arg);
    _default = arg;
  }

  const ViewModel* DefaultFilter::Eval(const ViewModel* target, ViewContext& ctx) {
    std::string buffer;
    
    bool useDef = target == 0 || 
      (target->getType() == ViewModel::String && target->size() == 0);

    if(useDef){
      return _default->Eval(ctx);
    }
    return target;
  }

}
