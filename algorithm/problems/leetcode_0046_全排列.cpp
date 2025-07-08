#include "common.hpp"

std::vector<std::vector<int32_t>> solution1(std::vector<int32_t> &nums) {
  int32_t n = nums.size();

  std::vector<std::vector<int32_t>> ans;
  ans.push_back(nums);
  [&](this const auto &self, std::vector<int32_t> &nums, int32_t i) -> void {
    if (i == n - 1) {
      return;
    }

    for (int32_t j = i; j < n; ++j) {
      if (j == i) {
        self(nums, i + 1);
      } else {
        std::vector<int32_t> copy = nums;
        std::swap(copy[i], copy[j]);
        ans.push_back(copy);

        self(copy, i + 1);
      }
    }
  }(nums, 0);

  return ans;
}

std::vector<std::vector<int32_t>> solution2(std::vector<int32_t> &nums) {
  std::vector<std::vector<int32_t>> ans;

  [&](this const auto &backtrack, auto &&track) -> void {
    if (track.size() == nums.size()) {
      ans.push_back(track);
      return;
    }

    int32_t n = nums.size();
    for (int32_t i = 0; i < n; i++) {
      if (std::find(track.begin(), track.end(), nums[i]) != track.end()) {
        continue;
      }

      track.push_back(nums[i]);
      backtrack(track);
      track.pop_back();
    }
  }(std::vector<int32_t>{});

  return ans;
}

std::vector<std::vector<int32_t>> solution3(std::vector<int32_t> &nums) {
  std::vector<std::vector<int32_t>> ans;

  int32_t n = nums.size();
  [&](this const auto &backtrack, std::vector<int32_t> &nums, int32_t pos = 0) -> void {
    if (pos == n - 1) {
      ans.push_back(nums);
      return;
    }

    for (int32_t i = pos; i < n; i++) {
      std::swap(nums[i], nums[pos]);
      backtrack(nums, pos + 1);
      std::swap(nums[i], nums[pos]);
    }
  }(nums);

  return ans;
}
