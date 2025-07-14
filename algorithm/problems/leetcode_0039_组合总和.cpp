#include "common.hpp"

struct Tracker {
  int32_t sum = 0;
  size_t i = 0;
  std::vector<int32_t> comb = {};
};

std::vector<std::vector<int32_t>> solution(std::vector<int32_t> &candidates, int32_t target) {
  std::vector<std::vector<int32_t>> ans;

  size_t n = candidates.size();
  [&](this const auto &backtrack, auto &&track) -> void {
    if (track.sum > target) {
      return;
    }
    if (track.sum == target) {
      return ans.push_back(track.comb);
    }

    for (size_t i = track.i; i < n; i++) {
      track.sum += candidates[i];
      track.comb.push_back(candidates[i]);
      track.i = i;

      backtrack(track);

      track.sum -= candidates[i];
      track.comb.pop_back();
      track.i = i;
    }

    for (auto &num : std::as_const(candidates)) {
    }
  }(Tracker());

  return ans;
}
