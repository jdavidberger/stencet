/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once
#include <stencet/stencet>

namespace stencet {
  struct NowTag : public Tag {
    Expr* format;
    ~NowTag();
    virtual void render(std::ostream& out, ViewContext& vm) const;    
    NowTag(std::istream& stream, const std::string& content);
  };  

}
