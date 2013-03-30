// -*-c++-*-
/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

namespace stencet {
  template <typename T> 
  auto Template::render(std::ostream& out, const T& t) const
    -> decltype(MetaClass_<T>::fields(), void())
  {
    auto vm = ViewModel_<T>(t);
    render(out, vm);
  }	 
}
