#include <stencet/stencet>
#include <string.h>

#include <stencet/tags/ForTag.h>
#include <stencet/tags/IfTag.h>
#include <stencet/tags/IncludeTag.h>
#include <stencet/tags/ExtendsTag.h>
#include <stencet/tags/BlockTag.h>
#include <stencet/tags/CycleTag.h>
#include <stencet/tags/NowTag.h>
#include <stencet/tags/SpacelessTag.h>
#include <stencet/tags/CommentTag.h>

#include <stencet/filters/capfirst.h>
#include <stencet/filters/default.h>

namespace stencet {
  bool RegisterBuiltins() {
    stencet::TagFactory::Register<stencet::ForTag>("for");
    stencet::TagFactory::Register<stencet::IfTag>("if");
    stencet::TagFactory::Register<stencet::IncludeTag>("include");
    stencet::TagFactory::Register<stencet::ExtendsTag>("extends");
    stencet::TagFactory::Register<stencet::BlockTag>("block");
    stencet::TagFactory::Register<stencet::CycleTag>("cycle");
    stencet::TagFactory::Register<stencet::NowTag>("now");
    stencet::TagFactory::Register<stencet::SpacelessTag>("spaceless");
    stencet::TagFactory::Register<stencet::CommentTag>("comment");
    
    stencet::FilterFactory::Register<stencet::CapFirstFilter>("capfirst");
    stencet::FilterFactory::Register<stencet::DefaultFilter>("default");
    return true;
  }
}
