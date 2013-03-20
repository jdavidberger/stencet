#include <stencet/tags/ForTag.h>
#include <string.h>
namespace stencet {
  void ForTag::render(std::ostream& out, ViewContext& vm) const {
    ViewModel* loopOver = vm.at(listName);
    assert(loopOver);

    ForTagModel loop;
    loop.forTag = this;
    vm.scopes.push_back(&loop);

    loop.loopOver = loopOver;
    loop.size = loopOver->size();
    for(size_t i = 0;i < loopOver->size();i++) {
      loop.index = i;
      loop.current = loopOver->at(i);      
      body.render(out, vm);
    }
    if(loopOver->size() == 0){
      empty.render(out, vm);
    }
    vm.scopes.pop_back();    
  }


  ForTag::ForTag(std::istream& stream, const std::string& content) {
    assert(3 == msscanf(content, "for ${val} in ${loop}", currentName, listName));
    if("" != body.Parse(stream)) {
      empty.Parse(stream);
    }
    
  }

}

