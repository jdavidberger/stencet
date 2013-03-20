#include <iostream>
#include <map>
#include <vector>
#include <stencet/viewModel.h>

namespace stencet {
  ViewModel* ViewContext::at(size_t) {
    assert(false);
  }

  size_t ViewContext::size() const {
    return 0;
  }

  bool ViewContext::hasValue(const std::string& name){
    for(size_t i = scopes.size() - 1;i != (size_t)-1;i--){
     if(scopes[i]->hasValue(name))
	return true;
    }   
   return false;
  }
  ViewModel* ViewContext::at(const std::string& name){
    for(size_t i = scopes.size() - 1;i != (size_t)-1;i--){
      if(scopes[i]->hasValue(name))
	return scopes[i]->at(name);
    }
    return NULL;
  }
}
