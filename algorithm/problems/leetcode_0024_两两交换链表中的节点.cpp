#include "common.hpp"

ListNode *solution1(ListNode *head) {
  if (!head || !head->next) {
    return head;
  }

  ListNode *ans = head->next;

  ListNode *node1 = head, *node2 = head->next;
  while (node1 && node2) {
    ListNode *node3 = node2->next;
    ListNode *node4 = node3 ? node3->next : nullptr;
    node2->next = node1;
    node1->next = node4 ? node4 : node3;

    node2 = node4;
    node1 = node3;
  }

  return ans;
}
