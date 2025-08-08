#include "common.hpp"

// 正整数从 [0....k] 的范围取值。如果一个输入序列它不想被找出「缺失的正整数」，假设它的长度为 n，那么他就必须是 [1,2,3,4,...,n] 的形式。
//
// 因此，考虑一个长度为 n 的输入序列，我们可以把它的所有正整数都放到一张 hash 表内。遍历 1....n，第一个不存在哈希表内的数字则为缺失的正整数。
//
// 在极端情况下，一个长度为 4 的输入序列可能是 [1,2,3,4] 的形式。这时候缺失的正整数则为 n+1 即 5。
//
// 但是这种做法会有 O(n) 的空间不符合题目要求，一种优化方案是将输入序列本身作为哈希表，逻辑也是从上面过度过来的。

int32_t solution1(std::vector<int32_t> &nums) {
  std::unordered_set<int32_t> us;
  for (auto &num : std::as_const(nums)) {
    if (num > 0) {
      us.insert(num);
    }
  }

  for (int32_t i = 1; i <= nums.size(); i++) {
    if (!us.count(i)) {
      return i;
    }
  }

  return nums.size() + 1;
}

int32_t solution2(std::vector<int32_t> &nums) {
  int32_t n = nums.size();
  for (int32_t i = 0; i < n; i++) {
    while (i + 1 != nums[i] && (nums[i] > 0 && nums[i] <= n)) {
      if (nums[i] == nums[nums[i]] - 1) break; // 重复元素，互相交换会形成死循环
      std::swap(nums[i], nums[nums[i] - 1]);
    }
  }

  for (int32_t i = 0; i < n; i++) {
    if (nums[i] != i + 1) {
      return i + 1;
    }
  }

  return n + 1;
}
