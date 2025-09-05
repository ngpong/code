#include "common.hpp"

int32_t solution1(std::vector<int32_t> &stones) {
  int32_t sum = std::reduce(stones.begin(), stones.end());
  int32_t capacity = sum / 2;

  std::vector mem(stones.size(), std::vector<int32_t>(capacity + 1, -1));
  int32_t ans = [&](this const auto &dfs, int32_t i, int32_t j) -> int32_t {
    if (i < 0) {
      return 0;
    }

    int32_t &v = mem[i][j];
    if (v != -1) {
      return v;
    }

    if (j < stones[i]) {
      v = dfs(i - 1, j);
    } else {
      v = std::max(dfs(i - 1, j), dfs(i - 1, j - stones[i]) + stones[i]);
    }

    return v;
  }(stones.size() - 1, capacity);

  return sum - ans * 2;
}

int32_t solution2(std::vector<int32_t> &stones) {
  int32_t sum = std::reduce(stones.begin(), stones.end());
  int32_t capacity = sum / 2;

  std::vector dp(stones.size() + 1, std::vector<int32_t>(capacity + 1, 0));
  for (int32_t i = 1; i <= stones.size(); i++) {
    int32_t w = stones[i - 1];
    for (int32_t j = 0; j <= capacity; j++) {
      if (j < w) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - w] + w);
      }
    }
  }

  return sum - dp[stones.size()][capacity] * 2;
}
