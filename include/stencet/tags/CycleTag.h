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
