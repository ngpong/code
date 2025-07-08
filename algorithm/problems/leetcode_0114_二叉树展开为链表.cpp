#include "common.hpp"

void solution1(TreeNode *root) {
  if (!root) {
    return;
  }

  std::vector<TreeNode *> v;
  [&](this const auto& preorder, TreeNode *node) -> void {
    if (!node) {
      return;
    }

    v.push_back(node);
    preorder(node->left);
    preorder(node->right);
  }(root);

  TreeNode *dummy = v.front();
  for (int32_t i = 1; i < v.size(); i++) {
    dummy->left = nullptr;
    dummy->right = v[i];
    dummy = dummy->right;
  }
}

void solution2(TreeNode *root) {
  TreeNode dummy;
  TreeNode *tail = &dummy;

  [&](this const auto &preorder, TreeNode *node) {
    if (!node) {
      return;
    }

    TreeNode *left  = node->left;
    TreeNode *right = node->right;

    tail->left = nullptr;
    tail->right = node;
    tail = node;

    preorder(left);
    preorder(right);
  }(root);
}
