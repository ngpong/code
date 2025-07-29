#include "common.hpp"

// 由于每一回合前进会改变坐标点(i,j)，因此可以设定坐标点即为可改变的状态，
// 因此可定义dp数组为：能够到达节点[i, j]的所有路径为dp[i][j]
//
// 最终只能由上或左的方向到达，那么要求的抵达终点时的所有路径就依赖于终点的上边和左边的节点。
// 因此 dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
//
// 因为左上角的节点是必定会经过，因此初始化 dp[0][0] = 1

int32_t solution1(int32_t m, int32_t n) {
  std::vector mem(m + 1, std::vector<int32_t>(n + 1, -1));
  return [&](this const auto &dfs, int32_t i, int32_t j) -> int32_t {
    int32_t ans = mem[i][j];
    if (ans != -1) {
      return ans;
    }

    if (i <= 0 || j <= 0) {
      return ans = 0;
    } else if (i == 1 && j == 1) {
      return ans = 1;
    } else {
      return ans = dfs(i - 1, j) + dfs(i, j - 1);
    }
  }(m, n);
}

int32_t solution2(int32_t m, int32_t n) {
  std::vector dp(m + 1, std::vector<int32_t>(n + 1, 0x0));
  dp[1][0] = 1;

  for (int32_t i = 1; i <= m; i++) {
    for (int32_t j = 1; j <= n; j++) {
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
  }

  return dp[m][n];
}
