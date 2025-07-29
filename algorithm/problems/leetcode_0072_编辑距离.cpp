#include "common.hpp"

// 以word1[0...i]转化为word2[0...j]所需的最小编辑数为 dp[i][j]
//
// 设word1=abc，word2=adc，指针i，j分别指向末尾
//
//   word1: a b c
//              i
//   word2: a d c
//              j
//
// 当word1[i]==word2[j]时，不需要任何转换操作，因此可知
//
//   if word1[i] == word2[j] then dp[i][j] = dp[i - 1][j - 1]
//
// 令i和j分别减1后word1[i]!=word2[j]，此时分别有三种选择：
//
//   word1: a b c
//            i
//   word2: a d c
//            j
//
//   1. 插入一个字符: 在b的后面插入一个字符d后，使得该字符与word2的字符d相同，
//   此时，由于word2又完成了一个字符的匹配，因此j-1；而word1由于时向后插入，
//   因此i目前所指向的字符还未完成匹配，因此i不变
//
//   word1: a b d c
//            i
//   word2:   a d c
//            j
//
//   2. 删除一个字符: 在word1删除一个字符b后，此时任需继续匹配i-1剩下的部分，
//   而word2由于并未执行任何操作，因此j不变。
//
//   word1: a b c
//          i x
//   word2: a d c
//            j
//
//   3. 修改一个字符：由于修改的word1使得word1[i]==word2[j]，因此此时变回了字符
//   相等时的问题。
//
//               * dp[i-1][j-1]                               , word1[i]==word2[j]
//              /
//  dp[i][j] = *
//              \
//               * min(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]) + 1, word1[i]!=word2[j]

int32_t solution1(std::string word1, std::string word2) {
  std::vector mem(word1.size(), std::vector<int32_t>(word2.size(), -1));
  return [&](this const auto &dfs, int32_t i, int32_t j) -> int32_t {
    if (i < 0 && j < 0) {
      // 两个空字符串之间不需要任何转换
      // "" -> "" = 0
      return 0;
    } else if (i < 0 || j < 0) {
      // 任意一个字符串为空，转化为另一个字符串需要操作目标字符串的长度，全部插入/删除
      // abc -> "" = 3
      // "" -> abc = 3
      return i < 0 ? j + 1 : i + 1;
    }

    int32_t &operand = mem[i][j];
    if (operand != -1) {
      return operand;
    }

    if (word1[i] == word2[j]) {
      // word1: a d c
      //            i
      // word2: a b c
      //            j
      return operand = dfs(i - 1, j - 1);
    } else {
      // word1: a d b
      //            i
      // word2: a d c
      //            j
      return operand = std::min({
        // 插入
        // word1: a d b c
        //            i *
        // word2:   a d c
        //            j
        dfs(i, j - 1) + 1,
        // 删除
        // word1: a d b
        //          i *
        // word2: a d c
        //            j
        dfs(i - 1, j) + 1,
        // 替换
        // word1: a d c
        //          i
        // word2: a d c
        //          j
        dfs(i - 1, j - 1) + 1
      });
    }
  }(word1.size() - 1, word2.size() - 1);
}

int32_t solution2(std::string word1, std::string word2) {
  int32_t m = word1.size(), n = word2.size();

  std::vector dp(m + 1, std::vector<int32_t>(n + 1));
  dp[0][0] = 0;
  for (int32_t i = 1; i <= m; i++) {
    dp[i][0] = i;
  }
  for (int32_t j = 1; j <= n; j++) {
    dp[0][j] = j;
  }

  for (int32_t i = 1; i <= m; i++) {
    for (int32_t j = 1; j <= n; j++) {
      if (word1[i - 1] == word2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = std::min({
          dp[i][j - 1],
          dp[j][i - 1],
          dp[i - 1][j - 1],
        }) + 1;
      }
    }
  }

  return dp[m][n];
}
