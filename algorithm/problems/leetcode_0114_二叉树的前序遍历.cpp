#include "common.hpp"

// 题目：给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
// 先访问根节点，然后访问左子树，最后访问右子树。

void solution1(TreeNode *root) {
  if (!root) {
    return;
  }

  std::cout << root->val << std::endl;
  solution1(root->left);
  solution1(root->right);
}

void solution2(TreeNode *root) {
  std::stack<TreeNode *> s;

  while (!s.empty() || root) {
    while (root) {
      std::cout << root->val << std::endl;
      s.push(root);
      root = root->left;
    }

    if (!s.empty()) {
      root = s.top()->left; s.pop();
    }
  }
}

std::int32_t main (std::int32_t argc, char *argv[]) {
  TreeNode *bt = get_binary_tree(10);
  std::cout << bt << std::endl;

  solution1(bt);
  std::cout << "=====================" << std::endl;
  solution2(bt);

  return 0;
}
