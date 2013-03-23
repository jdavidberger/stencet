#pragma once
#include <stencet/stencet>

namespace stencet {
  struct IfTag : public BodyTag {
    std::vector<std::pair< Expr*, Template* > > bodies;
    ~IfTag();
    virtual void render(std::ostream& out, ViewContext& vm) const;    
    IfTag(std::istream& stream, const std::string& content);
  };  

}
