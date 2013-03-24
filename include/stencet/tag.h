#pragma once
#include <stencet/template.h>
#include <stencet/region.h>
#include <stencet/factory.h>
namespace stencet {
  struct ParseError : public std::runtime_error { 
  ParseError(const std::string& what) : std::runtime_error(what) {}
  }; 

  struct BadlyFormedTagError : public ParseError { 
  BadlyFormedTagError(const std::string& what) : ParseError(what) {}
  };

   struct Tag : public Region {

   };

   struct BodyTag : public Tag {
     Template body;
   };

   typedef Factory<Tag, std::istream, std::string> TagFactory;
}
