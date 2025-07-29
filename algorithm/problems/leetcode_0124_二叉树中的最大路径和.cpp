#include "common.hpp"

int32_t solution1(TreeNode *root) {
  int32_t ans = -1001;

  [&](this const auto &dfs, TreeNode *node) -> int32_t {
    if (!node) {
      return -1001;
    }

    int32_t lmax = dfs(node->left);
    int32_t rmax = dfs(node->right);

    int32_t max_path = std::max({
      node->val,
      node->val + lmax,
      node->val + rmax,
    });

    ans = std::max({ ans, max_path, node->val + lmax + rmax });
    return max_path;
  }(root);

  return ans;
}
