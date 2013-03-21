#include <stencet/filter.h>
#include <stencet/variant.h>
#include <string.h>

namespace stencet {
  struct CapFirstFilter : public Filter {
    CapFirstFilter(const std::string&);
    virtual ViewModel* Eval(const ViewModel& target);
  };
  CapFirstFilter::CapFirstFilter(const std::string&){}

  ViewModel* CapFirstFilter::Eval(const ViewModel& target) {
    std::string buffer;
    target.asString(buffer);
    
    if(buffer.size() > 0 && buffer[0] >= 'a' && buffer[0] <= 'z')
      buffer[0] += 'A' - 'a';
    
    Variant* rtn = new Variant();
    *rtn = buffer;
    return rtn;
  }

}


