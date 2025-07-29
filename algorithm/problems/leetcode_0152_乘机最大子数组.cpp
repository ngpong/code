#include "common.hpp"

int32_t solution1(std::vector<int32_t> &nums) {
  struct Product {
    int32_t max;
    int32_t min;
  };

  std::unordered_map<int32_t, Product> mem(nums.size());
  mem[0] = { nums[0], nums[0] };
  std::function<Product(int32_t)> dfs = [&](int32_t i) -> Product {
    if (auto it = mem.find(i); it != mem.end()) {
      return it->second;
    }

    Product pd0 = dfs(i - 1);
    Product pd1 = {
      std::max({ pd0.max * nums[i], pd0.min * nums[i], nums[i] }),
      std::min({ pd0.max * nums[i], pd0.min * nums[i], nums[i] })
    };
    mem[i] = pd1;

    return pd1;
  };

  int32_t max = nums[0];
  for (int32_t i = nums.size() - 1; i >= 0; i--) {
    max = std::max(dfs(i).max, max);
  }

  return max;
}

int32_t solution2(std::vector<int32_t> &nums) {
  struct Product {
    int32_t max;
    int32_t min;
  };

  std::vector<Product> dp(nums.size());
  dp[0] = { nums[0], nums[0] };

  int32_t ans = nums[0];
  for (int32_t i = 1; i < nums.size(); i++) {
    dp[i].max = std::max({ dp[i - 1].max * nums[i], dp[i - 1].min * nums[i], nums[i] });
    dp[i].min = std::min({ dp[i - 1].max * nums[i], dp[i - 1].min * nums[i], nums[i] });
    ans = std::max(dp[i].max, ans);
  }

  return ans;
}
