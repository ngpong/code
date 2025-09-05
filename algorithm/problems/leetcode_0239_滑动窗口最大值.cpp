#include "common.hpp"

std::vector<int32_t> solution1(std::vector<int32_t> &nums, int32_t k) {
  std::vector<int32_t> ans;

  int32_t i = 0, j = k - 1;
  std::multiset<int32_t, std::greater<int32_t>> ms(nums.begin(), nums.begin() + j + 1);
  while (j < nums.size()) {
    ans.push_back(*ms.begin());
    if (j == nums.size() - 1) {
      break;
    }

    // 删除的元素可能会在set中存在重复的
    if (int32_t vali = nums[i++], count = ms.count(vali) - 1; count > 0) {
      ms.erase(vali);
      for (; count > 0; count--) {
        ms.insert(vali);
      }
    } else {
      ms.erase(vali);
    }
    ms.insert(nums[++j]);
  }

  return ans;
}

std::vector<int32_t> solution2(std::vector<int32_t> &nums, int32_t k) {
  std::priority_queue<std::pair<int32_t, int32_t>> q;
  for (int32_t i = 0; i < k; i++) {
    q.emplace(nums[i], i);
  }

  std::vector<int32_t> ans = { std::get<0>(q.top()) };
  for (int32_t i = k; i < nums.size(); i++) {
    q.emplace(nums[i], i);
    while (q.top().second <= i - k) { // i - k 为当前窗口左边界之外
      q.pop();
    }

    ans.push_back(q.top().first);
  }

  return ans;
}

std::vector<int32_t> solution3(std::vector<int32_t> &nums, int32_t k) {
  std::deque<int32_t> lst;
  for (int32_t i = 0; i < k; i++) {
    while (!lst.empty() && nums[lst.back()] < nums[i]) {
      lst.pop_back();
    }
    lst.push_back(i);
  }

  std::vector<int32_t> ans = { nums[lst.front()] };
  for (int32_t i = k; i < nums.size(); i++) {
    while (!lst.empty() && nums[lst.back()] < nums[i]) {
      lst.pop_back();
    }
    lst.push_back(i);

    while (!lst.empty() && lst.front() <= i - k) {
      lst.pop_front();
    }
    ans.push_back(nums[lst.front()]);
  }

  return ans;
}
