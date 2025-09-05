#include "common.hpp"

// 题目: 给定一个数组，将偶数都放在左边，奇数都放在右边
//
// 双指针解法，给定一个首尾的指针，先判断首指针的元素是否为奇数，如果是
// 奇数的话，就交换和尾指针的值，并且继续判断当前首指针的元素是否还是奇
// 数(因为我们不排除尾指针在交换前就是奇数的可能性)，如果还是奇数的话，那
// 就证明在执行交换前，首尾指针都属于奇数，那么这时候我们让尾指针往下走，继续
// 判断

std::vector<int32_t> sortArrayByParity(std::vector<int32_t>& nums) {
  int32_t i = 0, j = nums.size() - 1;
  while (i <= j) {
    bool i_even = nums[i] % 2 == 0;
    bool j_odd  = nums[j] % 2 == 1;

    if (!i_even && !j_odd) {
      std::swap(nums[i], nums[j]);
      i++;
      j--;
    } else {
      if (i_even) {
        i++;
      }
      if (j_odd) {
        j--;
      }
    }
  }
  return nums;
}