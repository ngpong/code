#include "common.hpp"

int32_t solution1(std::vector<int32_t> &nums) {
  int32_t max = INT32_MIN;

  size_t n = nums.size();
  for (size_t i = 0; i < n; i++) {
    for (size_t j = i; j < n; j++) {
      size_t start = i;
      size_t ended = j;

      int32_t sum = 0;
      while (start <= ended) {
        sum += nums[start];
        max = std::max(sum, max);

        start++;
      }
    }
  }

  return max;
}
