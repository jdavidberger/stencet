#pragma once
#include <vector>
#include <iostream>
#include <stencet/factory.h>
#include <stencet/viewModel.h>

namespace stencet {
  struct Filter {
    virtual ViewModel* Eval(const ViewModel& target) = 0;
  };

  typedef Factory<Filter, std::string> FilterFactory;
}
