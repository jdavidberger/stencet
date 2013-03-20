#pragma once
#include <templace/templace>

namespace templace {
  struct IncludeTag : public BodyTag {
    std::string includeFileName;
    Template* includeThis = 0;

    virtual void render(std::ostream& out, ViewContext& vm) const;    
    IncludeTag(std::istream& stream, const std::string& content);
  };  

}
