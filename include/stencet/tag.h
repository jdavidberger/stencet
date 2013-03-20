#pragma once
#include <stencet/template.h>
#include <stencet/region.h>
#include <stencet/factory.h>
namespace stencet {
   struct Tag : public Region {

   };

   struct BodyTag : public Tag {
     Template body;
   };

   typedef Factory<Tag, std::istream, std::string> TagFactory;
}
