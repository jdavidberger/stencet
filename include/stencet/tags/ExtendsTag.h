#pragma once
#include <stencet/stencet>

namespace stencet {

  struct ExtendsTag : public BodyTag {
    Template* extendThis = 0;
    std::string extendThisName;
    std::map<std::string, Template> sections;

    virtual void render(std::ostream& out, ViewContext& vm) const;    
    ExtendsTag(std::istream& stream, const std::string& content);
  };  

}

