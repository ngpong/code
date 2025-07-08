#include "common.hpp"

std::vector<std::vector<int32_t>> solution(std::vector<int32_t> &nums) {

}

int32_t main(int32_t argc, char *argv[]) {
  std::vector<int32_t> v = { 1, 2, 3, 4, 5 };
  std::cout << v << std::endl;

  auto i = v.begin();
  auto j = v.begin() + 1;

  std::vector<int32_t> v1(i, j);
  std::cout << v1 << std::endl;

  std::vector<int32_t> v2(i, j + 1);
  std::cout << v2 << std::endl;

  std::vector<int32_t> v3(i, j + 2);
  std::cout << v3 << std::endl;


  std::vector<int32_t> v4(i, j + 4);
  std::cout << v4 << std::endl;

  std::cout << ((j + 4) == v.end()) << std::endl;
}
