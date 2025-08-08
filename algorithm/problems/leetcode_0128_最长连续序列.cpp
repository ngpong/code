#include "common.hpp"

int32_t solution1(std::vector<int32_t> &nums) {
  std::unordered_set<int32_t> us;
  for (auto &num : std::as_const(nums)) {
    us.insert(num);
  }

  int32_t longest = 0;
  for (auto &num : std::as_const(us)) {
    if (!us.count(num - 1)) {
      int32_t len = 1;
      for (int32_t x = num + 1; us.count(x); x++) {
        len++;
      }

      longest = std::max(longest, len);
    }
  }

  return longest;
}
