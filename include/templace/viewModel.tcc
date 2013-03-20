// -*-c++-*-
#include <sstream>
#include <assert.h>
#include "reflection.h"

namespace templace {
  template<typename T> 
  Variant& Variant::operator=(const T& t){
    VariantT::operator =(t);
    return *this;   
  } 

  template<typename T> struct ViewBase_ : public ViewModel {
    const T& t;
    ViewBase_(const T& _t) : t(_t) {}    
    virtual void asString(std::string& str) const { 
      std::stringstream ss;
      ss << t;
      str = ss.str();
    }
  };

  template <typename T> struct ViewModel_ : public ViewModel {
    const T& t;
    ViewModel_(const T& _t) : t(_t) { }
    std::map<std::string, ViewModel*> map;

    template <typename S> 
    ViewModel* operator()(const Field_<T, S>& field){
      return new ViewModel_<S>( field.get(t) );
    }
    virtual bool hasValue(const std::string& name) { 
      const auto& m = MetaClass_<T>::fields().map;
      return m.find(name) != m.end();
    };
    virtual ViewModel* at(const std::string& name) {
      if(map.find(name) == map.end())
	return map[name] = MetaClass_<T>::fields().get(name, *this);
      return map[name];
    }
  };

  template<> struct ViewModel_<std::string> : public ViewBase_<std::string> {
    ViewModel_(const std::string& _t) : ViewBase_<std::string>(_t) {}
    virtual void asString(std::string& str) const { str = t; };

  };
  template<> struct ViewModel_<int> : public ViewBase_<int> {
    ViewModel_(const int& _t) : ViewBase_<int>(_t) {}
    virtual int  asInt() const { return t; };
  };
  template<> struct ViewModel_<bool> : public ViewBase_<bool> {
    ViewModel_(const bool& _t) : ViewBase_<bool>(_t) {}
    virtual bool asBool() const { return t; };
  };
  template<> struct ViewModel_<double> : public ViewBase_<double> {
    ViewModel_(const double& _t) : ViewBase_<double>(_t) {}
    virtual double asDouble() const { return t; };
  };
}
