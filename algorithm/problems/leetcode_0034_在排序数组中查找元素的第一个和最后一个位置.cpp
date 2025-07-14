#include "common.hpp"

int32_t upper_bound(std::vector<int32_t> &nums, int32_t target) {
  int32_t lt = 0, gt = nums.size() - 1;
  while (lt <= gt) {
    int32_t mid = (lt + gt) >> 1;
    if (target < nums[mid]) {
      gt = mid - 1;
    } else if (target >= nums[mid]) {
      lt = mid + 1;
    }
  }

  return lt;
}

int32_t lower_bound(std::vector<int32_t> &nums, int32_t target) {
  int32_t lt = 0, gt = nums.size() - 1;
  while (lt <= gt) {
    int32_t mid = (lt + gt) >> 1;
    if (target <= nums[mid]) {
      gt = mid - 1;
    } else if (target > nums[mid]) {
      lt = mid + 1;
    }
  }

  return lt >= nums.size() || nums[lt] != target ? -1 : lt;
}

std::vector<int32_t> searchRange(std::vector<int32_t> &nums, int32_t target) {
  std::vector<int32_t> ans = { -1, -1 };
  if (nums.empty()) {
    return ans;
  }

  int32_t lb = lower_bound(nums, target);
  if (lb < 0) {
    return ans;
  }
  ans[0] = lb;

  int32_t ub = upper_bound(nums, target);
  ans[1] = ub - 1;

  return ans;
}
