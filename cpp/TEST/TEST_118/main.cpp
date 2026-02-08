#include <iostream>

class Foo {
public:
  bool _val0;
  int32_t _val1;
  std::string _val2;
};

int32_t main (int32_t argc, char *argv[]) {
  Foo f;
  f._val0 = false;
  f._val1 = 1024;
  f._val2 = "hello,world";

  printf("%p\n", &f);
  printf("%p\n", &f._val0);
  printf("%p\n", &f._val1);
  printf("%p\n", &f._val2);

  std::cout << f._val0 << std::endl;
  std::cout << f._val1 << std::endl;
  std::cout << f._val2 << std::endl;

  printf("%p\n", new (&f._val0) bool(true));
  printf("%p\n", new (&f._val1) int32_t(256));
  printf("%p\n", new (&f._val2) std::string("changed"));

  std::cout << f._val0 << std::endl;
  std::cout << f._val1 << std::endl;
  std::cout << f._val2 << std::endl;

  return 0;
}
