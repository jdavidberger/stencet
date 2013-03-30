/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once
#include <stencet/stencet>

namespace stencet {
  /** \page IfTag If
      Use in the form: 
      ~~~~~~~
      {% if <expression> %}
      ...
      {% elif <expression> %}
      ...
      {% else %}
      ...
      {% endif %}
      ~~~~~~~

      Look at \ref expressions for information on what can go into an expression (it's about what you'd expect though). There can be as many else if statements as you need; but an error is triggered if you try specifying the else before an elif, or if you try specifying more than one else. 
   */
  struct IfTag : public BodyTag {
    std::vector<std::pair< Expr*, Template* > > bodies;
    ~IfTag();
    virtual void render(std::ostream& out, ViewContext& vm) const;    
    IfTag(std::istream& stream, const std::string& content);
  };  

}
