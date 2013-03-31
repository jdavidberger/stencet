/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

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

    virtual Type getType() const;
    virtual size_t size() const;
    virtual bool hasValue(const std::string& name);
    virtual ViewModel* at(size_t);    
    virtual ViewModel* at(const std::string& name);
  };
}
