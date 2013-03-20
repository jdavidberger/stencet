#pragma once
#include <stencet/stencet>

namespace stencet {
  struct IfTag : public BodyTag {
    std::vector<std::pair< std::string, Template > > bodies;

    virtual void render(std::ostream& out, ViewContext& vm) const;    
    IfTag(std::istream& stream, const std::string& content);
  };  

}