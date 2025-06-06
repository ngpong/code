#include "common.hpp"

// 题目：
// 给你一个链表的头节点 head ，判断链表中是否有环。
//
// 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。

bool solution1(ListNode *head) {
  std::set<ListNode *> s;

  for (ListNode *node = head; node; node = node->next) {
    if (s.find(node) != s.end()) {
      return true;
    }
    s.insert(node);
  }

  return false;
}

bool solution2(ListNode *head) {
  if (head == nullptr || head->next == nullptr) {
    return false;
  }

  ListNode *slow = head;
  ListNode *fast = head->next;

  while (slow != fast) {
    if (fast == nullptr || fast->next == nullptr) {
      return false;
    }
    slow = slow->next;
    fast = fast->next->next;
  }
  return true;
}

int32_t main (int32_t argc, char *argv[]) {
  ListNode *list = get_list(10);

  return 0;
}
