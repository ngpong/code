#include "common.hpp"

std::vector<std::vector<int32_t>> solution(std::vector<int32_t>& nums) {
  std::vector<std::vector<int32_t>> ans;
  ans.push_back({});

  int32_t n = nums.size();
  [&](this const auto &backtrack, auto &&track, int32_t i = 0) -> void {
    for (; i < n; i++) {
      track.push_back(nums[i]);
      ans.push_back(track);

      backtrack(track, i + 1);

      track.pop_back();
    }
  }(std::vector<int32_t>{});

  return ans;
}
