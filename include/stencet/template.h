/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once

#include <stencet/region.h>
#include <vector>
#include <iostream>
#include <mxcomp/reflection.h>
#include "parser.h"

namespace stencet {

  struct Template {
    std::vector<Region*> regions;

    void render(std::ostream& out, ViewContext& vc) const;
    void render(std::ostream& out, ViewModel& vm) const;
       
    template <typename T> 
      auto render(std::ostream& out, const T& t)  const 
      -> decltype(MetaClass_<T>::fields(), void());

    template <typename T> 
    auto With(T& t)  const 
    -> std::function< void (std::ostream&)> 
    { 
      return [&](std::ostream& out) { 
	this->render(out, t); 
      }; 
    }

    ~Template();

    ParseStatus::t Parse(std::istream& stream);
    ParseStatus::t Parse(const std::string&);
    ParseStatus::t Parse(std::istream& stream, std::string&);
    static void AddDirectory(const std::string&);
    static std::map<std::string, Template>& Templates();
    static Template& ByName(const std::string& name);
    
  };

  
  
  bool RegisterBuiltins();
  //  void split(const std::string&, std::vector<std::string>&);
}

#include "template.tcc"
