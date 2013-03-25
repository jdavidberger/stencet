#include <stencet/tags/VerbatimTag.h>
#include <stencet/parser.h>
#include <string.h>

namespace stencet {
  void VerbatimTag::render(std::ostream& out, ViewContext& vm) const {
    out << body;
  }

  static inline void emit_token(Token t, char c, std::string& b){
    b += c;
    switch(t){
    case OpenVar: b += '{'; break;
    case OpenTag: b += '%'; break;
    case CloseVar: 
    case CloseTag: b += '}'; break;
    default: break;
    }    
  }

  VerbatimTag::VerbatimTag(std::istream& stream, const std::string& content) { 
    std::string cmdName, blockName;

    msscanf(content, "${cmdName} ${blockName}", cmdName, blockName);
    assert(cmdName.size());
    cmdName = "end" + cmdName;

    bool done = false;
    char c;    
    Token token = Val;
    do {
      token = nextToken(stream, c);
      if( OpenTag == token ) {
	std::string temp;
	temp += "{%";

	while(stream.peek() == ' ') temp += (char)stream.get();	

	bool cmdNameMatch = true;
	for(size_t i = 0;i < cmdName.size();i++){
	  if( stream.peek() != cmdName[i] ) {
	    cmdNameMatch = false;
	    break;
	  }
	  temp += stream.get();
	}
	while(stream.peek() == ' ') temp += (char)stream.get();

	bool blockNameMatch = true;
	for(size_t i = 0;i < blockName.size();i++){
	  if( stream.peek() != blockName[i] ) {
	    blockNameMatch = false;
	    break;
	  }
	  temp += stream.get();
	}
	while(stream.peek() == ' ') temp += (char)stream.get();

	bool closeTag = 
	  '%' == (char)stream.get() && 
	  '}' == (char)stream.peek();

	done = blockNameMatch && cmdNameMatch && closeTag;

	if(!done) {
	  body += temp;
	  stream.unget();
	} else {
	  stream.get(); // Eat the '}'
	}

      } else if (token != eof) {	
	emit_token(token, c, body);
      }
    } while (token != eof);
    
  }
}
