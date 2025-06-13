// 题目：
// 给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

#include "common.hpp"

// 计数排序；考虑如何处理负值的问题
ListNode *solution1(ListNode *head) {
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

ListNode *merge(ListNode *left, ListNode *right) {
  ListNode dummy;
  ListNode *tmp = &dummy;
  while (left && right) {
    if (left->val < right->val) {
      tmp->next = left;
      left = left->next;
    } else {
      tmp->next = right;
      right = right->next;
    }
    tmp = tmp->next;
  }

  if (left) {
    tmp->next = left;
  } else {
    tmp->next = right;
  }

  return dummy.next;
}
ListNode *solution2(ListNode *head) {
  if (!head || !head->next) {
    return head;
  }

  ListNode *slow = head;
  ListNode *fast = head->next;
  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
  }

  ListNode *left  = head;
  ListNode *right = slow->next;
  slow->next = nullptr;

  left = solution2(left);
  right = solution2(right);
  return merge(left, right);
}
