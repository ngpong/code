#include "common.hpp"

std::vector<int32_t> solution(std::vector<int32_t> &nums1, std::vector<int32_t> &nums2) {
  std::unordered_set<int32_t> hash(nums1.begin(), nums1.end());

  std::vector<int32_t> ans;
  for (auto &num : std::as_const(nums2)) {
    if (hash.erase(num)) {
      ans.push_back(num);
    }
  }

  return ans;
}
