#include <iostream>
#include <stack>

// 题目: 设计一个能够返回当前栈中所有元素最小值的栈，要求时间复杂度和空间复杂度都为 O(1)

class min_stack {
  std::stack<int> m_stack;

  int get_min(int val) {
    return val & 0xFFFF0000 >> 16;
  }

  int get_real(int val) {
    return val & 0xFFFF;
  }

  int set_num(int val, int min_val) {
    return val | min_val << 16;
  }

public:
  void push(int val) {
    if (m_stack.empty()) {
      m_stack.push(set_num(val, val));
      m_stack.push(val);
    }

    int min_val = get_min(m_stack.top());
    if (val < min_val) {
      min_val = val;
    }

    m_stack.push(set_num(val, min_val));
  }

  int pop() {
    int ret = m_stack.top();
    m_stack.pop();
    return ret;
  }

  int min() {
    return m_stack.top() >> 16;
  }
};
