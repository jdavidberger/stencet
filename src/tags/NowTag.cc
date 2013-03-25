#include <mxcomp/use.h>
#include <stencet/tags/NowTag.h>
#include <istream>
#include <ctime>
#include <cstring>

namespace stencet {
  void NowTag::render(std::ostream& out, ViewContext& vm) const {
    std::string format_string;
    
    std::time_t t = std::time(NULL);
    std::tm tm = *std::localtime(&t);
    
    use(format->Eval(vm))->asString(format_string);
    
    char buffer[128];
    strftime(buffer, sizeof(buffer), format_string.c_str(), &tm);
    out << buffer;
  }

  NowTag::~NowTag(){
    delete format;
  }

  NowTag::NowTag(std::istream& stream, const std::string& content) {
    const char* b = &content[0];
    while(isspace(*b)) b++;   
    assert(strncmp(b, "now", 3) == 0);
    b += 3;
    while(isspace(*b)) b++; 

    format = parseAtom(b);
    assert(format);       
  }
}
