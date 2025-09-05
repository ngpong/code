#include "common.hpp"

int32_t solution1(std::vector<std::string> &strs, int32_t m, int32_t n) {
  std::vector<int32_t> cnt0(strs.size(), 0);
  std::vector<int32_t> cnt1(strs.size(), 0);
  for (int32_t i = 0; i < strs.size(); i++) {
    for (int32_t j = 0; j < strs[i].size(); j++) {
      if (strs[i][j] == '0') {
        cnt0[i]++;
      } else {
        cnt1[i]++;
      }
    }
  }

  std::vector mem(strs.size(), std::vector(m + 1, std::vector<int32_t>(n + 1, -1)));
  return [&](this const auto &dfs, int32_t i, int32_t j, int32_t k) -> int32_t {
    if (i < 0) {
      return 0;
    }

    int32_t &ans = mem[i][j][k];
    if (ans != -1) {
      return ans;
    }

    if (j < cnt0[i] || k < cnt1[i]) {
      return ans = dfs(i - 1, j, k);
    } else {
      return ans = std::max(dfs(i - 1, j, k), dfs(i - 1, j - cnt0[i], k - cnt1[i]) + 1);
    }
  }(strs.size() - 1, m, n);
}

int32_t solution2(std::vector<std::string> &strs, int32_t m, int32_t n) {
  std::vector<int32_t> cnt0(strs.size(), 0);
  std::vector<int32_t> cnt1(strs.size(), 0);
  for (int32_t i = 0; i < strs.size(); i++) {
    for (int32_t j = 0; j < strs[i].size(); j++) {
      if (strs[i][j] == '0') {
        cnt0[i]++;
      } else {
        cnt1[i]++;
      }
    }
  }

  std::vector dp(strs.size() + 1, std::vector(m + 1, std::vector<int32_t>(n + 1, 0)));
  for (int32_t i = 1; i <= strs.size(); i++) {
    int32_t __cnt0 = cnt0[i - 1];
    int32_t __cnt1 = cnt1[i - 1];
    for (int32_t j = 0; j <= m; j++) {
      for (int32_t k = 0; k <= n; k++) {
        if (j < __cnt0 || k < __cnt1) {
          dp[i][j][k] = dp[i - 1][j][k];
        } else {
          dp[i][j][k] = std::max(dp[i - 1][j][k], dp[i - 1][j - __cnt0][k - __cnt1] + 1);
        }
      }
    }
  }

  return dp[strs.size()][m][n];
}
