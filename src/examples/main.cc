/* Copyright (C) 2012-2013 Justin Berger 
   The full license is available in the LICENSE file at the root of this project and is also available at http://opensource.org/licenses/MIT. */

#include <stencet/stencet>
using namespace stencet;
int main() {
  Template::AddDirectory("/home/justin/projects/stencet/tcs");

  Variant vm;
  vm["test"] = 123;
  vm["testb"] = false;
  vm["list"].append("A");
  vm["list"].append("B");
  vm["list"].append("C");
  vm["list"][1] = "Z";

  Template::ByName("include_test").render(std::cerr, vm);

  vm["testb"] = true;
  Template::ByName("include_test").render(std::cerr, vm);
  std::cerr << "---" << std::endl;
  Template::ByName("extendsTest").render(std::cerr, vm);
  std::cerr << "---" << std::endl;
  return 0;
}
