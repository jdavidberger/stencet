#include <stencet/tags/IncludeTag.h>
#include <string.h>
namespace stencet {
  void IncludeTag::render(std::ostream& out, ViewContext& vm) const {
    if(includeThis == 0)
      const_cast<IncludeTag*>(this)->includeThis = &Template::ByName(includeFileName);
    includeThis->render(out, vm);
  }

  IncludeTag::IncludeTag(std::istream& stream, const std::string& content) {
    std::vector<std::string> tokens;
    split(content, tokens);
    assert(tokens.size() == 2);
    assert(tokens[1][0] == '\'' && tokens[1].back() == '\'');
    includeFileName = std::string(&tokens[1][1]);
    includeFileName.pop_back();
  }
}
