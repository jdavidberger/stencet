#pragma once
#include <stencet/stencet>

namespace stencet {
  struct IncludeTag : public BodyTag {
    std::string includeFileName;
    Template* includeThis = 0;

    virtual void render(std::ostream& out, ViewContext& vm) const;    
    IncludeTag(std::istream& stream, const std::string& content);
  };  

}
