#pragma once
#include <stencet/stencet>

namespace stencet {
  /** \page CommentTag Comment
      This tag ignores everything within its body.       
   */
  struct CommentTag : public BodyTag {
    virtual void render(std::ostream& out, ViewContext& vm) const;    
    CommentTag(std::istream& stream, const std::string& content);
  };  
}
