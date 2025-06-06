#include "common.hpp"

// 题目:
// 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。
//
// 如果两个链表不存在相交节点，返回 null 。

// 情况一：两个链表相交
// 链表 headA 和 headB 的长度分别是 m 和 n。假设链表 headA 的不相交部分有 a 个节点，链表 headB 的不相交部分有 b 个节点，两个链表相交的部分有 c 个节点，则有 a+c=m，b+c=n。
//  如果 a=b，则两个指针会同时到达两个链表相交的节点，此时返回相交的节点；
//  如果 a=b，则指针 pA 会遍历完链表 headA，指针 pB 会遍历完链表 headB，两个指针不会同时到达链表的尾节点，然后指针 pA 移到链表 headB 的头节点，指针 pB 移到链表 headA 的头节点，然后两个指针继续移动，在指针 pA 移动了 a+c+b 次、指针 pB 移动了 b+c+a 次之后，两个指针会同时到达两个链表相交的节点，该节点也是两个指针第一次同时指向的节点，此时返回相交的节点。
// 情况二：两个链表不相交
// 链表 headA 和 headB 的长度分别是 m 和 n。考虑当 m=n 和 m=n 时，两个指针分别会如何移动：
//  如果 m=n，则两个指针会同时到达两个链表的尾节点，然后同时变成空值 null，此时返回 null；
//  如果 m =n，则由于两个链表没有公共节点，两个指针也不会同时到达两个链表的尾节点，因此两个指针都会遍历完两个链表，在指针 pA 移动了 m+n 次、指针 pB 移动了 n+m 次之后，两个指针会同时变成空值 null，此时返回 null。

ListNode *solution(ListNode *headA, ListNode *headB) {
  ListNode *pA = headA;
  ListNode *pB = headB;

  while (pA != pB) {
    pA = pA == nullptr ? headB : pA->next;
    pB = pB == nullptr ? headA : pB->next;
  }

  return pA;
}
