#pragma once

#include <templace/region.h>
#include <vector>
#include <iostream>
#include "reflection.h"

namespace templace {

  struct Template {
    std::vector<Region*> regions;
    void render(std::ostream& out, ViewContext& vc) const;
    void render(std::ostream& out, ViewModel& vm) const;
    
    template <typename T> 
      auto render(std::ostream& out, const T& t)  const 
      -> decltype(MetaClass_<T>::fields(), void());

    std::string Parse(std::istream& stream);


    static void AddDirectory(const std::string&);
    static std::map<std::string, Template>& Templates();
    static Template& ByName(const std::string& name);
  };

  void split(const std::string&, std::vector<std::string>&);
}

#include "template.tcc"
