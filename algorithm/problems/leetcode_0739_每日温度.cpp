#include "common.hpp"

std::vector<int32_t> solution(std::vector<int32_t> &temperatures) {
  std::vector<int32_t> ans(temperatures.size());

  std::stack<uint64_t> st;
  for (int32_t i = 0; i < temperatures.size(); i++) {
    int32_t temp = temperatures[i];

    while (!st.empty()) {
      uint64_t flg = st.top();

      if (temp > (flg >> 32)) {
        int32_t j = flg & 0xFFFFFFFF;
        ans[j] = i - j;
        st.pop();
      } else {
        break;
      }
    }
    st.push((static_cast<uint64_t>(temp) << 32) | i);
  }

  return ans;
}
