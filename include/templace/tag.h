#pragma once
#include <templace/template.h>
#include <templace/region.h>

namespace templace {
   struct Tag : public Region {

   };

   struct BodyTag : public Tag {
     Template body;
   };


   struct TagFactory {
     using Maker = std::function< Tag*(std::istream&, const std::string&) >;
     
     static auto Makers() -> std::map<std::string, Maker >&;
     
     template <typename T>
     static auto Register(const std::string& name) -> Maker {
       return Makers()[name] = [](std::istream& s, const std::string& c) {
	 return new T(s, c);
       };
    }
     static Tag* Create(std::istream&, const std::string&);
  };

}
