#include "common.hpp"

// 题目：给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。
// 先访问左子树，然后访问右子树，最后访问根节点。

void solutions_1(TreeNode *root, std::vector<int> &res) {
  if (!root) {
    return;
  }

  solutions_1(root->left, res);
  solutions_1(root->right, res);
  res.push_back(root->val);
}

int main (int argc, char *argv[]) {
  TreeNode *bt = get_binary_tree();
  std::cout << bt << std::endl;

  std::vector<int> res;
  solutions_1(bt, res);

  return 0;
}
