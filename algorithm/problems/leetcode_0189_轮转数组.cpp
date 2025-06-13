#include "common.hpp"

// 题目: 给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

// void reverse(string &str, int start, int end) {
//   char tmp;
//   for (; start < end; ++start, --end) {
//     tmp = str[start];
//     str[start] = str[end];
//     str[end] = tmp;
//   }
// }
// void string_right_shift(string str, int k) {
//   int n = str.size();
//   reverse(str, 0, n - k - 1);
//   reverse(str, k, n - 1);
//   reverse(str, 0, n - 1);
//
//   cout << str << endl;
// }

void reverse(std::vector<int32_t> &nums, int32_t start, int32_t end) {
  for (int32_t lt = start, gt = end; lt < gt; lt++, gt--) {
    std::swap(nums[lt], nums[gt]);
  }
}
void solution1(std::vector<int32_t> &nums, int32_t k) {
  int32_t sz = nums.size();
  reverse(nums, 0, sz);
  reverse(nums, 0, k);
  reverse(nums, k, sz);
}

void solution2(std::vector<int32_t> &nums, int32_t k) {
  int32_t sz = nums.size();

  std::vector<int32_t> rotate_nums(sz);
  for (int32_t i = 0; i < sz; i++) {
    rotate_nums[(i + k) % sz] = nums[i];
  }
  nums.assign(rotate_nums.begin(), rotate_nums.end());
}
