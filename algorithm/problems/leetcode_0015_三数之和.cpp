#include "common.hpp"

std::vector<std::vector<int32_t>> solution1(std::vector<int32_t> &nums) {
  std::vector<std::vector<int32_t>> res;

  for (int32_t i = 0; i < nums.size(); i++) {
    int32_t target = 0 - nums[i];

    std::unordered_set<int32_t> us;
    for (int32_t j = i + 1; j < nums.size(); j++) {
      int32_t x = nums[j];
      int32_t y = target - x;

      if (us.count(y)) {
        res.push_back({ nums[i], x, y });
        break;
      } else {
        us.insert(nums[j]);
      }
    }
  }

  // 去除重复项
  for (auto &inner : res) {
    std::sort(inner.begin(), inner.end());
  }
  std::sort(res.begin(), res.end());
  res.erase(std::unique(res.begin(), res.end()), res.end());

  return res;
}

std::vector<std::vector<int32_t>> solution2(std::vector<int32_t> &nums) {
  std::vector<std::vector<int32_t>> res;

  std::sort(nums.begin(), nums.end());

  int32_t n = nums.size();
  for (size_t k = 0; k < n; k++) {
    if (k && nums[k] == nums[k - 1]) {
      continue;
    }

    int32_t target = 0 - nums[k];
    int32_t i = k + 1, j = n - 1;
    while (i < j) {
      int32_t sum = nums[i] + nums[j];
      if (sum > target) {
        j--;
      } else if (sum < target) {
        i++;
      } else {
        res.push_back({ nums[k], nums[i], nums[j] });
        for (i++; i < j && nums[i] == nums[i - 1]; i++);
        for (j--; i < j && nums[j] == nums[j + 1]; j--);
      }
    }
  }

  return res;
}
