#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <mxcomp/utils.h>
#include <stdexcept>
#include <mxcomp/reflection.h>

namespace stencet {
  struct UnsupportedCast : public std::runtime_error {
  UnsupportedCast(const std::string& what) : std::runtime_error(what) {}
  };

  struct ViewModel {    
    bool managed = true;
    enum Type {
      Null = -1,
      Object = 0,
      List = 1,
      String = 2,
      Double = 3,
      Int = 4,
      Bool = 5
    };
    
    virtual bool isConvertible(Type t) const;
    
    virtual Type getType() const { return Object; }
    virtual void asString(std::string& str) const { throw UnsupportedCast(""); };
    virtual double asDouble() const { return asInt(); }
    virtual bool asBool() const { return asInt() > 0; }
    virtual int  asInt() const { return asDouble(); };

    virtual size_t size() const;
    virtual bool hasValue(const std::string& name) { return false; };

    virtual ~ViewModel();
    virtual ViewModel* at(size_t);
    virtual ViewModel* at(const std::string& name) { throw UnsupportedCast(""); } ;
  };

  inline bool operator==(const ViewModel& lhs, const ViewModel& rhs);
  inline bool operator!=(const ViewModel& lhs, const ViewModel& rhs);
  inline bool operator< (const ViewModel& lhs, const ViewModel& rhs);
  inline bool operator> (const ViewModel& lhs, const ViewModel& rhs);
  inline bool operator<=(const ViewModel& lhs, const ViewModel& rhs);
  inline bool operator>=(const ViewModel& lhs, const ViewModel& rhs);

  std::ostream& operator<<(std::ostream& stream, const ViewModel& variant);

  struct Template;
  struct ViewContext : public ViewModel {
    std::vector<ViewModel*> scopes;
    std::map<std::string, const Template*> blocks;

    virtual Type getType();
    virtual size_t size() const;
    virtual bool hasValue(const std::string& name);
    virtual ViewModel* at(size_t);    
    virtual ViewModel* at(const std::string& name);
  };

  template <typename T> struct ViewModel_;  
}

#include "viewModel.tcc"
