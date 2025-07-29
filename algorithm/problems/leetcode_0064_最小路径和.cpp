#include "common.hpp"

// 走到(i, j)的所有可能路径总和的最小价值为dp[i][j]
//
// dp[i][j] = min(dp[i - 1][j], dp[i][j - 1])
//
// 要注意边界的处理问题

int32_t solution1(std::vector<std::vector<int32_t>> &grid) {
  int32_t m = grid.size() - 1;
  int32_t n = grid[0].size() - 1;

  std::vector mem(m + 1, std::vector<int32_t>(n + 1, -1));
  return [&](this const auto &dfs, int32_t i, int32_t j) -> int32_t {
    if (i == 0 && j == 0) {
      return grid[0][0];
    }

    int32_t &acc = mem[i][j];
    if (acc != -1) {
      return acc;
    }

    if (i == 0) {
      return acc = dfs(i, j - 1) + grid[i][j];
    } else if (j == 0) {
      return acc = dfs(i - 1, j) + grid[i][j];
    } else {
      return acc = std::min(dfs(i - 1, j), dfs(i, j - 1)) + grid[i][j];
    }
  }(m, n);
}

int32_t solution2(std::vector<std::vector<int32_t>> &grid) {
  int32_t m = grid.size();
  int32_t n = grid[0].size();

  std::vector dp(m + 1, std::vector<int32_t>(n + 1, INT32_MAX));
  dp[0][1] = 0;
  for (int32_t i = 1; i <= m; i++) {
    for (int32_t j = 1; j <= n; j++) {
      dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + grid[i - 1][j - 1] ;
    }
  }

  return dp[m][n];
}
