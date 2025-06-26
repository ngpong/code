#include "common.hpp"

int32_t solution1(TreeNode *root, int32_t k) {
  using Heap = std::priority_queue<int32_t>;

  Heap heap;
  [&](this const auto &self, TreeNode *root) -> void {
    if (!root) {
      return;
    }

    self(root->left);
    self(root->right);

    if (heap.size() < k) {
      heap.push(root->val);
    } else {
      if (root->val < heap.top()) {
        heap.pop();
        heap.push(root->val);
      }
    }
  }(root);

  return heap.top();
}

int32_t solution2(TreeNode *root, int32_t k) {
  int32_t ans;
  [&](this const auto &self, TreeNode *root) -> void {
    if (!root) {
      return;
    }

    self(root->left);

    if (k--; !k) {
      ans = root->val;
      return;
    }

    self(root->right);
  }(root);

  return ans;
}
