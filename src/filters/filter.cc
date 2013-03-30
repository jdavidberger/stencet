/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

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
