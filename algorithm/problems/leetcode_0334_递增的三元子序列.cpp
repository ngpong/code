#include "common.hpp"

// 题目: 给你一个整数数组 nums ，判断这个数组中是否存在长度为 3 的递增子序列

bool solution1(std::vector<int> &nums) {
  if (nums.size() < 3) {
    return false;
  }

  int first = INT32_MAX, second = INT32_MAX;
  for(auto &num : nums) {
    if (num <= first) {
      first = num;
    } else if (num <= second) {
      second = num;
    } else if (num > second) {
      return true;
    }
  }

  return false;
}
