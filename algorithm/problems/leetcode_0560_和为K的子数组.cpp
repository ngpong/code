#include "common.hpp"

int32_t solution(std::vector<int32_t> &nums, int32_t k) {
  std::vector<int32_t> s(nums.size() + 1);
  for (size_t i = 0; i < nums.size(); i++) {
    s[i + 1] = s[i] + nums[i];
  }

  int32_t ans = 0;

  std::unordered_map<int32_t, int32_t> counter;
  for (size_t i = 0; i < s.size(); i++) {
    int32_t sj = s[i];
    if (auto it = counter.find(sj - k); it != counter.end()) {
      ans += it->second;
    }
    counter[sj]++;
  }

  return ans;
}
