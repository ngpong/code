#include "common.hpp"

std::vector<int32_t> solution(std::vector<int32_t>& nums) {
  int32_t n = nums.size();

  std::vector<int32_t> prefix(n);
  prefix[0] = 1;
  for (int32_t i = 1; i < n; i++) {
    prefix[i] = nums[i - 1] * prefix[i - 1];
  }

  std::vector<int32_t> suffix(n);
  suffix[n - 1] = 1;
  for (int32_t i = n - 2; i >= 0; i--) {
    suffix[i] = nums[i + 1] * suffix[i + 1];
  }

  std::vector<int32_t> ans(n);
  for (int32_t i = 0; i < n; i++) {
    ans[i] = prefix[i] * suffix[i];
  }

  return ans;
}
