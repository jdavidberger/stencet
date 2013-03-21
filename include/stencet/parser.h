#pragma once
#include <vector>
#include <iostream>
#include "region.h"
namespace stencet {
  namespace ParseStatus {
    enum t {
      END,
      POP,
      UNKNOWN
    };
  }
  ParseStatus::t Parse(std::istream& stream, 
		       std::vector<Region*>& regions,
		       std::string& unknown);
}
