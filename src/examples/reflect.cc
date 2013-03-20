#include <stencet/stencet>
using namespace stencet;

struct Pet {
  std::string name;
};

struct Person {
  Pet p;
  std::string name;
  int age; 
};


template<>
struct MetaClass_<Person> {
  static auto fields() 
    STATIC_RETURN(make_fields(make_field("age", &Person::age),
			      make_field("name", &Person::name),
			      make_field("p", &Person::p)
			      ));
};

template<>
struct MetaClass_<Pet> {
  static auto fields() 
    STATIC_RETURN(make_fields(make_field("name", &Pet::name)
			      ));
};


int main() {
  Template::AddDirectory("/home/justin/stencet/tcs");
  
  Person person;
  person.name = "justin";
  person.age = 100;
  person.p.name = "Oliver";

  Template::ByName("display_person").render(std::cerr, person);
  return 0;
}
