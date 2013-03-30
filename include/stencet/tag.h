/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

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
