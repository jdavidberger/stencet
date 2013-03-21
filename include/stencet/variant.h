#pragma once
#include "viewModel.h"

namespace stencet {  
  struct Variant : 
    public ViewModel, 
    public Variant_< std::map<std::string, Variant>, std::vector<Variant>, std::string, double, int, bool> {

    using MapT = std::map<std::string, Variant>;
    using ListT = std::vector<Variant>;
    using VariantT = Variant_<MapT, ListT, std::string, double, int, bool>;
    Variant();

    template <typename T>
      explicit  Variant(const T& t) : Variant() {
      *this = t;
    }

    void* operator new(size_t size);
    void operator delete(void*);

    virtual Variant* at(const std::string& name);
    virtual Variant* at(size_t);
    Variant& operator[](const std::string& name);    
    Variant& operator[](size_t);
    virtual bool hasValue(const std::string& name);
    
    virtual Type getType() const;
    virtual int asInt() const;
    virtual void asString(std::string& str) const;
    virtual size_t size() const override;

    template<typename T>
      Variant& operator=(const std::initializer_list<T>&);
    template<typename T> 
      Variant& operator=(const T&);
  };

  template<typename T>
    Variant& Variant::operator=(const std::initializer_list<T>& t){
    ListT& list = this->as<ListT>();
    list.resize(t.size());
    for(size_t i = 0;i < t.size();i++)
      list[i] = t.begin()[i];
    return *this;
  }

  template<typename T> 
  Variant& Variant::operator=(const T& t){
    VariantT::operator =(t);
    return *this;   
  } 

}
