#include "common.hpp"

std::unordered_map<int32_t, int32_t> mem;
int32_t dfs(std::vector<int> &nums, int32_t k) {
  if (auto it = mem.find(k); it != mem.end()) {
    return it->second;
  }

  int32_t count = 0;
  for (int32_t i = k - 1; i >= 0; i--) {
    if (nums[i] < nums[k]) {
      count = std::max(count, dfs(nums, i));
    }
  }

  count += 1;
  mem[k] = count;

  return count;
}
int32_t solution1(std::vector<int32_t> &nums) {
  int32_t count = 0;
  for (int32_t k = nums.size() - 1; k >= 0; k--) {
    count = std::max(count, dfs(nums, k));
  }

  return count;
}

int32_t solution2(std::vector<int32_t> &nums) {
  int32_t ans = 0;

  std::vector<int32_t> dp(nums.size(), 0);
  for (int32_t i = 0; i < nums.size(); i++) {
    int32_t count = 0;
    for (int32_t j = 0; j <= i; j++) {
      if (nums[j] < nums[i]) {
        count = std::max(count, dp[j]);
      }
    }
    dp[i] = ++count;

    ans = std::max(ans, dp[i]);
  }

  return ans;
}
