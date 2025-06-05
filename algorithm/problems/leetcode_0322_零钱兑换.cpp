#include "common.hpp"

// 假设我有3种类型的硬币，分别为 2元、5元、7元，问: 最少使用多少个硬币可以拼出 27 元
//
// 分析得到最优子问题为:
//  最少使用多少个硬币可以拼出 27 - a_k 元
// 这里，a_k 则为所提供的三种类型的硬币中的一种，因为它仅能取这三种情况，那么当我们对该最优子问题进行划分，并取得最小值，则为所提供的公式:
//  f(x) = min{ f(x - a_2) + 1, f(x - a_5) + 1, f(x - a_7) + 1 }
// 在这里，+1 的目的是为了加上减去的 a_k
//
// 代码实现中稍微优化了以下，即原题所提供的恒定的币种改为 k 种币种

// 穷举法
int32_t solution1(int32_t amount, std::vector<int32_t> &coins) {
  if (amount == 0) {
    return 0;
  }

  int32_t count = INT32_MAX;
  for(auto &coin : coins) {
    if (amount >= coin) {
      int32_t opt = solution1(amount - coin, coins);
      count = std::min(count, opt);
    }
  }

  return count != INT32_MAX ? count + 1 : INT32_MAX;
}

// 自顶向下记忆优化递归解法
int32_t solution2(int32_t amount, std::vector<int32_t> &coins, std::map<int32_t, int32_t> &m) {
  if (auto it = m.find(amount); it != m.end()) {
    return it->second;
  }

  if (amount == 0) {
    return 0;
  }

  int32_t count = INT32_MAX;
  for(auto &coin : coins) {
    if (amount >= coin) {
      int32_t opt = solution2(amount - coin, coins, m);
      count = std::min(count, opt);
    }
  }

  count = count != INT32_MAX ? count + 1 : INT32_MAX;
  m[amount] = count;

  return count;
}

// 自底向上动态递归解法
int32_t solution3(int32_t amount, std::vector<int32_t> &coins) {
  std::vector<int32_t> dp(amount + 1, INT32_MAX);
  dp[0] = 0;

  for (int32_t i = 1; i <= amount; i++) {
    for(auto &coin : coins) {
      if (coin <= i) {
        int32_t opt = dp[i - coin];
        dp[i] = std::min(dp[i], opt == INT32_MAX ? INT32_MAX : opt + 1);
      }
    }
  }

  return dp[amount];
}

int main(void) {
  return EXIT_SUCCESS;
}
