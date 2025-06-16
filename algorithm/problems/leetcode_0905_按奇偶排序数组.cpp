#include <iostream>
#include <vector>

using namespace std;

#define SWAP(x, y) \
  if (x != y) {    \
    x = x ^ y;     \
    y = x ^ y;     \
    x = x ^ y;     \
  }

// 题目: 给定一个数组，将偶数都放在左边，奇数都放在右边
//
// 双指针解法，给定一个首尾的指针，先判断首指针的元素是否为奇数，如果是
// 奇数的话，就交换和尾指针的值，并且继续判断当前首指针的元素是否还是奇
// 数(因为我们不排除尾指针在交换前就是奇数的可能性)，如果还是奇数的话，那
// 就证明在执行交换前，首尾指针都属于奇数，那么这时候我们让尾指针往下走，继续
// 判断

std::vector<int> event_left_odd_right(std::vector<int> &nums) {
  if (nums.size() == 0) return nums;

  int i = 0;
  int j = nums.size() - 1;
  while (i < j) {
    while (nums[i] % 2 != 0) {
      SWAP(nums[i], nums[j]);
      j--;
    }
    i++;
  }

  return nums;
}

int main(void) {
  vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  arr = event_left_odd_right(arr);

  for (auto val = arr.begin(); val != arr.end(); ++val) {
    cout << *val << endl;
  }

  return EXIT_SUCCESS;
}
