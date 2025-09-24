#include "boost/pfr/core_name.hpp"
#include <boost/pfr.hpp>
#include <iostream>
#include <string>

struct Person {
  int age;
  std::string name;
  double salary;
};

int main() {
  Person p{30, "Alice", 65000.5};

  // Print fields using Boost.PFR
  boost::pfr::for_each_field(p, [](const auto &field, std::size_t index) {
    std::cout << "Field " << index << ": " << field << "\n";
  });

  boost::pfr::for_each_field_with_name(p, [](auto fieldname, auto value) {
    std::cout << fieldname << ": " << value << "\n";
  });

  // Access by index
  std::cout << "Name field only: " << boost::pfr::get<1>(p) << "\n";

  return 0;
}