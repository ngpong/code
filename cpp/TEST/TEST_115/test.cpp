#include <iostream>

#include "test.hpp"

void bar() {
  std::cout << "test.cpp::bar" << std::endl;
  NG::val = 256;
  std::cout << NG::val << std::endl;
}
