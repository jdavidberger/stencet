#include <stencet/tags/IfTag.h>
#include <string.h>
namespace stencet {
  
  void IfTag::render(std::ostream& out, ViewContext& vm) const {
    for(auto pair : bodies){
      bool eval = pair.first == 0; // Means this is a raw else
      if(!eval){
	auto pred = use(pair.first->Eval(vm));
	eval = pred->asBool();
      }
      if(eval) {
	pair.second->render(out, vm);
	return;
      }
    }
  }

  IfTag::IfTag(std::istream& stream, const std::string& _content) {
    std::string content = _content;
    bool seenIf = false;
    bool seenElse = false;
    while( content != "" ) {
      auto& pair = *(bodies.insert( bodies.end(), std::make_pair( (Expr*)0, new Template() ) ));      
      std::string ex;
      finish f{ex};
      std::string command;
      assert(!seenElse);
      msscanf(content, "${command} ${pred}", command, f);
      if(!seenIf){
	assert(command == "if");
	seenIf = true;
	assert(ex != "");
	pair.first = Parse(ex);
      } else if(command == "else") {
	seenElse = true;
      }
            
      pair.second->Parse(stream, content);
    } 
  }

}
