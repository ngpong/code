#include "common.hpp"

std::vector<int32_t> solution(std::vector<int32_t> &nums, int32_t target) {
  std::vector<int32_t> res;

  int32_t i = 0, j = nums.size() - 1;
  while (i < j) {
    int32_t sum = nums[i] + nums[j];

    if (sum > target) {
      j--;
    } else if (sum < target) {
      i++;
    } else {
      res.push_back(i);
      res.push_back(j);
      break;
    }
  }

  return res;
}
