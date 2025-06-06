#include "common.hpp"

// 题目：
// 给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。

// 双链表实现
ListNode *solutions_1(ListNode *head) {
  ListNode newlist;
  ListNode *dummy = &newlist;

  ListNode *node = head;
  while (node) {
    ListNode *nextnode = node->next;

    ListNode *l = dummy->next; // 提取 dummy 剩余的部分
    dummy->next = node;        // 设置头节点
    dummy->next->next = l;     // 链接头节点与剩余的部分

    node = nextnode;
  }

  return dummy->next;
}

// 栈实现
ListNode *solutions_2(ListNode *head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }

  std::stack<ListNode *> s;

  ListNode *it = head;
  while (it) {
    s.push(it);
    it = it->next;
  }

  ListNode *first = s.top(); s.pop();

  it = first;
  while (true) {
    ListNode *prev = s.top(); s.pop();

    it->next = prev;
    it       = it->next;

    if (s.empty()) {
      it->next = nullptr;
      break;
    }
  }

  return first;
}
