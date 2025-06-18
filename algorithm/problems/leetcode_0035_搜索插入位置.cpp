#include "common.hpp"

int solution(std::vector<int> &nums, int target) {
  int lt = 0, gt = nums.size() - 1;
  while (lt <= gt) {
    int mid = (lt + gt) / 2;
    if (target < nums[mid]) {
      gt = mid - 1;
    } else if (target > nums[mid]) {
      lt = mid + 1;
    } else {
      return mid;
    }
  }

  return lt;
}
