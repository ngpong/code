#include "common.hpp"

ListNode *mergeList(ListNode *left, ListNode *right) {
  if (!left || !right) {
    return !left ? right : left;
  }

  ListNode sentinel;
  ListNode *dummy = &sentinel;
  while (left && right) {
    if (left->val < right->val) {
      dummy->next = left;
      left = left->next;
    } else {
      dummy->next = right;
      right = right->next;
    }
    dummy = dummy->next;
  }

  if (left) {
    dummy->next = left;
  } else {
    dummy->next = right;
  }

  return sentinel.next;
}

ListNode *sortList(ListNode *head) {
  if (!head || !head->next) {
    return head;
  }

  ListNode *s = head, *f = head;
  while (f->next && f->next->next) {
    s = s->next;
    f = f->next->next;
  }

  ListNode *left = head;
  ListNode *right = s->next;
  s->next = nullptr;

  left = sortList(left);
  right = sortList(right);

  return mergeList(left, right);
}

int32_t main(int32_t argc, char *argv[]) {
  std::vector<int32_t> prices = { 7, 1, 5, 3, 6, 4 };
}
