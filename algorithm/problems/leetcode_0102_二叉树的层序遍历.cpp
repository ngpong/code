#include "common.hpp"

std::vector<std::vector<int>> solution(TreeNode *root) {
  std::vector<std::vector<int>> res;
  if (!root) {
    return res;
  }

  std::queue<TreeNode *> q;
  q.push(root);

  while (!q.empty()) {
    std::vector<int> vals;

    int n = q.size();
    while (n > 0) {
      TreeNode *node = q.back(); q.pop();
      vals.push_back(node->val);

      if (node->left) {
        q.push(node->left);
      }

      if (node->right) {
        q.push(node->right);
      }

      n--;
    }

    res.emplace_back(std::move(vals));
  }

  return res;
}
