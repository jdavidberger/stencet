#include <stencet/filter.h>
#include <string.h>

namespace stencet {
  struct CapFirstFilter : public Filter {
    CapFirstFilter(const std::string&);
    virtual ViewModel* Eval(const ViewModel& target);
  };
}
