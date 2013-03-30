/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

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
