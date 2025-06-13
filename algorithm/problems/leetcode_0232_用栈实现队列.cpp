#include "common.hpp"

class MyQueue {
  std::stack<int32_t> m_input;
  std::stack<int32_t> m_output;

public:
  void push(int32_t x) {
    m_input.push(x);
  }

  int32_t pop() {
    int32_t val = peek();
    m_output.pop();
    return val;
  }

  int32_t peek() {
    // 转化为 output 栈
    if (m_output.empty()) {
      while (!m_input.empty()) {
        int32_t val = m_input.top();
        m_input.pop();
        m_output.push(val);
      }
    }
    return m_output.top();
  }

  bool empty() {
    return m_input.empty() && m_output.empty();
  }
};
