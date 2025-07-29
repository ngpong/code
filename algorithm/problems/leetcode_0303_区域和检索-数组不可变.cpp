#include "common.hpp"

class NumArray1 {
  std::vector<int32_t> m_sums;

public:
  NumArray1(std::vector<int32_t>& nums) {
    m_sums.clear();

    int32_t sum = 0;
    for (auto num : nums) {
      sum += num;
      m_sums.push_back(sum);
    }
  }

  int32_t sumRange(int32_t left, int32_t right) {
    if (left == 0) {
      return m_sums[right];
    } else {
      return m_sums[right] - m_sums[left - 1];
    }
  }
};

class NumArray2 {
  std::vector<int32_t> m_sums;

public:
  NumArray2(std::vector<int32_t>& nums) {
    m_sums.reserve(nums.size() + 1);
    m_sums.push_back(0);

    for (int32_t i = 0; i < nums.size(); i++) {
      m_sums[i + 1] = m_sums[i] + nums[i];
    }
  }

  int32_t sumRange(int32_t left, int32_t right) {
    return m_sums[left] + m_sums[right + 1];
  }
};
