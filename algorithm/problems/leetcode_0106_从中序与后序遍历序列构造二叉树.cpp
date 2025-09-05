#include "common.hpp"

TreeNode *solution(std::vector<int32_t> &inorder, std::vector<int32_t> &postorder) {
  if (inorder.empty() || postorder.empty()) {
    return nullptr;
  }

  TreeNode *root = new TreeNode(postorder[postorder.size() - 1]);

  int32_t i = std::find(inorder.begin(), inorder.end(), root->val) - inorder.begin();
  std::vector<int32_t> inorder_l(inorder.begin(), inorder.begin() + i);
  std::vector<int32_t> inorder_r(inorder.begin() + i + 1, inorder.end());
  std::vector<int32_t> postorder_l(postorder.begin(), postorder.begin() + i);
  std::vector<int32_t> postorder_r(postorder.begin() + i, postorder.end() - 1);

  root->left = solution(inorder_l, postorder_l);
  root->right = solution(inorder_r, postorder_r);

  return root;
}
