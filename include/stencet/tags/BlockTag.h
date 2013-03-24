#pragma once
#include <stencet/stencet>

namespace stencet {
  /** \page BlockTag Block
      Defines a named overrideable section of content. The form is:
      
      ~~~~~~~
      {% block <name> %}
      ...
      {% endblock %}
      ~~~~~~~

      Whatever occurs between the tag is the default content to be rendered. If the sub-template page doesn't override the block, this is the content displayed. 

      If the template is invoked directly, and not extended, blocks don't do anything. 
   */
  struct BlockTag : public BodyTag {    
    std::string name;
    Template defaultTemplate;

    virtual void render(std::ostream& out, ViewContext& vm) const;    
    BlockTag(std::istream& stream, const std::string& content);
  };  

}
