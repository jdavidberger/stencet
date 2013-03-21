#pragma once
#include "viewModel.h"

namespace stencet {  
  struct Variant : public ViewModel, public Variant_<std::map<std::string, Variant>, std::vector<Variant>, std::string, double, int, bool> {
    using MapT = std::map<std::string, Variant>;
    using ListT = std::vector<Variant>;
    using VariantT = Variant_<MapT, ListT, std::string, double, int, bool>;
    Variant();
    Variant(bool managed);

    virtual Variant* at(const std::string& name);
    virtual Variant* at(size_t);
    Variant& operator[](const std::string& name);    
    Variant& operator[](size_t);
    virtual bool hasValue(const std::string& name);
    
    virtual int asInt() const;
    virtual void asString(std::string& str) const;
    virtual size_t size() const;

    Variant& operator=(const Variant&);
    
    template<typename T> 
      Variant& operator=(const T&);
  };

  template<typename T> 
  Variant& Variant::operator=(const T& t){
    VariantT::operator =(t);
    return *this;   
  } 

}
