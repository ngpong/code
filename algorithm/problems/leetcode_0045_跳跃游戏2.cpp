#include "common.hpp"

int32_t solution(std::vector<int32_t> &nums) {
  int32_t count = 0;

  int32_t last = nums.size() - 1;
  for (int32_t start = 0; start < last; ) {
    int32_t end = start + nums[start];
    if (end >= last) {
      count++;
      break;
    } else {
      int32_t maxdist = 0;
      for (int32_t i = start + 1; i <= end; i++) {
        int32_t dist = i + nums[i];
        if (dist > maxdist) {
          maxdist = dist;
          start = i;
        }
      }
      count++;
    }
  }

  return count;
}
