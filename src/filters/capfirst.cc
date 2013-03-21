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
    
    Variant* rtn = new Variant();
    *rtn = buffer;
    return rtn;
  }

}


