#include <iostream>
#include <set>

class Base {
public:
  Base() {}
  int32_t _val;
  std::string _str;
};

template<typename T>
void foo(Base &b, T Base::*_off) {
  std::cout << b.*_off << std::endl;
}

int32_t main (int32_t argc, char *argv[]) {
  int Base::*_valPtr = &Base::_val;
  std::string Base::*_strPtr = &Base::_str;

  Base b;
  b.*_valPtr = 10;
  b.*_strPtr = "1024";

  foo(b, _valPtr);
  foo(b, _strPtr);
  // std::cout << b._val << std::endl;
  // std::cout << b.*_valPtr << std::endl;
  // std::cout << b._str << std::endl;
  // std::cout << b.*_strPtr << std::endl;
  
  int i = 10;
  int *ptr = new (&i) int(0x400);
  printf("%p\n", &i);
  printf("%p\n", ptr);

  std::cout << i << std::endl;
  std::cout << *ptr << std::endl;

  return 0;
}
