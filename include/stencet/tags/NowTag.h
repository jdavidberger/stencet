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
