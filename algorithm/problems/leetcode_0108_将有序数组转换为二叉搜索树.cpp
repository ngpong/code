#include "common.hpp"

TreeNode *solution(std::vector<int> &nums) {
  if (nums.empty()) {
    return nullptr;
  }

  int mid = (nums.size() - 1) / 2;

  std::vector<int> left(nums.begin(), nums.begin() + mid);
  std::vector<int> right(nums.begin() + mid + 1, nums.end());

  TreeNode *root = new TreeNode(nums[mid]);
  root->left = solution(left);
  root->right = solution(right);

  return root;
}
