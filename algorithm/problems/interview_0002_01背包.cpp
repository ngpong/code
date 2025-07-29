#include "common.hpp"

// 有n件物品和一个最多能背重量为 capacity 的背包。
// 第i件物品的重量是weight[i]，得到的价值是value[i] 。
// 每件物品只能用一次，求解将哪些物品装入背包里物品价值总和最大。

// 举例：
// weight = { 1,  3,  4 }
// value  = { 15, 20, 30 }
// capacity = 4
// 最终答案为 35，即只能取物品 0 和 1 放入背包

// https://www.bilibili.com/video/BV1cg411g7Y6/?vd_source=e47d384d6bfaab962bea6d6b23939f99
// https://www.bilibili.com/video/BV1pY4y1J7na/

// dp[i][j] = 对于前 i 个物品，当背包容量为 j 时，可以装的最大价值就是 dp[i][j]
// 比如说dp[3][5] = 6：对于给定的一系列物品中，如果只对前3个物品进行选择，当背包容量为 5 时，可以装进去的最大价值是 6
//
// 每个物品 i 在容量 j 时有两种选择：
//  * 1. 选择当前物品放入背包：dp[i][j] = dp[i - 1][j - weights[i]] + values[i]
//  * 2. 不选当前物品放入背包：dp[i][j] = dp[i - 1][j]
// 又由于需要求的最优解，因此 dp[i][j] 为上述去最大值
//
// 在这期间要注意 weight[i] 不能大于 capacity 的问题
//
//      │  0  │  1  │  2  │  3  │  4  │
// ─────┼─────┼─────┼─────┼─────┼─────┼
//   0  │     │     │     │     │     │
// ─────┼─────┼─────┼─────┼─────┼─────┼
//   1  │     │     │     │     │     │
// ─────┼─────┼─────┼─────┼─────┼─────┼
//   2  │     │     │     │     │     │
// ─────┼─────┼─────┼─────┼─────┼─────┼
//   3  │     │     │     │     │     │
// ─────┼─────┼─────┼─────┼─────┼─────┼


int32_t solution1(std::vector<int32_t> &weights, std::vector<int32_t> &values, int32_t capacity) {
  std::vector<std::vector<int32_t>> mem(weights.size(), std::vector<int32_t>(capacity + 1, -1));
  return [&](this const auto &dfs, int32_t i, int32_t cap) -> int32_t {
    if (i < 0) {
      return 0;
    }

    int32_t &v = mem[i][cap];
    if (v != -1) {
      return v;
    }

    if (weights[i] > cap) {
      v = dfs(i - 1, cap);
    } else {
      v = std::max(dfs(i - 1, cap), dfs(i - 1, cap - weights[i]) + values[i]);
    }

    return v;
  }(weights.size() - 1, capacity);
}

int32_t solution2(std::vector<int32_t> &weights, std::vector<int32_t> &values, int32_t capacity) {
  std::vector<std::vector<int32_t>> dp(weights.size(), std::vector<int32_t>(capacity + 1, -1));
  for (int32_t i = 0; i < dp.size(); i++) {
    dp[i][0] = 0;
  }
  for (int32_t j = 0; j <= capacity; j++) {
    if (j < weights[0]) {
      dp[0][j] = 0;
    } else {
      dp[0][j] = values[0];
    }
  }

  for (int32_t i = 1; i < weights.size(); i++) {
    for (int32_t j = 1; j <= capacity; j++) {
      if (j < weights[i]) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weights[i]] + values[i]);
      }
    }
  }

  return dp[weights.size() - 1][capacity];
}
