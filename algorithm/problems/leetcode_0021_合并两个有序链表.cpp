#include "common.hpp"

// 题目：将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

// 参考归并排序时的合并操作

ListNode *soultion(ListNode *left, ListNode *right) {
  ListNode dummy;
  ListNode *tmp = &dummy;

  while (left && right) {
    if (left->val < right->val) {
      tmp->next = left;
      left     = left->next;
    } else {
      tmp->next = right;
      right     = right->next;
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
