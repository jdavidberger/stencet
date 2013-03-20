#pragma once
#include <stencet/stencet>

namespace stencet {
  struct BlockTag : public BodyTag {    
    std::string name;
    Template defaultTemplate;

    virtual void render(std::ostream& out, ViewContext& vm) const;    
    BlockTag(std::istream& stream, const std::string& content);
  };  

}