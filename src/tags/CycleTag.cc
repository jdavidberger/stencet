/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#include <stencet/tags/CycleTag.h>
#include <string.h>
#include <stencet/parser.h>
#include <mxcomp/use.h>

namespace stencet {
  CycleTag::~CycleTag(){
    for(auto e : values)
      delete e;
  }

  void CycleTag::render(std::ostream& out, ViewContext& vm) const {
    int val = 0;

    if(!vm.locals().hasValue(unique_name)) {
      vm.locals()[unique_name] = 0;
    } else {
      val = (vm.locals()[unique_name].asInt() + 1) % values.size();
      vm.locals()[unique_name] = val;
    }

    std::string buffer; 
    use(values[val]->Eval(vm))->asString(buffer);
    out << buffer;
  }


  CycleTag::CycleTag(std::istream& stream, const std::string& content) {
    const char* b = &content[0];
    while(isspace(*b)) b++; // Read up to the word cycle.
    
    assert(strncmp(b, "cycle", 5) == 0);
    b += 5;

    while(isspace(*b)) b++; // Eat all the spaces;
    
    while(*b != 0) {
      auto expr = parseAtom(b);
      assert(expr);
      values.push_back(expr);
      while(isspace(*b)) b++; // Eat all the spaces;
    }
    
    if(values.size() == 0){
      throw BadlyFormedTagError("Cycle tags must have at least one value.");
    }
    
    std::stringstream _name;
    _name << "$cycle_" << (void*)this;
    unique_name = _name.str();
  }

}

