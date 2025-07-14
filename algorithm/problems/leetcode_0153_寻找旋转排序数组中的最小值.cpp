#include "common.hpp"

int32_t solution(std::vector<int32_t> &nums) {
  int32_t min = nums[0];

  int32_t lt = 0, gt = nums.size() - 1;
  while (lt <= gt) {
    int32_t mid = (lt + gt) >> 1;

    if (nums[lt] <= nums[mid]) {
      min = std::min(min, nums[lt]);
      lt = mid + 1;
    } else {
      min = std::min(min, nums[mid + 1]);
      gt = mid;
    }
  }

  return min;
}
