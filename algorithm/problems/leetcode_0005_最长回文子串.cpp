#include "common.hpp"

// dp[i][j]: 字符串区间 i...j 是否为回文串
//
// 假设给定一个回文串
//   abcba
//   ↑   ↑
//   i   j
// 当 s[i] == s[j] 时，还需要依赖于 s[i + 1] == [j - 1]。
// 由于 dp 数组的定义中，状态 i 和 j 分别表示区间的左右边界，
// 因此可知 dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1]
//
// 当 i == j 时，则为一个字符，此时一个字符本身也是回文串。
// 为了表示正确的区间，i 必须要小于 j。
// 因此可知我们只需要遍历二维状态容器的左下/右上半的部分即可。
//
//      │  0  │  1  │  2  │  3  │  4  │
// ─────┼─────┼─────┼─────┼─────┼─────┤
//   0  │  o  │     │     │     │     │
// ─────┼─────┼─────┼─────┼─────┼─────┤
//   1  │  o  │  o  │     │     │     │
// ─────┼─────┼─────┼─────┼─────┼─────┤
//   2  │  o  │  o  │  o  │     │     │
// ─────┼─────┼─────┼─────┼─────┼─────┤
//   3  │  o  │  o  │  o  │  o  │     │
// ─────┼─────┼─────┼─────┼─────┼─────┤
//   4  │  o  │  o  │  o  │  o  │  o  │
// ─────┴─────┴─────┴─────┴─────┴─────┘

std::string solution1(std::string s) {
  int32_t n = s.size();

  std::vector mem(n, std::vector<int32_t>(n, -1));
  auto is_palindrome = [&](this const auto &dfs, int32_t i, int32_t j) -> bool {
    if (i > j) {
      return true;
    }

    if (i == j) {
      return true;
    }

    int32_t &ans = mem[i][j];
    if (ans != -1) {
      return ans;
    }

    return ans = (s[i] == s[j]) && dfs(i + 1, j - 1);
  };

  auto l = s.begin(), r = s.begin() + 1; // 对角线的部分
  for (int32_t i = 0; i < n - 1; i++) {
    for (int32_t j = i + 1; j < n; j++) {
      if (!is_palindrome(i, j)) {
        continue;
      }

      if (j - i + 1 > std::distance(l, r)) {
        l = s.begin() + i;
        r = s.begin() + j + 1;
      }
    }
  }

  return std::string(l, r);
}

std::string solution2(std::string s) {
  int32_t n = s.size();

  // dp数组初始化对角线和左下半的部分
  //
  //      │  0  │  1  │  2  │  3  │  4  │
  // ─────┼─────┼─────┼─────┼─────┼─────┤
  //   0  │  o  │     │     │     │     │
  // ─────┼─────┼─────┼─────┼─────┼─────┤
  //   1  │  o  │  o  │     │     │     │
  // ─────┼─────┼─────┼─────┼─────┼─────┤
  //   2  │  o  │  o  │  o  │     │     │
  // ─────┼─────┼─────┼─────┼─────┼─────┤
  //   3  │  o  │  o  │  o  │  o  │     │
  // ─────┼─────┼─────┼─────┼─────┼─────┤
  //   4  │  o  │  o  │  o  │  o  │  o  │
  // ─────┴─────┴─────┴─────┴─────┴─────┘
  std::vector dp(n, std::vector<bool>(n, false));
  for (int32_t i = 0; i < n; i++) {
    for (int32_t j = 0; j <= i; j++) {
      dp[i][j] = true;
    }
  }

  auto l = std::begin(s), r = std::begin(s) + 1; // 对角线的部分
  for (int32_t layer = 1; layer < n; layer++) {
    for (int32_t i = 0; i < n - layer; i++) {
      int32_t j = i + layer;

      dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];

      if (dp[i][j] && j - i + 1 > std::distance(l, r)) {
        l = std::begin(s) + i;
        r = std::begin(s) + j + 1;
      }
    }
  }

  return std::string(l, r);
}
