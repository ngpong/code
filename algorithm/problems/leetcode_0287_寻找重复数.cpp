#include "common.hpp"

int32_t solution(std::vector<int32_t> &nums) {
  int32_t slow = 0, fast = 0;
  while (true) { // 依据题目描述，必定存在环，因此可以求得解，不存在死循环
    slow = nums[slow];
    fast = nums[nums[fast]];
    if (slow == fast) {
      fast = 0;

      while (true) {
        slow = nums[slow];
        fast = nums[fast];
        if (slow == fast) {
          return slow;
        }
      }
    }
  }
}
