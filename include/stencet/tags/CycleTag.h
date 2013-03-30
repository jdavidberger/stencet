/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once
#include <stencet/stencet>

namespace stencet {
  struct CycleTag : public Tag {
    std::vector<Expr*> values;
    std::string unique_name;

    ~CycleTag();
    virtual void render(std::ostream& out, ViewContext& vm) const;    
    CycleTag(std::istream& stream, const std::string& content);
  };  
}
