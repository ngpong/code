#include "common.hpp"

int32_t solution(std::vector<int32_t> &heights) {
  std::stack<int32_t> sk;
  std::vector<int32_t> lmin(heights.size(), -1);
  std::vector<int32_t> rmin(heights.size(), heights.size());
  for (int32_t i = 0; i < heights.size(); i++) {
    while (!sk.empty() && heights[sk.top()] > heights[i]) {
      rmin[sk.top()] = i;
      sk.pop();
    }

    // 当压入元素时，如果栈顶存在元素，那么栈顶元素则为当前压入元素左边第一个小于它的元素。
    if (!sk.empty()) {
      lmin[i] = sk.top();
    }
    sk.push(i);
  }

  int32_t ans = INT32_MIN;
  for (int32_t i = 0; i < heights.size(); i++) {
    ans = std::max(ans, (rmin[i] - lmin[i] - 1) * heights[i]);
  }

  return ans;
}
