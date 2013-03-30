/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once
#include <stencet/stencet>

namespace stencet {
  /** \page IncludeTag Include
      Used to nest pages. Uses the form:
      ~~~~~~~
      {% include '<includethis>' %}
      ~~~~~~~
      With no extension. Does not currently allow you to specify the name with a variable. 
   */
  struct IncludeTag : public BodyTag {
    std::string includeFileName;
    Template* includeThis = 0;

    virtual void render(std::ostream& out, ViewContext& vm) const;
    IncludeTag(std::istream& stream, const std::string& content);
  };  

}
