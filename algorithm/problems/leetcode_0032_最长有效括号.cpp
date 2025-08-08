#include "common.hpp"

// 每当遇到一个左括号则直接入栈
// 每当遇到一个右括号则直接弹出栈顶元素。
//
// 那么，当一个子串是有效的时候，栈的元素必定不会有残留。
// 如果有残留，就证明在过去的某个时间产生了一个令有效子串无效的分割符。

int32_t solution1(std::string s) {
  int32_t ans = 0;

  std::stack<int32_t> sk;
  sk.push(-1);
  for (int32_t i = 0; i < s.size(); i++) {
    if (s[i] == '(') {
      sk.push(i);
    } else {
      sk.pop();
      if (sk.empty()) {
        sk.push(i);
      } else {
        ans = std::max(ans, i - sk.top());
      }
    }
  }

  return ans;
}
