#include "common.hpp"

// 题目:
// 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和
// 为目标值 target 的那两个整数，并返回它们的数组下标。

// 解:
// 两数之和，解 target = a + b，那么假设知道 a 的情况下，这其实就是一个
// 求 b = target - a 的过程。
//
// 在这里使用了 hash 表，键为值，值下标。
//
// 每次遍历的过程中，寻找 target - a(当前下标对应元素的值) 是否已存在，如
// 果存在则代表着当前数组中存在 a + b = target 的关系

std::pair<int, int> two_sum_hash(std::vector<int> &nums, int target) {
  // target = a + b
  std::unordered_map<int32_t, int32_t> hash;
  for (int32_t i = 0; i < nums.size(); ++i) {
    auto it = hash.find(target - nums[i]);
    if (it != hash.end()) {
      return { it->second, i };
    }

    hash[nums[i]] = i;
  }

  return {};
}

std::pair<int, int> solution_2(std::vector<int> &nums, int target) {
  for (int32_t i = 0; i < nums.size(); ++i) {
    int32_t x = nums[i];
    for (int32_t j = i + 1; j < nums.size(); ++j) {
      int32_t y = nums[j];
      if (target == x + y) {
        return { i, j };
      }
    }
  }

  return {};
}

std::pair<int, int> solution_3(std::vector<int> &nums, int target) {
  int32_t left = 0, right = nums.size() - 1;

  while (left < right) {
    for (size_t i = left + 1; i <= right; i++) {
      if (target == nums[left] + nums[i]) {
        return { left, i };
      }
    }
    left++;

    for (size_t i = right - 1; i >= left; i--) {
      if (target == nums[right] + nums[i]) {
        return { right, i };
      }
    }
    right--;
  }

  return {};
}

int main(int argc, char *argv[]) {
  std::vector<int32_t> nums = { 3, 2, 4, 7, 2, 1, 0, 5, 4, 9, 11, 20, 21, 22, 23 };

  auto pair = two_sum_hash(nums, 100);

  std::cout << pair.first << std::endl;
  std::cout << pair.second << std::endl;

  return 0;
}
