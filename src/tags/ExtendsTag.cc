/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#include <stencet/tags/ExtendsTag.h>
#include <string.h>
namespace stencet {
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
      if(m != 1){
	char tidbit[18];
	stream.getline(tidbit, 18);
	std::cerr << "'" << tidbit << "' does not specify a valid block." << std::endl;
	std::cerr << "If you are extending a template, all content must be in blocks." << std::endl;
      }

      sections[blockname].Parse(stream);
    }
  }

}

