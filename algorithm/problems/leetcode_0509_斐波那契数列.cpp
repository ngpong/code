#include "common.hpp"

// 自顶向下的递归
int32_t fibonacci1(int32_t n) {
  if (n <= 2) return n == 0 ? 0 : 1;
  return fibonacci1(n - 1) + fibonacci1(n - 2);
}

int32_t fibonacci2(int32_t n, std::map<int32_t, int32_t>& m) {
  if (auto it = m.find(n); it != m.end()) {
    return it->second;
  }

  int32_t sum;
  if (n == 0) {
    sum = 0;
  } else if (n <= 2) {
    sum = 1;
  } else {
    sum = fibonacci2(n - 1, m) + fibonacci2(n - 2, m);
  }
  m[n] = sum;

  return sum;
}

int32_t fibonacci3(int32_t n) {
  if (n == 0) return 0;
  int32_t dp[2] = { 1, 1 };

  for (int32_t i = 3; i <= n; i++) {
    int32_t sum = dp[0] + dp[1];
    dp[0] = dp[1];
    dp[1] = sum;
  }

  return dp[n];
}

int main(void) {
  foo_recursion();
  foo_unrecursion();

  return EXIT_SUCCESS;
}
