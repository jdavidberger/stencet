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
  
  ParseStatus::t Template::Parse(std::istream& stream){
    std::string exitCond;
    return Parse(stream, exitCond);
  }
  ParseStatus::t Template::Parse(const std::string& temp){
    std::stringstream ss(temp);
    return Parse(ss);
  }
  ParseStatus::t Template::Parse(std::istream& stream, std::string& unknown){
    auto status = stencet::Parse(stream, regions, unknown);
    return status;
  }
}
