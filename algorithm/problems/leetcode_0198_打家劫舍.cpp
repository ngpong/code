#include "common.hpp"

int32_t solution1(std::vector<int32_t> &nums) {
  std::unordered_map<int32_t, int32_t> map;
  return [&](this const auto &rob2, int32_t n) -> int32_t {
    // 剪枝优化减少重复计算
    if (map.count(n)) {
      return map[n];
    }

    if (n < 0) {
      return 0;
    }

    // 剩下最后一间房时，为了保证最大劫掠收益，所以一定要偷
    if (n == 0) {
      return nums[0];
    }

    // 如果房间 n 要偷，那么总收益则为前 n - 2 间房的总收益加上当前房间的收益
    int32_t take = rob2(n - 2) + nums[n];
    // 如果房间 n 不偷，那么总收益则为前 n - 1 间房的总收益
    int32_t skip = rob2(n - 1);

    // 到底是偷当前房间划算还是不偷当前房间划算？
    int32_t amount = std::max(take, skip);
    map[n] = amount;

    return amount;
  }(nums.size() - 1);
}

int32_t solution(std::vector<int32_t> &nums) {
 int32_t n = nums.size();
  if (n == 1) {
    return nums[0];
  }

  std::vector<int32_t> dp(n, 0);      // 考虑从起始坐标到下标 i，dp[i] 则为偷到的最大金额
  dp[0] = nums[0];                    // 只有一间房时，保证最大收益一定要偷
  dp[1] = std::max(nums[0], nums[1]); // 只有两间房时，我们只能偷其中一间，因此取最大值

  for (int32_t i = 2; i < n; i++) {
    // 如果房间 n 要偷，那么总收益则为前 n - 2 间房的总收益加上当前房间的收益
    int32_t take = dp[i - 2] + nums[i];
    // 如果房间 n 不偷，那么总收益则为前 n - 1 间房的总收益
    int32_t skip = dp[i - 1];

    // 到底是偷当前房间划算还是不偷当前房间划算？
    dp[i] = std::max(take, skip);
  }

  return dp[n - 1];
}
