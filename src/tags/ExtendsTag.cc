#include <templace/tags/ExtendsTag.h>
#include <string.h>
namespace templace {
  void ExtendsTag::render(std::ostream& out, ViewContext& vm) const {
    for(auto& pair : sections){
      vm.blocks[pair.first] = &pair.second;
    }

    if(extendThis == 0)
      const_cast<ExtendsTag*>(this)->extendThis = &Template::ByName(extendThisName);
    extendThis->render(out, vm);
  }


  ExtendsTag::ExtendsTag(std::istream& stream, const std::string& content) {
    int m = msscanf(content, "extends \"${extendThis}\"", extendThisName);
    assert(m == 2);
    while(stream.good()){
      std::string blockname;      
      int m = msscanf(stream, "{% block ${blockname} %}", blockname);
      assert(m == 1);
      sections[blockname].Parse(stream);
    }
  }

}

