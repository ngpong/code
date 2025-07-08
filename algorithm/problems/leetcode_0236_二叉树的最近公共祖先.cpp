#include "common.hpp"

TreeNode *solution(TreeNode *root, TreeNode *p, TreeNode *q) {
 if (!root) {
    return nullptr;
  }

  if (root->val == p->val || root->val == q->val) {
    return root;
  }

  TreeNode *left = solution(root->left, p, q);
  TreeNode *right = solution(root->right, p, q);
  if (left == nullptr && right != nullptr) {
    return right;
  }
  else if (left != nullptr && right == nullptr) {
    return left;
  }
  else if (left != nullptr && right != nullptr) {
    return root;
  }
  else {
    return nullptr;
  }
}
