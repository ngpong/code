#include "common.hpp"

int32_t solution1(std::vector<int32_t> &nums, int32_t k) {
  std::vector<int32_t> S(nums.size() + 1);
  for (size_t i = 0; i < nums.size(); i++) {
    S[i + 1] = S[i] + nums[i];
  }

  int32_t ans = 0;

  std::unordered_map<int32_t, int32_t> counter;
  for (size_t i = 0; i < S.size(); i++) {
    int32_t Sj = S[i];
    if (auto it = counter.find(Sj - k); it != counter.end()) {
      ans += it->second;
    }
    counter[Sj]++;
  }

  return ans;
}

int32_t solution2(std::vector<int32_t> &nums, int32_t k) {
  int32_t ans = 0;

  int32_t S = 0;
  std::unordered_map<int32_t, int32_t> counter = { { 0, 1} };
  for (size_t i = 0; i < nums.size(); i++) {
    S = S += nums[i];
    if (auto it = counter.find(S - k); it != counter.end()) {
      ans += it->second;
    }
    counter[S]++;
  }

  return ans;
}
