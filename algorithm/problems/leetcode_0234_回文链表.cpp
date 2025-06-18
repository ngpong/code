#include "common.hpp"

bool solution1(ListNode *head) {
  std::list<ListNode *> lst;
  for (ListNode *node = head; node; node = node->next) {
    lst.push_back(node);
  }

  while (lst.size() > 1) {
    ListNode *front_node = lst.front();
    ListNode *back_node  = lst.back();

    if (front_node->val != back_node->val) {
      return false;
    }

    lst.pop_front();
    if (!lst.empty()) {
      lst.pop_back();
    }
  }

  return true;
}

bool solution2(ListNode *head) {
  std::vector<int> nums;
  for (ListNode *node = head; node; node = node->next) {
    nums.push_back(node->val);
  }

  for (int i = 0, j = nums.size() - 1; i < j; i++, j--) {
    if (nums[i] != nums[j]) {
      return false;
    }
  }

  return true;
}

bool solution3(ListNode *head) {
  ListNode *slow = head, *fast = head;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *prev = nullptr;
  for (ListNode *node = slow; node;) {
    ListNode *next_node = node->next;

    node->next = prev;
    prev = node;

    node = next_node;
  }
  ListNode *right_part = prev;

  ListNode *lst1 = head, *lst2 = right_part;
  while (lst2) {
    if (lst1->val != lst2->val) {
      return false;
    }
    lst1 = lst1->next;
    lst2 = lst2->next;
  }

  return true;
}
