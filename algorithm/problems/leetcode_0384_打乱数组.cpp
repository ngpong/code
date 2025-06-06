#include <sys/time.h>
#include "common.hpp"

// 题目：
// 给你一个整数数组 nums ，设计算法来打乱一个没有重复元素的数组。
//
// 打乱后，数组的所有排列应该是等可能的。

// 等比的意思是：每个元素都够等概率出现在每个位置中，也就是说需要设计一个公平的随机洗牌算法。
//
// 经典的 Knuth 洗牌算法能够保证公平的同时并在 O(n) 的时间复杂度内返回结果。解释如下：
//  1. 开始数组共有 5 个元素
//  2. 在前 5 个元素中随机选择一个与第 5 个元素交换，此时，每个数都有 1/5 的概率被交换到第 5 的位置；我们看作此次交换的概率为 1/5。
//  3. 在前 4 个元素中随机选择一个与第 4 个元素交换，每个数都有 1/4 的概率被交换到第 4 的位置，又由于第 4 个元素在步骤 2 时有 4/5
//  的概率逃逸，所以我们看作此次交换的概率为 4/5 * 1/4 = 1/5
//  4. 在前 3 个元素中随机选择一个与第 3 个元素交换，每个数都有 1/3 的概率被交换到第 3 的位置，又由于第 3 个元素在步骤 2 和 步骤 3 时分别有 4/5 和 4/3 的概率逃逸，所以我们看作此次交换的概率为 4/5 * 4/3 * 1/3 = 1/5
//  5. ...
//  6. 依次类推，我们可以得出所有元素被交换的概率都是等比的。

class Solution {
  std::vector<int32_t> m_org;

public:
  Solution(std::vector<int32_t> &nums) {
    srand((unsigned)time(NULL));
    m_org = nums;
  }

  const std::vector<int32_t> &reset() {
    return m_org;
  }

  std::vector<int32_t> shuffle() {
    std::vector<int32_t> nums = m_org;
    for (int32_t i = nums.size(); i >= 0; i--) {
      std::swap(nums[i], nums[std::rand() % (i + 1)]);
    }

    return nums;
  }
};

std::int32_t main(std::int32_t argc, char *argv[]) {
  return 0;
}
