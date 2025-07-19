#include "common.hpp"

std::vector<int32_t> solution(std::vector<int32_t> &temperatures) {
  std::vector<int32_t> ans(temperatures.size());

  std::stack<int32_t> sk;
  for (int32_t i = 0; i < temperatures.size(); i++) {
    int32_t temp = temperatures[i];

    while (!sk.empty() && temp > temperatures[sk.top()]) {
      int32_t j = sk.top();
      ans[j] = i - j;
      sk.pop();
    }

    sk.push(i);
  }

  return ans;
}
