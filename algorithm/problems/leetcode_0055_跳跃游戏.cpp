#include "common.hpp"

bool solution(std::vector<int32_t> &nums) {
  int32_t cover = 1;

  auto it = nums.begin();
  for (; cover > 0 && it != nums.end(); cover--) {
    if (int32_t newcover = *it + 1; newcover > cover) {
      cover = newcover;
    }

    std::advance(it, 1);
  }

  return it == nums.end();
}
