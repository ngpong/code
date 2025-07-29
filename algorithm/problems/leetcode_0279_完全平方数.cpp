#include "common.hpp"

int32_t solution1(int32_t n) {
  std::vector<int32_t> squares;
  for (int32_t i = std::ceil(std::sqrt(n)); i > 0; i--) {
    squares.push_back(std::pow(i, 2));
  }

  std::unordered_map<int32_t, int32_t> mem;
  return [&](this const auto &dfs, int32_t n) -> int32_t {
    if (auto it = mem.find(n); it != mem.end()) {
      return it->second;
    }

    if (n == 0) {
      return 0;
    }

    int32_t count = INT32_MAX;
    for (auto &sq : squares) {
      if (n >= sq) {
        int32_t opt = dfs(n - sq);
        count = std::min(count, opt);
      }
    }

    count = count != INT32_MAX ? count + 1 : INT32_MAX;
    mem[n] = count;

    return count;
  }(n);
}

int32_t solution2(int32_t n) {
  std::vector<int32_t> squares;
  for (int32_t i = std::ceil(std::sqrt(n)); i > 0; i--) {
    squares.push_back(std::pow(i, 2));
  }

  std::vector<int32_t> dp(n + 1, INT32_MAX);
  dp[0] = 0;
  for (int32_t i = 1; i <= n; i++) {
    int32_t count = INT32_MAX;
    for (auto &sq : std::as_const(squares)) {
      if (i >= sq) {
        int32_t opt = dp[i - sq];
        count = std::min(count, opt);
      }
    }

    if (count != INT32_MAX) {
      dp[i] = count + 1;
    }
  }

  return dp[n];
}
