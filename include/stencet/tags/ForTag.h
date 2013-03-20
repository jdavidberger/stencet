#pragma once
#include <stencet/stencet>

namespace stencet {

  struct ForTag : public BodyTag {
    Template body, empty;
    
    std::string currentName, listName;

    ForTag(const std::string& contentLine){
    }

    ForTag(const std::string& n, 
	     const std::string& l) : currentName(n), listName(l) {
    }
    virtual void render(std::ostream& out, ViewContext& vm) const;
    
    ForTag(std::istream& stream, const std::string& content);
  };  

  struct ForTagModel : public ViewModel {
    size_t size, index;
    ViewModel* loopOver, *current;
    const ForTag* forTag;
    std::string argName;

    virtual bool hasValue(const std::string& name) {
      return at(name) != 0;
    }

    virtual ViewModel* at(const std::string& name) {
      if( name == forTag->currentName)
	return current;
      return 0;
    }
  };

}
