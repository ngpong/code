#include "common.hpp"

void solution1(std::vector<int32_t> &nums) {
  std::multiset<int32_t> ms;
  for (int32_t i = nums.size() - 1; i >= 0; i--) {
    int32_t num = nums[i];
    nums.pop_back();

    ms.insert(num);
    if (auto it = ms.upper_bound(num); it != ms.end() && *it > num) {
      nums.push_back(*it);
      ms.erase(it);
      break;
    }
  }

  nums.insert(nums.end(), ms.begin(), ms.end());
}

void solution2(std::vector<int32_t> &nums) {
  auto i = nums.rbegin();
  for (; i != nums.rend(); i++) {
    if (auto find = std::upper_bound(nums.rbegin(), i, *i); find != i) {
      std::swap(*i, *find);
      break;
    }
  }
  std::reverse(nums.rbegin(), i);
}
