#include "common.hpp"

int32_t solution1(std::vector<int32_t> &nums) {
  std::vector<int32_t> mem(nums.size(), -1);
  auto dfs = [&](this const auto &dfs, int32_t i) -> int32_t {
    if (mem[i] != -1) {
      return mem[i];
    }

    int32_t len = 0;
    for (int32_t j = i - 1; j >= 0; j--) {
      if (nums[j] < nums[i]) {
        len = std::max(len, dfs(j));
      }
    }

    mem[i] = ++len;

    return len;
  };

  int32_t len = 0;
  for (int32_t i = nums.size() - 1; i >= 0; i--) {
    len = std::max(len, dfs(i));
  }

  return len;
}

int32_t solution2(std::vector<int32_t> &nums) {
  int32_t ans = 0;

  std::vector<int32_t> dp(nums.size(), 0);
  for (int32_t i = 0; i < nums.size(); i++) {
    int32_t len = 0;
    for (int32_t j = 0; j < i; j++) {
      if (nums[j] < nums[i]) {
        len = std::max(len, dp[j]);
      }
    }
    dp[i] = ++len;

    ans = std::max(ans, len);
  }

  return ans;
}
