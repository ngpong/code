#include "common.hpp"

TreeNode *solution(TreeNode *root) {
  if (!root) {
    return root;
  }

  std::queue<TreeNode *> q;
  q.push(root);

  while (!q.empty()) {
    int n = q.size();
    while (n > 0) {
      TreeNode *node = q.front();
      q.pop();

      TreeNode *left = node->left;
      TreeNode *right = node->right;

      node->right = left;
      node->left = right;

      if (left) {
        q.push(left);
      }

      if (right) {
        q.push(right);
      }

      n--;
    }
  }

  return root;
}

TreeNode *solution2(TreeNode *root) {
  if (!root) {
    return root;
  }

  TreeNode *left  = solution2(root->left);
  TreeNode *right = solution2(root->right);

  root->left = right;
  root->right = left;

  return root;
}
