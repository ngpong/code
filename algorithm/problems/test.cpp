#include "common.hpp"

ListNode *solution1(ListNode *head) {
  ListNode newlist;
  ListNode *dummy = &newlist;

  ListNode *node = head;
  while (node) {
    ListNode *nextnode = node->next;

    ListNode *l = dummy->next;
    dummy->next = node;
    dummy->next->next = l;

    node = nextnode;
  }

  return dummy->next;
}

ListNode *solution2(ListNode *head) {
  std::stack<ListNode *> s;

  for (ListNode *node = head; node; node = node->next) {
    s.push(node);
  }

  ListNode newlst;
  ListNode *dummy = &newlst;
  while (!s.empty()) {
    ListNode *node = s.top();
    s.pop();

    dummy->next = node;
    dummy = dummy->next;
  }
  dummy->next = nullptr; // 设置最后的尾节点的 nil 防止形成环

  return newlst.next;
}

int32_t main (int32_t argc, char *argv[]) {
  ListNode *list = get_list(4);
  std::cout << list << std::endl;
  std::cout << solution2(list) << std::endl;
  return 0;
}
