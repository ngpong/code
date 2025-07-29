#include "common.hpp"

void solution1(std::vector<int32_t> &nums) {
  std::vector<int32_t> bucket(3, 0x0);

  for (int32_t i = 0; i < nums.size(); i++) {
    bucket[nums[i]]++;
  }

  int32_t k = 0;
  for (int32_t i = 0; i <= 2; i++) {
    for (int32_t j = 0; j < bucket[i]; j++) {
      nums[k++] = i;
    }
  }
}

void solution2(std::vector<int32_t> &nums) {
  int32_t lt = -1, gt = nums.size();
  int32_t i = lt + 1;

  while (i < gt) {
    if (nums[i] < 1) {
      std::swap(nums[++lt], nums[i++]);
    } else if (nums[i] > 1) {
      std::swap(nums[--gt], nums[i]);
    } else {
      i++;
    }
  }
}

