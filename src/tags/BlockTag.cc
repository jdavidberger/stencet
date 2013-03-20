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
