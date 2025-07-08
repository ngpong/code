#include "common.hpp"

std::vector<int32_t> solution1(TreeNode *root) {
  std::queue<TreeNode *> q;
  if (root) {
    q.push(root);
  }

  std::vector<std::vector<int32_t>> levels;
  while (!q.empty()) {
    std::vector<int32_t> lv;

    for (int32_t n = q.size(); n > 0; n--) {
      TreeNode *node = q.front();
      if (node->left) q.push(node->left);
      if (node->right) q.push(node->right);

      lv.push_back(node->val);
    }

    levels.emplace_back(std::move(lv));
  }

  std::vector<int32_t> ans;
  for (auto &lv : std::as_const(levels)) {
    ans.push_back(lv.back());
  }

  return ans;
}
