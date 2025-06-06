#include "common.hpp"

ListNode *merge(ListNode *left, ListNode *right) {
  ListNode dummy;
  ListNode *t = &dummy;

  while (left && right) {
    if (left->val < right->val) {
      t->next = left;
      left = left->next;
    } else {
      t->next = right;
      right = right->next;
    }
    t = t->next;
  }

  if (left) {
    t->next = left;
  } else {
    t->next = right;
  }

  return dummy.next;
}
ListNode *solution1(ListNode *head) {
  if (!head || !head->next) {
    return head;
  }

  ListNode *slow = head;
  ListNode *fast = head->next;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *left = head;
  ListNode *right = slow->next;
  slow->next = nullptr;

  left = solution1(left);
  right = solution1(right);
  return merge(left, right);
}

ListNode *solution2(ListNode *head) {
  int32_t min = head->val;
  int32_t max = head->val;
  for (auto node = head; node; node = node->next) {
    if (node->val < min) {
      min = node->val;
    }
    if (node->val > max) {
      max = node->val;
    }
  }
  int32_t size = std::abs(max - min + 1);

  Array bucket(size, 0x0);
  for (auto node = head; node; node = node->next) {
    bucket[node->val - min]++;
  }

  ListNode *node = head;
  for (int32_t i = 0; i < size; i++) {
    for (int32_t j = 0; j < bucket[i]; j++) {
      node->val = i + min;
      node = node->next;
    }
  }

  return head;
}

int32_t main (int32_t argc, char *argv[]) {
  ListNode *list = get_list_desc();
  std::cout << list << std::endl;
  std::cout << solution2(list) << std::endl;

  return 0;
}
