#include "common.hpp"

ListNode *solution1(std::vector<ListNode *> &lists) {
  ListNode dummy;
  ListNode *dummy_p = &dummy;

  while (true) {
    auto min = lists.end();
    for (auto it = lists.begin(); it != lists.end(); it++) {
      if (!*it) {
        continue;
      }

      if (min == lists.end()) {
        min = it;
      } else if ((*it)->val < (*min)->val) {
        min = it;
      }
    }
    if (min == lists.end()) {
      break;
    }

    dummy_p->next = *min;
    dummy_p = dummy_p->next;
    *min = (*min)->next;

    if (*min == nullptr) {
      lists.erase(min);
    }

    if (lists.empty()) {
      break;
    } else if (lists.size() == 1) {
      dummy_p->next = lists[0];
      break;
    }
  }

  return dummy.next;
}

ListNode *solution2(std::vector<ListNode *> lists) {
  auto merge = [&](ListNode *head0, ListNode *head1) -> ListNode * {
    if (!head0) return head1;
    if (!head1) return head0;

    ListNode ans;
    ListNode *dummy = &ans;
    while (head0 && head1) {
      if (head0->val < head1->val) {
        dummy->next = head0;
        head0 = head0->next;
      } else {
        dummy->next = head1;
        head1 = head1->next;
      }
      dummy = dummy->next;
    }

    if (head0) {
      dummy->next = head0;
    } else {
      dummy->next = head1;
    }

    return ans.next;
  };

  return [&](this const auto &split, int32_t low, int32_t high) -> ListNode * {
    if (low == high) {
      return lists[low];
    }
    if (low > high) {
      return nullptr;
    }

    int32_t mid = (low + high) >> 1;
    ListNode *head0 = split(low, mid);
    ListNode *head1 = split(mid + 1, high);
    return merge(head0, head1);
  }(0, lists.size() - 1);
}
