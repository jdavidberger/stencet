#include <templace/templace>
#include <string.h>
namespace templace {

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
    ViewModel* m = expression->Eval(vm);
    
    if(m){
      std::string buffer; 
      m->asString(buffer);
      out << buffer;
    } else 
      std::cerr << "No variable '" << expression << "' defined." << std::endl;
  }
  
}

#include <templace/blocks/ForRegion.h>
#include <templace/blocks/IfRegion.h>
#include <templace/blocks/IncludeRegion.h>
#include <templace/blocks/ExtendsRegion.h>
#include <templace/blocks/NamedRegion.h>

static auto ___For = templace::RegionFactory::Register<templace::ForRegion>("for");
static auto ___If  = templace::RegionFactory::Register<templace::IfRegion>("if");
static auto ___Include  = templace::RegionFactory::Register<templace::IncludeRegion>("include");
static auto ___Extends  = templace::RegionFactory::Register<templace::ExtendsRegion>("extends");
static auto ___Region  = templace::RegionFactory::Register<templace::>("block");
