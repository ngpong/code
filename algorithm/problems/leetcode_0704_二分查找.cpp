#include "common.hpp"

int32_t solution(std::vector<int32_t> &nums, int32_t target) {
  int32_t lt = 0;
  int32_t gt = nums.size() - 1;

  while (lt <= gt) {
    int32_t mid = (lt + gt) >> 1;

    if (target < nums[mid]) {
      gt = mid - 1;
    } else if (target > nums[mid]) {
      lt = mid + 1;
    } else {
      return mid;
    }
  }

  return -1;
}

int32_t main (int32_t argc, char *argv[]) {
  std::vector<int32_t> nums = { 1, 3, 6, 8, 8, 9, 10, 21, 33 };

  std::cout << solution(nums, 1) << std::endl;
  std::cout << solution(nums, 2) << std::endl;
  std::cout << solution(nums, 8) << std::endl;
  std::cout << solution(nums, 21) << std::endl;
  std::cout << solution(nums, 100) << std::endl;

  return 0;
}
