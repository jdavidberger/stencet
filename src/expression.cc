#include <templace/expression.h>
#include <templace/viewModel.h>

namespace templace {
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

  Expr* Parse(const std::string& exp){
    auto expr = new Variable();
    
    const char* b = &exp[0];
    while(*b == ' ') b++;
    while(*b && *b != ' '){
      std::string& part = 
	*expr->parts.insert(expr->parts.end(), 
			    std::string() );

      while(*b != '.' && *b != ' ' &&  *b != 0) {
	part += *b;
	b++;
      }
      b++;
    }
    return expr;
  }


}
