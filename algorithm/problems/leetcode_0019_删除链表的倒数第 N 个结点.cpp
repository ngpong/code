#include "common.hpp"

ListNode *solution1(ListNode *head, int32_t n) {
  ListNode *i = head, *j = head;

  while (n > 0) {
    j = j->next;
    n--;
  }

  ListNode *p = nullptr;
  while (i && j) {
    p = i;
    i = i->next;
    j = j->next;
  }

  if (p) {
    p->next = i->next;
    return head;
  } else {
    return i->next;
  }
}
