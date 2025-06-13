#include "common.hpp"

// 题目：请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。

class MyStack {
  std::queue<int32_t> m_in;
  std::queue<int32_t> m_out;

public:
  void push(int32_t val) {
    m_in.push(val);
  }

  int32_t pop() {
    int32_t val = top();
    m_out.pop();
    return val;
  }

  int32_t top() {
    if (m_out.empty()) {
      while (!m_in.empty()) {
        int32_t val = m_in.front();
        m_in.pop();
        m_out.push(val);
      }
    }
    return m_out.front();
  }

  bool empty() {
    return m_out.empty() && m_in.empty();
  }
};
