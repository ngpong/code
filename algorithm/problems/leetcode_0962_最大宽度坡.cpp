#include "common.hpp"

int32_t solution(std::vector<int32_t>& nums) {
  std::stack<int32_t> sk;
  for (int32_t i = 0; i < nums.size(); i++) {
    if (sk.empty() || nums[sk.top()] > nums[i]) {
      sk.push(i);
    }
  }

  int32_t ans = 0;
  for (int32_t j = nums.size() - 1; j >= 0; j--) {
    while (!sk.empty() && nums[j] >= nums[sk.top()]) {
      ans = std::max(ans, j - sk.top());
      sk.pop();
    }
  }

  return ans;
}
