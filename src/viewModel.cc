#include <stencet/viewModel.h>

namespace stencet {

  ViewModel::~ViewModel() {};
  ViewModel* ViewModel::at(size_t) { assert(false); }

  size_t ViewModel::size() const { 
    return 0;
  }

  bool ViewModel::isConvertible(Type t) const{
    Type myType = getType();
    if(t == myType) return true;
    int l = std::min(myType, t);
    int m = std::max(myType, t);
    switch(l){
    case Null: return m == Null;
    case Object: return m == Object;
    case List: return m == List;
    case String: return m > List;
    case Double: return m >= Double;
    case Int: return m >= Double;
    case Bool: return m >= Double;
    }
    return false;
  }

  std::ostream& operator<<(std::ostream& stream, const ViewModel& variant){
    std::string s; 
    variant.asString(s);
    return stream << s << std::endl;
  }
}
