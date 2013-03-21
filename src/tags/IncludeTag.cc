#include <stencet/tags/IncludeTag.h>
#include <string.h>
namespace stencet {
  void IncludeTag::render(std::ostream& out, ViewContext& vm) const {
    if(includeThis == 0)
      const_cast<IncludeTag*>(this)->includeThis = &Template::ByName(includeFileName);
    includeThis->render(out, vm);
  }

  IncludeTag::IncludeTag(std::istream& stream, const std::string& content) {
    assert(2 == msscanf(content, "include \"${}\"", includeFileName));
  }
}
