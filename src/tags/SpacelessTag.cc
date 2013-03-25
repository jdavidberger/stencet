#include <mxcomp/use.h>
#include <stencet/tags/SpacelessTag.h>
#include <istream>
#include <ctime>
#include <cstring>

namespace stencet {
  void SpacelessTag::render(std::ostream& out, ViewContext& vm) const {
    // There is some unfortunateness here -- namely we have to render the inner template before we know fully where spaces we want to eliminate are.
    std::stringstream ss;
    body.render(ss, vm);
    
    std::string space_buffer;

    while(ss.peek() != EOF){
      while(isspace( ss.peek() )) {
	space_buffer += ss.get();
      };

      if(ss.peek() != '<')
	out << space_buffer;      
      space_buffer.clear();
      
      while(ss.peek() != EOF && ss.peek() != '>') 
	out << (char)ss.get();
      if(ss.peek() == '>')
	out << (char)ss.get(); // Ingest that token
    }
  }

  SpacelessTag::SpacelessTag(std::istream& stream, const std::string& content) {
    auto status = body.Parse(stream);
    if(status != ParseStatus::POP){
      std::stringstream what;
      what << "Spaceless body parsed with a status code of: " << status;
      throw BadlyFormedTagError(what.str());
    }
  
  }
}
