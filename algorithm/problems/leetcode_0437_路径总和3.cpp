#include "common.hpp"

int64_t solution(TreeNode *root, int64_t target) {
  int32_t ans = 0;

  std::unordered_map<int64_t, int64_t> hash = { { 0, 1 } };
  [&](this const auto &DFS, TreeNode *root, int64_t sum = 0) -> void {
    if (!root) {
      return;
    }

    sum += root->val;
    if (auto it = hash.find(sum - target); it != hash.end()) {
      ans += it->second;
    }
    hash[sum]++;

    DFS(root->left, sum);
    DFS(root->right, sum);

    hash[sum]--;
  }(root);

  return ans;
}
