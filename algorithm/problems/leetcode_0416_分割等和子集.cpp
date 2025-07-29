#include "common.hpp"

// dp[i][j]: 对于前 i 个任意元素，在背包容量为 j 的情况下，dp[i][j] 为是否能够填满整个背包
// dp[i][j] = dp[i - 1] || dp[i - 1][j - nums[i]]

bool solution1(std::vector<int32_t> &nums) {
  int32_t capacity;
  if (int32_t sum = std::reduce(nums.begin(), nums.end()); sum % 2) {
    return false;
  } else {
    capacity = sum / 2;
  }

  std::vector mem(nums.size(), std::vector<int32_t>(capacity + 1, -1));
  return [&](this const auto &dfs, int32_t i, int32_t j) -> bool {
    if (i < 0) {
      return j == 0;
    }

    int32_t &ans = mem[i][j];
    if (ans != -1) {
      return ans;
    }

    if (j < nums[i]) {
      ans = dfs(i - 1, j);
    } else {
      ans = dfs(i - 1, j) || dfs(i - 1, j - nums[i]);
    }

    return ans;
  }(nums.size() - 1, capacity);
}

bool solution2(std::vector<int32_t> &nums) {
  int32_t capacity;
  if (int32_t sum = std::reduce(nums.begin(), nums.end()); sum % 2) {
    return false;
  } else {
    capacity = sum / 2;
  }

  std::vector dp(nums.size() + 1, std::vector<int32_t>(capacity + 1));
  dp[0][0] = true;

  for (int32_t i = 1; i <= nums.size(); i++) {
    int32_t num = nums[i - 1];
    for (int32_t j = 0; j <= capacity; j++) {
      if (num > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j] || dp[i - 1][j - num];
      }
    }
  }

  return dp[nums.size()][capacity];
}
