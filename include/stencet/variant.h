#pragma once
#include "viewModel.h"
#include <memory>
#include <mxcomp/variant.h>

namespace stencet {  

  struct Variant;
  using MapT = std::map<std::string, std::unique_ptr<Variant> >;
  using ListT = std::vector< std::unique_ptr<Variant> >;
  using VariantT = Variant_<MapT, ListT, std::string, double, int, bool>;
  
  struct Variant : public ViewModel, public VariantT {
  public:
    Variant();
    template <typename T>
      static Variant* Create(const T& t)  {
      auto rtn = new Variant();
      *rtn = t;
      rtn->managed = false;
      return rtn;
    }

    virtual Variant* at(const std::string& name);
    virtual Variant* at(size_t);
    Variant& operator[](const std::string& name);    
    Variant& operator[](size_t);

    template<typename T> Variant& append(const T&);

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

  template<typename T> Variant& Variant::append(const T& t){
    ListT& list = this->as<ListT>();
    list.push_back( std::unique_ptr<Variant>( new Variant() ) );     
    *list.back() = t;
    return *list.back().get();
  }
}
