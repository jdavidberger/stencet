#include <stencet/tags/ForTag.h>
#include <string.h>
#include <stencet/parser.h>
namespace stencet {

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


  void ForTag::render(std::ostream& out, ViewContext& vm) const {
    ViewModel* loopOver = vm.at(listName);
    assert(loopOver);

    ForTagModel loop;
    loop.forTag = this;
    vm.push_scope(&loop);

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

    vm.pop_scope();
  }


  ForTag::ForTag(std::istream& stream, const std::string& content) {
    assert(3 == msscanf(content, "for ${val} in ${loop}", currentName, listName));
    if(ParseStatus::UNKNOWN == body.Parse(stream)) {
      empty.Parse(stream);
    }
  }

}

