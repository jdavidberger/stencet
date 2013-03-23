#include <stencet/filter.h>

namespace stencet {
  std::ostream& operator <<(std::ostream& stream, const Filter&f){
    f.write(stream);
    return stream;
  }

  Filter::~Filter() {

  }

  void Filter::write(std::ostream& stream) const {
    stream << "(no info)";
  }
}
