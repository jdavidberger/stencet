#pragma once
#include <stencet/stencet>

namespace stencet {
  /** \page SpacelessTag Spaceless
      Removes spaces from between XML tags. 
   */
  struct SpacelessTag : public BodyTag {
    Template body;
    virtual void render(std::ostream& out, ViewContext& vm) const;    
    SpacelessTag(std::istream& stream, const std::string& content);
  };  
}
