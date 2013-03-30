/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

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

  enum Token {
    Val,
    OpenVar,  // {{
    CloseVar, // }}
    OpenTag,  // {%
    CloseTag, // %}
    eof = EOF
  };

  Token nextToken(std::istream& stream, char& buffer);
      
  ParseStatus::t Parse(std::istream& stream, 
		       std::vector<Region*>& regions,
		       std::string& unknown);
}
