#include <stencet/stencet>
#include <string.h>
namespace stencet {

  void LiteralRegion::render(std::ostream& out, ViewContext& vm) const {
    out << data;
  }

  LiteralRegion::LiteralRegion(const std::string& d) : data(d) {
  }
  LiteralRegion::LiteralRegion() {
  }

  VariableRegion::VariableRegion(const std::string& name) {
    expression = Parse(name);
  }

  void VariableRegion::render(std::ostream& out, ViewContext& vm) const {
    auto m = use(expression->Eval(vm));
    if(m){
      std::string buffer; 
      m->asString(buffer);
      out << buffer;
    } else 
      std::cerr << "No variable '" << expression << "' defined." << std::endl;
  }
  
}

#include <stencet/tags/ForTag.h>
#include <stencet/tags/IfTag.h>
#include <stencet/tags/IncludeTag.h>
#include <stencet/tags/ExtendsTag.h>
#include <stencet/tags/BlockTag.h>

static auto ___For = stencet::TagFactory::Register<stencet::ForTag>("for");
static auto ___If  = stencet::TagFactory::Register<stencet::IfTag>("if");
static auto ___Include  = stencet::TagFactory::Register<stencet::IncludeTag>("include");
static auto ___Extends  = stencet::TagFactory::Register<stencet::ExtendsTag>("extends");
static auto ___Region  = stencet::TagFactory::Register<stencet::BlockTag>("block");

#include <stencet/filters/capfirst.h>
#include <stencet/filters/default.h>
static auto ___capfirst  = stencet::FilterFactory::Register<stencet::CapFirstFilter>("capfirst");
static auto ___default  = stencet::FilterFactory::Register<stencet::DefaultFilter>("default");
