#include "common.hpp"

// 题目: 每次只能走1步或者两步，求计算 N 级台阶总共需要多少种走法
//
// 假设有 3 级台阶，那么就拥有 3 种走法，分别是:
// 1 1 1
// 1 2
// 2 1
//
// 设跳上 n 级台阶有 f(n) 种跳法。在所有跳法中，青蛙的最后一步只有两种情况：跳上 1 级或 2 级台阶。
//  1. 当为 1 级台阶： 剩 n − 1 个台阶，此情况共有 f(n − 1) 种跳法。
//  2. 当为 2 级台阶： 剩 n − 2 个台阶，此情况共有 f(n − 2) 种跳法。
// 即 f(n) 为以上两种情况之和，即 f(n) = f(n − 1) + f(n − 2) ，以上递推性质为斐波那契数列。因此，本题可转化为 求斐波那契数列的第 n 项，区别仅在于初始值不同：
//  * 青蛙跳台阶问题：f(0) = 1, f(1) = 1, f(2) = 2 。
//  * 斐波那契数列问题：f(0) = 0, f(1) = 1, f(2) = 1 。

// 穷举法
int32_t solution1(int32_t n) {
  if (n <= 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  if (n == 2) {
    return 2;
  }

  return solution1(n - 1) + solution1(n - 2);
}

// 记忆优化法
int32_t solution2(int32_t n, std::map<int32_t, int32_t> &m) {
  if (auto it = m.find(n); it != m.end()) {
    return it->second;
  }

  int32_t sum;
  if (n <= 0) {
    return 0;
  } else if (n == 1) {
    return 1;
  } else if (n == 2) {
    return 2;
  } else {
    sum = solution2(n - 1, m) + solution2(n - 2, m);
  }

  m.emplace(n, sum);
  return sum;
}

// 动态规划
int32_t solution3(int32_t n) {
  if (n == 0) return 0;
  int32_t dp[2] = { 1, 2 };

  for (int32_t i = 3; i <= n; i++) {
    int32_t sum = dp[1] + dp[0];
    dp[0] = dp[1];
    dp[1] = sum;
  }

  return dp[1];
}

int32_t main(void) {
  std::map<int32_t, int32_t> m;

  solution1(40);
  solution2(40, m);
  solution3(40);

  return EXIT_SUCCESS;
}
