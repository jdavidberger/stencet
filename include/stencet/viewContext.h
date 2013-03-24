#pragma once
#include <stencet/viewModel.h>
#include <stencet/variant.h>

namespace stencet {
  struct Template;
  struct ViewContext : public ViewModel {
  private: 
    std::vector<ViewModel*> scopes;
    std::vector<Variant> _locals;
  public:
    std::map<std::string, const Template*> blocks;

    Variant& locals();
    void push_scope(ViewModel*);
    void pop_scope();

    virtual Type getType();
    virtual size_t size() const;
    virtual bool hasValue(const std::string& name);
    virtual ViewModel* at(size_t);    
    virtual ViewModel* at(const std::string& name);
  };
}
