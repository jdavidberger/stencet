#include <stencet/parser.h>
#include <stencet/tag.h>
namespace stencet {

  enum Token {
    Val,
    OpenVar,  // {{
    CloseVar, // }}
    OpenTag,  // {%
    CloseTag, // %}
    eof = EOF
  };

  static inline Token nextToken(std::istream& stream, char* buffer){
    Token rtn = Val;
    buffer[0] = stream.get();
    if(buffer[0] == EOF)
      return eof;

    char peek = stream.peek();
    if(buffer[0] == '{'){
      rtn = 
	peek == '{' ? OpenVar :
	peek == '%' ? OpenTag : Val;
    } else if (peek == '}'){
      rtn = 
	buffer[0] == '}' ? CloseVar :
	buffer[0] == '%' ? CloseTag : Val;
    }

    if(rtn != Val)
      stream.get();

    return rtn;
  }

  static void finish(std::istream& stream, std::string& text){
    Token tkn; 
    char curr;
    text.clear();
    while( (tkn = nextToken(stream, &curr)) != EOF ){
      if(tkn == CloseVar || tkn == CloseTag)
	return;    
      if(curr != ' ' || text.size() > 0)
	text += curr;
    }
  }

  ParseStatus::t Parse(std::istream& stream,
		       std::vector<Region*>& regions,
		       std::string& unknown){
    char curr;
    unknown.clear();
    LiteralRegion* lb = 0;
    Token tkn; 
    int depth = 0;
    while( (tkn = nextToken(stream, &curr)) != EOF ){
      if(tkn == OpenVar || tkn == OpenTag) {
	lb = 0;
	std::string contents;
	finish(stream, contents);
	if(tkn == OpenTag){

	  if(stream.peek() == '\r') stream.get();
	  if(stream.peek() == '\n') stream.get();

	  bool endTag = contents.find("end") == 0;
	  depth += endTag ? -1 : 1;
	  if(depth == -1)
	    return ParseStatus::POP;

	  if(!endTag){
	    const char* n = &contents[0];
	    while(*n == ' ') n++;
	    const char* ne = n;
	    while(*ne != ' ' && *ne) ne++;

	    std::string name(n, ne);
	    Tag* tag = TagFactory::Create(name, stream, contents);
	    if(tag)
	      regions.push_back(tag);
	    else {
	      contents.swap(unknown);
	      return ParseStatus::UNKNOWN;
	    }
	  }

	} else {
	  regions.push_back(new VariableRegion(contents));
	}
      } else if(tkn == Val) {
	if(lb == 0){
	  lb = new LiteralRegion();
	  regions.push_back(lb);
	}
	lb->data += curr;
      }

    }
    return ParseStatus::END;
  }

}
