#include "common.hpp"

int32_t solution1(std::vector<int32_t> &nums) {
  int32_t max = INT32_MIN;

  size_t n = nums.size();
  for (size_t i = 0; i < n; i++) {
    for (size_t j = i; j < n; j++) {
      size_t start = i;
      size_t ended = j;

      int32_t sum = 0;
      while (start <= ended) {
        sum += nums[start];
        max = std::max(sum, max);

        start++;
      }
    }
  }

  return max;
}

int32_t solution2(std::vector<int32_t> &nums) {
  std::unordered_map<int32_t, int32_t> mem;
  std::function<int32_t(int32_t)> dfs = [&](int32_t i) -> int32_t {
    if (i == 0) {
      return nums[0];
    }

    if (auto it = mem.find(i); it != mem.end()) {
      return it->second;
    }

    int32_t sum = std::max(nums[i], dfs(i - 1) + nums[i]);
    mem[i] = sum;

    return sum;
  };

  int32_t sum = INT32_MIN;
  for (int32_t i = nums.size() - 1; i >= 0; i--) {
    sum = std::max(sum, dfs(i));
  }

  return sum;
}

int32_t solution(std::vector<int32_t> &nums) {
  std::vector<int32_t> dp(nums.size());
  dp[0] = nums[0];

  int32_t maxsum = dp[0];
  for (int32_t i = 1; i < nums.size(); i++) {
    dp[i] = std::max(dp[i] - 1 + nums[i], nums[i]);
    maxsum = std::max(dp[i], maxsum);
  }

  return maxsum;
}
