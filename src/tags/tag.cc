#include <templace/templace>
#include <string.h>
namespace templace {

  auto TagFactory::Makers() -> std::map<std::string, Maker >& { 
    static std::map<std::string, Maker > makers;
    return makers;
  }

  Tag* TagFactory::Create(std::istream& stream, const std::string& contents){
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

#include <templace/tags/ForTag.h>
#include <templace/tags/IfTag.h>
#include <templace/tags/IncludeTag.h>
#include <templace/tags/ExtendsTag.h>
#include <templace/tags/BlockTag.h>

static auto ___For = templace::TagFactory::Register<templace::ForTag>("for");
static auto ___If  = templace::TagFactory::Register<templace::IfTag>("if");
static auto ___Include  = templace::TagFactory::Register<templace::IncludeTag>("include");
static auto ___Extends  = templace::TagFactory::Register<templace::ExtendsTag>("extends");
static auto ___Region  = templace::TagFactory::Register<templace::BlockTag>("block");
