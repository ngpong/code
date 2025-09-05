#include "common.hpp"

int32_t solution1(std::vector<int32_t> &nums, int32_t target) {
  int32_t sum = std::reduce(nums.begin(), nums.end());

  float capacity = (sum + std::abs(target)) / 2.0;
  // 如果存在小数点代表无法求出组合
  if (std::floor(capacity) != capacity) {
    return 0;
  }

  // dp[i][j]：对于前 i 个物品，装满容量为 j 的背包共有 dp[i][j] 种方案
  // dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i]]
  // 这是因为问题需要的是方案数目，而不是求最大值或者最小值。这里每个选择（选或不选）都会贡献可能的方案数，所以需要将两种情况的结果相加

  std::vector mem(nums.size(), std::vector<int32_t>(capacity + 1, -1));
  return [&](this const auto &dfs, int32_t i, int32_t j) -> int32_t {
    // 当 i < 0 时代表没有数组可以继续向下选择，
    // 此时当 j == 0 时意味着已经没有空间，
    // 另一方面也说明 n 个数我们都已经考虑好了都要做某种（变成正数或者负数）选择，
    // 因此认可这种方案，因此返回 1。
    if (i < 0) {
      return j == 0;
    }

    int32_t &count = mem[i][j];
    if (count != -1) {
      return count;
    }

    if (nums[i] > j) {
      count = dfs(i - 1, j);
    } else {
      count = dfs(i - 1, j) + dfs(i - 1, j - nums[i]);
    }

    return count;
  }(nums.size() - 1, capacity);
}

int32_t solution2(std::vector<int32_t> &nums, int32_t target) {
  int32_t sum = std::reduce(nums.begin(), nums.end());

  float capacity = (sum + std::abs(target)) / 2.0;
  if (std::floor(capacity) != capacity) {
    return 0;
  }

  std::vector dp(nums.size() + 1, std::vector<int32_t>(capacity + 1));
  dp[0][0] = 1;

  for (int32_t i = 1; i <= nums.size(); i++) {
    for (int32_t j = 0; j <= capacity; j++) {
      int32_t num = nums[i - 1];
      if (j < num) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j] + dp[i - 1][j - num];
      }
    }
  }

  return dp[nums.size()][capacity];
}
