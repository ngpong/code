#include "common.hpp"

int32_t solution(std::vector<int32_t>& nums, int32_t target) {
  int32_t lt = 0, gt = nums.size() - 1;
  while (lt <= gt) {
    int32_t mid = (lt + gt) >> 1;

    if (nums[mid] == target) {
      return mid;
    } else if (nums[lt] <= nums[mid]) {
      if (nums[lt] <= target && target < nums[mid]) {
        gt = mid - 1;
      } else {
        lt = mid + 1;
      }
    } else if (nums[mid + 1] <= nums[gt]) {
      if (nums[mid + 1] <= target && target <= nums[gt]) {
        lt = mid + 1;
      } else {
        gt = mid - 1;
      }
    }
  }

  return -1;
}
