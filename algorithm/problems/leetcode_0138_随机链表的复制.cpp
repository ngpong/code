#include "common.hpp"

class Node {
public:
  int32_t val;
  Node *next;
  Node *random;

  Node(int32_t _val) {
    val    = _val;
    next   = nullptr;
    random = nullptr;
  }
};


Node *copyRandomList(Node *old_head) {
  if (!old_head) {
    return nullptr;
  }

  std::unordered_map<Node *, Node *> hash;

  Node *new_head = new Node(old_head->val);
  new_head->random = old_head->random;
  hash[old_head] = new_head;

  for (Node *old_node = old_head->next, *it = new_head; old_node; old_node = old_node->next) {
    Node *new_node = new Node(old_node->val);
    new_node->random = old_node->random;
    hash[old_node] = new_node;

    it->next = new_node;
    it = new_node;
  }

  for (Node *it = new_head; it; it = it->next) {
    if (it->random) {
      it->random = hash[it->random];
    }
  }

  return new_head;
}
