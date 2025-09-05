#include "common.hpp"

// dp[i][j]: 对于左端点 cuts[i] 和右端点 cuts[j] 的棍子，使用 cuts[i+1...j-1] 的切法将棍子全部切开的最小成本

int32_t solution1(int32_t n, std::vector<int32_t> &cuts) {
  cuts.push_back(0);
  cuts.push_back(n);
  std::sort(cuts.begin(), cuts.end());

  std::vector mem(cuts.size(), std::vector<int32_t>(cuts.size(), -1));
  return [&](this const auto &dfs, int32_t i, int32_t j) -> int32_t {
    if (j - i <= 1) {
      return 0;
    }

    int32_t &ans = mem[i][j];
    if (ans != -1) {
      return ans;
    }

    ans = INT32_MAX;
    for (int32_t k = i + 1; k < j; k++) {
      ans = std::min(ans, (dfs(i, k) + dfs(k, j)) + (cuts[j] - cuts[i]));
    }

    return ans;
  }(0, cuts.size() - 1);
}

int32_t solution2(int32_t n, std::vector<int32_t> &cuts) {
  cuts.push_back(0);
  cuts.push_back(n);
  std::sort(cuts.begin(), cuts.end());

  int32_t m = cuts.size();
  std::vector<std::vector<int32_t>> f(m, std::vector<int32_t>(m));
  for (int32_t i = m - 3; i >= 0; i--) {
    for (int32_t j = i + 2; j < m; j++) {
      int32_t res = INT_MAX;
      for (int32_t k = i + 1; k < j; k++) {
        res = std::min(res, f[i][k] + f[k][j]);
      }
      f[i][j] = res + cuts[j] - cuts[i];
    }
  }
  return f[0][m - 1];
}
