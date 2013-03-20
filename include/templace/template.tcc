// -*-c++-*-
namespace templace {
  template <typename T> 
  auto Template::render(std::ostream& out, const T& t) const
    -> decltype(MetaClass_<T>::fields(), void())
  {
    auto vm = ViewModel_<T>(t);
    render(out, vm);
  }	 
}
