#pragma once
#include <iostream>
#include <map>
#include <vector>
#include "utils.h"
#include <stdexcept>
#include "reflection.h"

namespace stencet {
  struct UnsupportedCast : public std::runtime_error {
  UnsupportedCast(const std::string& what) : std::runtime_error(what) {}
  };

  struct ViewModel {    
    bool managed = true;
    virtual void asString(std::string& str) const { throw UnsupportedCast(""); };
    virtual double asDouble() const { return asInt(); }
    virtual bool asBool() const { return asInt() > 0; }
    virtual int  asInt() const { return asDouble(); };

    virtual size_t size() const;
    virtual bool hasValue(const std::string& name) { return false; };
    
    virtual ViewModel* at(size_t);
    virtual ViewModel* at(const std::string& name) { throw UnsupportedCast(""); } ;
  };

  template <typename T> struct ViewModel_;

  struct Template;
  struct ViewContext : public ViewModel {
    std::vector<ViewModel*> scopes;
    std::map<std::string, const Template*> blocks;

    virtual size_t size() const;
    virtual bool hasValue(const std::string& name);
    virtual ViewModel* at(size_t);    
    virtual ViewModel* at(const std::string& name);
  };
  
  struct Variant : public ViewModel, public Variant_<std::map<std::string, Variant>, std::vector<Variant>, std::string, double, int, bool> {
    using MapT = std::map<std::string, Variant>;
    using ListT = std::vector<Variant>;
    using VariantT = Variant_<MapT, ListT, std::string, double, int, bool>;
    Variant();

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
  
}

#include "viewModel.tcc"
