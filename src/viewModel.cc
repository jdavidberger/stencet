#include <stencet/viewModel.h>

namespace stencet {

  ViewModel::~ViewModel() {};
  ViewModel* ViewModel::at(size_t) { assert(false); }
  size_t ViewModel::size() const { return 0; }
  
}
