/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once
#include <stencet/stencet>

namespace stencet {
  /** \page VerbatimTag Verbatim
      This tag disables template rendering within its body -- allowing you to use {{ and {%'s freely. 
      
      Anything following 'verbatim' in the opening tag will be used to designate its closing tag as well. 

      {% verbatim ignore %}
           This displays the verbatim block text {% verbatim %} {% endverbatim %}
      {% endverbatim ignore %}

      Also can be invoked with 'raw'. 
   */
  struct VerbatimTag : public BodyTag {
    std::string body;
    virtual void render(std::ostream& out, ViewContext& vm) const;    
    VerbatimTag(std::istream& stream, const std::string& content);
  };  
}
