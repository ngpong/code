#include "common.hpp"

ListNode *solution(ListNode *head) {


  ListNode *nodei = head, *nodej = head->next;
  while (nodej) {
  }
}

int32_t main(int32_t argc, char *argv[]) {
  ListNode *head = new ListNode(9);
  head->next = new ListNode(9);
  head->next->next = new ListNode(9);
  head->next->next->next = new ListNode(9);
  head->next->next->next->next = new ListNode(9);
  head->next->next->next->next->next = new ListNode(9);
  head->next->next->next->next->next->next = new ListNode(9);

  solution(head);
}
