/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once
#include <stencet/stencet>

namespace stencet {
  /** 
      \page ForTag For
      This filter is used to loop over a list. Its syntax is:
      ~~~~~~~
      {% for ${val} in ${loop} %}
      ...
      {% endfor %}
      ~~~~~~~
      
      where val must be a single valid variable name, and loop can be any expression. 

      Optionally, you can have an empty body definition too:

      ~~~~~~~
      {% for ${val} in ${loop} %}
      ...
      {% empty %}
      ...
      {% endfor %}
      ~~~~~~~

      Where items in the second body are only displayed if nothing is in the looped list. 
   */
  struct ForTag : public BodyTag {
    Template body, empty;
    
    std::string currentName, listName;

    virtual void render(std::ostream& out, ViewContext& vm) const;
    
    ForTag(std::istream& stream, const std::string& content);
  };  
}
