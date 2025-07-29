#include "common.hpp"

int32_t solution1(std::string text1, std::string text2) {
  // https://leetcode.cn/problems/longest-common-subsequence/solutions/67460/dong-tai-gui-hua-zhi-zui-chang-gong-gong-zi-xu-lie/?envType=study-plan-v2&envId=top-100-liked
  //
  // 对于 text1[0...i]，与 text2[0...j]，两个字符串的最长公共序列的长度为 dp[i][j]
  //
  // 我们可以向后开始逐个对比两个字符串的逐个字符
  //  * 如果字符相同，为了求得最长序列我们需要继续向后遍历，因此 dp[i][j] = dp[i - 1][j - 1]
  //  * 如果字符不同，此时有两种选择，固定任意一方另一方继续向后遍历以查找是否相同，因此 dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])

  std::vector mem(text1.size(), std::vector<int32_t>(text2.size(), -1));

  return [&](this const auto &dfs, int32_t i, int32_t j) -> int32_t {
    if (i < 0 || j < 0) {
      return 0;
    }

    int32_t &len = mem[i][j];
    if (len != -1) {
      return len;
    }

    if (text1[i] == text2[j]) {
      return len = dfs(i - 1, j - 1) + 1;
    } else {
      return len = std::max(dfs(i - 1, j), dfs(i, j - 1));
    }
  }(text1.size() - 1, text2.size() - 1);
}

int32_t solution2(std::string text1, std::string text2) {
  int32_t m = text1.size() + 1;
  int32_t n = text2.size() + 1;

  std::vector dp(m, std::vector<int32_t>(n, 0));
  for (int32_t i = 1; i < m; i++) {
    for (int32_t j = 1; j < n; j++) {
      if (text1[i - 1] == text2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1] + 1;
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  return dp[m - 1][n - 1];
}
