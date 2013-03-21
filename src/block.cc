#include <stencet/stencet>
#include <string.h>
namespace stencet {

  auto RegionFactory::Makers() -> std::map<std::string, Maker >& { 
    static std::map<std::string, Maker > makers;
    return makers;
  }

  Region* RegionFactory::Create(std::istream& stream, const std::string& contents){
    const char* nameEnd = strchr(&contents[0], ' ');
    std::string name = nameEnd ? std::string(&contents[0], nameEnd) : std::string(&contents[0]);
    auto maker = Makers().find( name );
    if(maker == Makers().end()){
      return 0;
    }
    return maker->second(stream, contents);
  }

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

#include <stencet/blocks/ForRegion.h>
#include <stencet/blocks/IfRegion.h>
#include <stencet/blocks/IncludeRegion.h>
#include <stencet/blocks/ExtendsRegion.h>
#include <stencet/blocks/NamedRegion.h>

static auto ___For = stencet::RegionFactory::Register<stencet::ForRegion>("for");
static auto ___If  = stencet::RegionFactory::Register<stencet::IfRegion>("if");
static auto ___Include  = stencet::RegionFactory::Register<stencet::IncludeRegion>("include");
static auto ___Extends  = stencet::RegionFactory::Register<stencet::ExtendsRegion>("extends");
static auto ___Region  = stencet::RegionFactory::Register<stencet::>("block");
