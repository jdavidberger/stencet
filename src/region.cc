#include <stencet/stencet>
#include <string.h>
namespace stencet {
  Region::~Region() {
  }

  void LiteralRegion::render(std::ostream& out, ViewContext& vm) const {
    out << data;
  }
  LiteralRegion::LiteralRegion() { }
  LiteralRegion::LiteralRegion(const std::string& d) : data(d) { }

  VariableRegion::VariableRegion(const std::string& name) {
    expression = Parse(name);
  }

  VariableRegion::~VariableRegion() {
    delete expression;
    expression = 0;
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
