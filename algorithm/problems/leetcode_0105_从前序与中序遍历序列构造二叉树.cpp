#include "common.hpp"

// 题目: 根据前序遍历和中序遍历的结果重构二叉树

TreeNode* solution(std::vector<int>& preorder, std::vector<int>& inorder) {
  // 依据前序的第一个元素可以知道树的根节点是什么；
  // 在中序中找到根节点的位置，此时左右则分别对应着左右子树；
  // 使用中序中求得的左右子树的长度划分在前序中的左右子树；
  // 此时我们得到了前序与中序的左右子树，作为子问题递归求解即可；

  // 在最坏的情况下，树仅有单向的分支；那么每次在中序中查找根节点的过程是 O(n) 的，那么整个时间复杂度则可以认为是 O(n^2)；
  // 一种优化手段是前置构造一份哈希表，简化中序中索引根节点的过程。
  //
  // 递归参数可以修改为下标区间来做

  if (preorder.empty()) {
    return nullptr;
  }

  TreeNode *root = new TreeNode(preorder[0]);

  int32_t i = std::find(inorder.begin(), inorder.end(), root->val) - inorder.begin();
  std::vector<int32_t> inorder_l(inorder.begin(), inorder.begin() + i);
  std::vector<int32_t> inorder_r(inorder.begin() + 1 + i, inorder.end());
  std::vector<int32_t> preorder_l(preorder.begin() + 1, preorder.begin() + 1 + i);
  std::vector<int32_t> preorder_r(preorder.begin() + 1 + i, preorder.end());

  root->left = solution(preorder_l, inorder_l);
  root->right = solution(preorder_r, inorder_r);

  return root;
}

int main(int argc, char* argv[]) {
  std::vector<int> preorder = { 3, 9, 20, 15, 7 };
  std::vector<int> inorder  = { 9, 3, 15, 20, 7 };

  std::cout << solution(preorder, inorder) << std::endl;

  return 0;
}
