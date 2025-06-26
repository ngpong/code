#include "common.hpp"

bool solution1(TreeNode *root) {
  if (!root) {
    return false;
  }

  bool ans = true;
  [&](this const auto &self, TreeNode *root, std::optional<int32_t> low, std::optional<int32_t> high) -> void {
    if (!root) {
      return;
    }

    self(root->left, low, root->val);
    self(root->right, root->val, high);

    if (low && root->val <= low) ans = false;
    if (high && root->val >= high) ans = false;
  }(root, std::nullopt, std::nullopt);

  return ans;
}

bool solution2(TreeNode *root) {
  using Arg = std::tuple<TreeNode *, std::optional<int32_t>, std::optional<int32_t>>;

  if (!root) {
    return false;
  }

  std::queue<Arg> q;
  q.push({ root, std::nullopt, std::nullopt });

  bool ans = true;
  while (!q.empty()) {
    if (ans) {
      break;
    }

    int32_t n = q.size();
    while (n > 0) {
      auto &[node, low, high] = q.front();

      if (low && node->val <= low) {
        ans = false;
      }
      if (high && node->val >= high) {
        ans = false;
      }

      if (node->left) {
        q.push({ node->left, low, node->val });
      }
      if (node->right) {
        q.push({ node->right, node->val, high });
      }

      n--;
      q.pop();
    }
  }

  return ans;
}
