/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#include <stencet/stencet>
#include <mxcomp/python.h>
using namespace stencet;

struct Pet {
  std::string name;
};

struct Person {
  Pet p;
  std::string name;
  int age; 
  int getAge() const { return age; }
};

namespace mxcomp {
  METACLASS(Person){
    MEMBERS(FIELD(age), 
	    FIELD(name), 
	    FIELD(p),
	    FUNCTION(getAge));
  };

  METACLASS(Pet){
    MEMBERS(FIELD(name));
  };
}

MODULE(ReflectTest, Person, Pet);

void B_() {
  std::cerr << "AAA" << std::endl;
}

void A_() {
  return B_();
};

struct A {};
struct B : A{};
struct C {};
int main() {
  Template::AddDirectory("/home/justin/projects/stencet/tcs");
  using namespace mxcomp;

  auto t = std::make_tuple(A(), B(), C(), C(), C(), A());
  auto s = mxcomp::tuples::ofType<A>(t);
  auto tail = mxcomp::tuples::tail(t);

  auto tp = std::make_tuple('a', 'b', 'c');
  
  mxcomp::tuples::applyTuple([](char& a, char& b, char& c) -> void { std::cerr << a << b << c << std::endl;}, tp);

  Person person;
  person.name = "justin";
  person.age = 100;
  person.p.name = "Oliver";

  //  Template::ByName("display_person").render(std::cerr, person);
  return 0;
}
