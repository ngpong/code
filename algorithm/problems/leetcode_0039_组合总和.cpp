#include "common.hpp"

struct Tracker {
  int32_t sum = 0;
  size_t i = 0;
  std::vector<int32_t> comb = {};
};

std::vector<std::vector<int32_t>> solution1(std::vector<int32_t> &candidates, int32_t target) {
  std::vector<std::vector<int32_t>> ans;

  size_t n = candidates.size();
  [&](this const auto &backtrack, auto &&track, int32_t i = 0) -> void {
    if (track.sum > target) {
      return;
    }
    if (track.sum == target) {
      return ans.push_back(track.comb);
    }

    for (; i < n; i++) {
      track.sum += candidates[i];
      track.comb.push_back(candidates[i]);

      backtrack(track, i);

      track.sum -= candidates[i];
      track.comb.pop_back();
    }
  }(Tracker());

  return ans;
}

std::vector<std::vector<int32_t>> solution2(std::vector<int32_t> &candidates, int32_t target) {
  std::vector<std::vector<int32_t>> ans;

  std::sort(candidates.begin(), candidates.end());

  size_t n = candidates.size();
  [&](this const auto &backtrack, auto &&track, int32_t i = 0) -> void {
    if (track.sum == target) {
      return ans.push_back(track.comb);
    }

    for (; i < n; i++) {
      if (candidates[i] + track.sum > target) {
        break;
      }

      track.sum += candidates[i];
      track.comb.push_back(candidates[i]);

      backtrack(track, i);

      track.sum -= candidates[i];
      track.comb.pop_back();
    }
  }(Tracker());

  return ans;
}
