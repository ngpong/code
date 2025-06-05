#include "common.hpp"

// 题目: 每过 k 次反转一次链表
// 例如: K = 3, 12345678 -> 32165478
//
// 利用栈的思想即可，每次遍历的时候压入栈中，到达第 k 次的时候，将栈中的元素挨个弹出就是一个反转的形态，拼接回即可

std::pair<ListNode *, ListNode *> revert_list(std::stack<ListNode *> &s) {
  ListNode *head = s.top(); s.pop();

  ListNode *tail = head;
  while (!s.empty()) {
    ListNode *node = s.top(); s.pop();

    tail->next = node;
    tail = tail->next;
  }
  tail->next = nullptr;

  return { head, tail };
}

ListNode *solutions(ListNode *list, std::int32_t k) {
  if (list == nullptr || list->next == nullptr) {
    return list;
  }

  std::stack<ListNode *> s;

  ListNode *top = new ListNode(-1, list);

  ListNode *it = list, *wrap = top;
  for (;;) {
    for (std::int32_t j = 0; j < k && it; ++j) {
      s.push(it);
      it = it->next;
    }

    if (s.size() < k) { // 处理尾部阶段剩余节点数不足k时的情况
      break;
    } else {            // 处理正常能够找到k个节点的情况
      auto [head, tail] = revert_list(s);
      tail->next = it;
      wrap->next = head;

      wrap = tail;
    }
  }

  ListNode *ret = top->next;
  delete top;

  return ret;
}

int main(void) {
  ListNode* node = get_list(10);

  solutions(node, 4);

  return EXIT_SUCCESS;
}
