#include <templace/tags/IfTag.h>
#include <string.h>
namespace templace {

  static bool eval(const std::string& expr, ViewContext& vm){
    return vm.at(expr) && vm.at(expr)->asInt() > 0;
  }
  
  void IfTag::render(std::ostream& out, ViewContext& vm) const {
    for(auto pair : bodies){
      if( pair.first.size() == 0 || eval(pair.first, vm) ) {
	pair.second.render(out, vm);
	return;
      }
    }
  }

  IfTag::IfTag(std::istream& stream, const std::string& _content) {
    std::string content = _content;
    bool seenIf = false;
    bool seenElse = false;
    while( content != "" ) {
      auto& pair = *(bodies.insert( bodies.end(), std::make_pair("", Template() ) ));      
      finish f{pair.first};
      std::string command;
      assert(!seenElse);
      msscanf(content, "${command} ${pred}", command, f);
      if(!seenIf){
	assert(command == "if");
	seenIf = true;
      } else if(command == "else") {
	seenElse = true;
      }
      
      const char* ifEnd = strchr(&content[0], ' ');
      assert(ifEnd);
      while(*ifEnd == ' ') ifEnd++;

      pair.first = std::string(ifEnd);
      while(pair.first.size() && pair.first.back() == ' ') pair.first.pop_back();
      
      content = pair.second.Parse(stream);
    } 
  }

}
