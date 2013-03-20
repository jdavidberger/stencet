#include <stencet/template.h>
#include <dlfcn.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stencet/tag.h>

namespace stencet {
  void Template::render(std::ostream& out, ViewModel& vm) const {
    ViewContext vc;
    vc.scopes.push_back(&vm);
    return render(out, vc);
  }

  void Template::render(std::ostream& out, ViewContext& vm) const {
    for(auto region : regions)
      region->render(out, vm);
  }

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


  static void getAssemblyPath(std::string& path){
    Dl_info info;
    dladdr( (void*)&getAssemblyPath, &info);
    std::string exePath(info.dli_fname);
  
    auto end = exePath.find_last_of('/');
    end = end == std::string::npos ? 1 : end;    
    path = std::string(&exePath[0], &exePath[end]);
  }

  std::map<std::string, Template>& Template::Templates(){
    static std::map<std::string, Template> templates;
    return templates;
  }

  static std::vector<std::string>& templateDirs(){
    static std::vector<std::string>* templateDirs = 0;
    if(templateDirs == 0){
      templateDirs = new std::vector<std::string>();
      std::string& path = *templateDirs->insert(templateDirs->end(), std::string());
      getAssemblyPath(path);      
    }
    return *templateDirs;
  }

  void Template::AddDirectory(const std::string& dir){
    templateDirs().push_back(dir);
  }

  Template& Template::ByName(const std::string& name){
    if(Template::Templates().find(name) == Template::Templates().end()){
      Template& tmplte = Template::Templates()[name];
      for(auto dir : templateDirs()){
	std::string fn = dir + "/" + name + ".tc";
	std::ifstream ifs( fn, std::ifstream::in);
	if(ifs.is_open()){
	  tmplte.Parse(ifs);
	  ifs.close();
	  return tmplte;
	}
      }
      std::cerr << "Could not find '" << name << "'" << std::endl;
      return tmplte;
    }
    return Template::Templates()[name];
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
  
  void split(const std::string& contents, std::vector<std::string>& rtn){
    rtn.clear();
    const char* start = &contents[0];
    while(start != 0 && *start != 0){
      const char* next = strchr(start, ' ');
      rtn.push_back( next == NULL ? std::string(start) : std::string(start, next));
      start = next;
      if(start) start++;
    }
  }

  std::string Template::Parse(std::istream& stream){
    char curr;

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
	    break;

	  if(!endTag){
	    const char* n = &contents[0];
	    while(*n == ' ') n++;
	    const char* ne = n;
	    while(*n != ' ' && *n) ne++;

	    std::string name(n, ne);
	    Tag* tag = TagFactory::Create(name, stream, contents);
	    if(tag)
	      regions.push_back(tag);
	    else {
	      return contents;
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
    return "";
  }
}
