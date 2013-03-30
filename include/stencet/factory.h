/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#pragma once
#include <map>
#include <functional>

namespace stencet {
  template <typename T, typename... Args>
  struct Factory {
    using Maker = std::function< T*(Args&...) >;

    static auto Makers() -> std::map<std::string, Maker >& { 
      static std::map<std::string, Maker > makers;
      return makers;
    }
     
    template <typename S>
    static auto Register(const std::string& name) -> bool {
      Makers()[name] = [](Args&... args) {
	return new S(args...);
      };
      return true;
    }

    static T* Create(const std::string& name, Args&... args){
      auto maker = Makers().find( name );
      if(maker == Makers().end()){
	return 0;
      }
      return maker->second(args...);
    }
  };
}

