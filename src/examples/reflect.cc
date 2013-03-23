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

namespace mxcomp {
  METACLASS(Person){
    FIELDS(FIELD(age), FIELD(name), FIELD(p))
      };

  METACLASS(Pet){
    FIELDS(FIELD(name))
      };
}

int main() {
  Template::AddDirectory("/home/justin/stencet/tcs");
  
  Person person;
  person.name = "justin";
  person.age = 100;
  person.p.name = "Oliver";

  Template::ByName("display_person").render(std::cerr, person);
  return 0;
}
