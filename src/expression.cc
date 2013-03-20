#include <stencet/expression.h>
#include <stencet/viewModel.h>

namespace stencet {
  std::ostream& operator <<(std::ostream& stream, Expr* e){
    e->write(stream);
    return stream;
  }

  ViewModel* Variable::Eval(ViewContext& ctx) {
    ViewModel* curr = &ctx;
    for(auto part : parts)
      if(curr)
	curr = curr->at(part);
    
    return curr;
  }

  void Variable::write(std::ostream& stream){
    stream << parts[0];
    for(size_t i = 1;i < parts.size();i++)
      stream << '.' << parts[i];    
  }

  ViewModel* FilterExpr::Eval(ViewContext& ctx) {
    if(!filter)
      filter = FilterFactory::Create(filterName, args);
    ViewModel* vm = target->Eval(ctx);
    assert(vm);
    assert(filter);
    return filter->Eval(*vm);
  }

  void FilterExpr::write(std::ostream& stream){
    target->write(stream);
    stream << " | " << filterName << " " << args;
  }

  static FilterExpr* parseFilter(Expr* target, const char*& b){
    auto filter = new FilterExpr();
    filter->target = target;

    while(*b == ' ') b++;
    while(isalpha(*b)) filter->filterName += *(b++);
    if(*b == ' ') {
      while(*b == ' ') b++;
      while(*b != '|' && *b != 0) filter->args += *b++;
    }
    
    return filter; 
  }

  static Variable* parseVariable(const char*& b) {
    auto expr = new Variable();   
    while(*b == ' ') b++;
    while(*b && *b != ' '){
      std::string& part = 
	*expr->parts.insert(expr->parts.end(), 
			    std::string() );

      while(*b != '.' && *b != ' ' &&  *b != 0) {
	part += *b;
	b++;
      }
      if(*b == '.')
	b++;
    }
    while(*b == ' ') b++;

    return expr;
  }

  Expr* Parse(const std::string& exp){
    const char* b = &exp[0];

    Expr* expr = parseVariable(b);
    if(*b == '|')
      expr = parseFilter(expr, ++b);
    
    if(*b)
      std::cerr << "Warning: '" << b << "' left unparsed." << std::endl;
    return expr;
  }
}
