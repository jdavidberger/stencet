#include <stencet/expression.h>
#include <stencet/viewModel.h>
#include <stencet/variant.h>
#include <string.h>
#include <mxcomp/use.h>

namespace stencet {
  std::ostream& operator <<(std::ostream& stream, Expr* e){
    e->write(stream);
    return stream;
  }

  Expr::~Expr(){}

  Expr* parseAtom(const char*& b);
  static Expr* ParseBuffer(const char*& b);

  const ViewModel* Variable::Eval(ViewContext& ctx) {
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

  FilterExpr::~FilterExpr(){
    delete target;
    delete filter;
  }

  const ViewModel* FilterExpr::Eval(ViewContext& ctx) {
    const ViewModel* vm = target->Eval(ctx);
    assert(filter);
    return filter->Eval(vm, ctx);
  }

  void FilterExpr::write(std::ostream& stream){
    target->write(stream);
    assert(filter);
    stream << " | " << (*filter);
  }

  static Expr* tryParseFilter(Expr* target, const char*& b){
    if(*b != '|') 
      return target;
    b++; // Eat '|'

    Filter::Arg arg = 0;
    std::string filterName;
    auto filter = new FilterExpr();

    filter->target = target;

    while(*b == ' ') b++;
    while(isalpha(*b)) filterName += *(b++);

    if(*b == ':'){
      b++;
      arg = parseAtom(b);      
    }
    
    while(*b == ' ') b++;

    filter->filter = FilterFactory::Create(filterName, arg);
    assert(filter->filter);
    return filter; 
  }


#define cmpreturn(b, str, type)			\
  {						\
    int size = strlen(str);			\
    if( strncmp(b, str, size) == 0) {		\
      b += size; return type;			\
    }						\
  }

  static InfixOps::t parseInfixOperator(const char*& b){  
    cmpreturn(b, "==", InfixOps::EQ);
    cmpreturn(b, "!=", InfixOps::NEQ);
    cmpreturn(b, "&&", InfixOps::AND);
    cmpreturn(b, "||", InfixOps::OR);
    cmpreturn(b, "<=", InfixOps::LEQ);
    cmpreturn(b, ">=", InfixOps::GEQ);
    cmpreturn(b, ">", InfixOps::GT);
    cmpreturn(b, "<", InfixOps::LT);
    cmpreturn(b, "^", InfixOps::XOR);
    return InfixOps::NONE;
  }

  const ViewModel* InfixOperatorExpr::Eval(ViewContext& ctx){
    assert(right);
    assert(left);
    switch(op) {
    case InfixOps::EQ:  return Variant::Create( use(left->Eval(ctx)) == use(right->Eval(ctx)) ) ;
    case InfixOps::NEQ: return Variant::Create( use(left->Eval(ctx)) != use(right->Eval(ctx)) ) ;
    case InfixOps::LEQ: return Variant::Create( use(left->Eval(ctx)) <= use(right->Eval(ctx)) ) ;
    case InfixOps::GEQ: return Variant::Create( use(left->Eval(ctx)) >= use(right->Eval(ctx)) ) ;
    default: assert(false);
    }
  }

  void InfixOperatorExpr::write(std::ostream& stream){
    right->write(stream);
    stream << " ";
    switch(op){
    default: 
      stream << "??";
    }
    stream << " ";
    left->write(stream);
  }

  InfixOperatorExpr::~InfixOperatorExpr(){
    delete right;
    delete left;
  }

  const ViewModel* LiteralExpr::Eval(ViewContext& ctx){
    return &value;
  }
  void LiteralExpr::write(std::ostream& stream){
    std::string b;
    value.asString(b);
    stream << b;
  }

  static Expr* tryParseInfix(Expr* target, const char*& b){
    auto op = parseInfixOperator(b);
    if(op == InfixOps::NONE)
      return target;
    else {
      auto expr = new InfixOperatorExpr();
      expr->left = target;
      expr->right = ParseBuffer(b);
      expr->op = op;
      return expr;
    }
    return target;
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
    while(isspace(*b)) b++;

    return expr;
  }
  
  static Expr* parseLiteral(const char*& b){
    bool isString = *b == '\'' || *b == '"';
    char end = isString ? *b : 0;
    bool isFloat = false;
    std::string content; 
    if(isString) b++; // Eat the qoute

    while(*b != 0 && *b != end && (isString || isdigit(*b)) ) {
      content += *b;
      if(*b == '.'){
	assert(!isFloat);
	isFloat = true;
      }
      b++;
    }

    assert( !isString || *b == end);
    assert(content.size());
    auto expr = new LiteralExpr();

    if(isString){
      b++; // eat quote;
      expr->value = content;
    } else if(isFloat) {
      expr->value = atof(content.c_str());
    } else {
      expr->value = atoi(content.c_str());
    } // TODO: Add... boolean? And maybe object, but probably just boolean.
    while(isspace(*b)) b++;
    return expr;
  }

  inline Expr* parseAtom(const char*& b){
    while( isspace(*b) ) b++;
    if(*b == '"' || *b == '\'' || isdigit(*b))
      return parseLiteral(b);
    return parseVariable(b);
  }

  static Expr* ParseBuffer(const char*& b){
    Expr* expr = parseAtom(b);
    expr = tryParseInfix(expr, b);
    expr = tryParseFilter(expr, b);
    
    if(*b)
      std::cerr << "Warning: '" << b << "' left unparsed." << std::endl;
    return expr;    
  }

  Expr* Parse(const std::string& exp){
    const char* b = &exp[0];
    return ParseBuffer(b);
  }
}
