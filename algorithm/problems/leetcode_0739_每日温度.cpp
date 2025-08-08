#include "common.hpp"

std::vector<int32_t> solution(std::vector<int32_t> &temperatures) {
  std::vector<int32_t> ans(temperatures.size());

  std::stack<int32_t> st;
  for (int32_t i = 0; i < temperatures.size(); i++) {
    while (!st.empty()) {
      int32_t j = st.top();
      if (temperatures[i] > temperatures[j]) {
        ans[j] = i - j;
        st.pop();
      } else {
        break;
      }
    }
    st.push(i);
  }

  return ans;
}
