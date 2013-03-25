#include <stencet/tags/CommentTag.h>
#include <stencet/parser.h>
#include <string.h>

namespace stencet {
  void CommentTag::render(std::ostream& out, ViewContext& vm) const {
    
  }

  CommentTag::CommentTag(std::istream& stream, const std::string& content) { 
    bool done = false;
    char c;
    char buffer[sizeof("endcomment")];

    Token token;
    do {
      token = nextToken(stream, c);
      
      if( OpenTag == nextToken(stream, c) ){
	while(stream.peek() == ' ') stream.get();	
	stream.get(buffer, sizeof(buffer) );
	while(stream.peek() == ' ') stream.get();

	bool closeTag = 
	  '%' == (char)stream.get() && 
	  '}' == (char)stream.peek();
	stream.unget();

	done = strncmp(buffer, "endcomment", sizeof(buffer)) == 0 && closeTag;
      }
    } while (!done && token != eof);
    
  }
}
