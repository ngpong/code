#include "common.hpp"

ListNode *solution(ListNode *l1, ListNode *l2) {
  ListNode ans;
  ListNode *dummy = &ans;

  bool carry1 = false; // need carry on 1 ?
  while (l1 || l2) {
    int32_t num1 = l1 ? l1->val : 0;
    int32_t num2 = l2 ? l2->val : 0;

    int32_t sum = num1 + num2;
    if (carry1) {
      sum++;
      carry1 = false;
    }
    if (sum >= 10) {
      sum   %= 10;
      carry1 = true;
    }

    dummy->next = new ListNode(sum);
    dummy = dummy->next;

    l1 = l1 ? l1->next : nullptr;
    l2 = l2 ? l2->next : nullptr;
  }
  if (carry1) {
    dummy->next = new ListNode(1);
  }

  return ans.next;
}
