#include <stencet/stencet>
using namespace stencet;
int main() {
  Template::AddDirectory("/home/justin/stencet/tcs");

  Variant vm;
  vm["test"] = 123;
  vm["testb"] = false;
  vm["list"][-1] = "A";
  vm["list"][-1] = "B";
  vm["list"][-1] = "C";
  vm["list"][1] = "Z";

  Template::ByName("include_test").render(std::cerr, vm);

  vm["testb"] = true;
  Template::ByName("include_test").render(std::cerr, vm);
  std::cerr << "---" << std::endl;
  Template::ByName("extendsTest").render(std::cerr, vm);
  std::cerr << "---" << std::endl;
  return 0;
}
