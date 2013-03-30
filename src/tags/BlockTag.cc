/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#include <stencet/tags/BlockTag.h>
#include <string.h>
namespace stencet {
  void BlockTag::render(std::ostream& out, ViewContext& vm) const {
    if(vm.blocks.find(name) == vm.blocks.end())
      defaultTemplate.render(out, vm);
    else
      vm.blocks[name]->render(out, vm);
  }


  BlockTag::BlockTag(std::istream& stream, const std::string& content) {
    int m = msscanf(content, "block ${blockname}", name);
    assert(m == 2);
    defaultTemplate.Parse(stream);
  }
}
