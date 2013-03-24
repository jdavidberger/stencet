#pragma once
#include <stencet/stencet>

namespace stencet {
  /** \page ExtendsTag Extends
     This one can be a bit tricky to get down specifially. See \ref TemplateInheritance for the full picture. 

     This tag must be the first in a template, and after it only block tags can exist at the top level. The form is:

     ~~~~~~~
     {% extends 'Layout' %}
     {% block content %}
     ...
     {% endblock %}
     ~~~~~~~
     
     Note that there can be many blocks defined. Note also that block means something different when not right underneath an extends tag.

     The basic idea though is that whatever blocks you define here 'overwrite' the analagous ones found in the 'Layout' template. 
     
     See also: \subpage BlockTag
   */
  struct ExtendsTag : public BodyTag {
    Template* extendThis = 0;
    std::string extendThisName;
    std::map<std::string, Template> sections;

    virtual void render(std::ostream& out, ViewContext& vm) const;    
    ExtendsTag(std::istream& stream, const std::string& content);
  };  

}

