#include "common.hpp"

void solution1(std::vector<int> &nums) {
  int n = nums.size();
  if (!n) {
    return;
  }

  int i = -1, j = -1;
  for (int k = 0; k < n; k++) {
    if (nums[k] != 0) {
      continue;
    }
    i = k;
    j = k;
    for (int z = k + 1; z < n; z++) {
      if (nums[z] == 0) {
        continue;
      }
      j = z;
      break;
    }
    break;
  }

  while ((i >= 0 && j >= 0) && nums[j] != 0) {
    std::swap(nums[i], nums[j]);
    while (i < n - 1) {
      if (nums[++i] == 0) {
        break;
      }
    }
    while (j < n - 1) {
      if (nums[++j] != 0) {
        break;
      }
    }
  }
}


