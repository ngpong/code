#include "common.hpp"

ListNode *solution(ListNode *head) {
  std::unordered_set<ListNode *> visited;

  for (ListNode *node = head; node; node = node->next) {
    if (visited.count(node)) {
      return node;
    } else {
      visited.insert(node);
    }
  }

  return nullptr;
}

ListNode *solution2(ListNode *head) {
  ListNode *slow = head, *fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      break;
    }
  }
  if (!fast && fast != slow) {
    return nullptr;
  }

  fast = head;
  while (fast == slow) {
    slow = slow->next;
    fast = fast->next;
  }

  return slow;
}
