#include "common.hpp"

// 题目：给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。
// 先访问左子树，然后访问根节点，最后访问右子树。

void solution1(TreeNode *root) {
  std::stack<TreeNode *> s;

  while (root || !s.empty()) {
    // 0x1: 从每个节点的开始，都需要一直扫描到其左子节点的末尾；追加入栈；为方便描述，我们将每一轮的root节点称为 “根节点”；
    while (root) {
      s.push(root);
      root = root->left;
    }

    if (!s.empty()) {
      // 0x2: 提取栈顶元素
      root = s.top(); s.pop();
      std::cout << root->val << std::endl;
      // 0x3:
      // 1. 如果有右节点则将右节点作为下一轮的根节点
      // 2. 如果没有则在下一轮中逐步向上弹出上一轮中根节点的父节点
      root = root->right;
    }
  }
}

void solution2(TreeNode *root) {
  if (!root) {
    return;
  }

  solution2(root->left);
  std::cout << root->val << std::endl;
  solution2(root->right);
}

int main(void) {
  TreeNode *bt = get_binary_tree(10);
  std::cout << bt << std::endl;

  solution1(bt);

  std::cout << "<<<<<<<<<<<<<<<<" << std::endl;

  solution2(bt);

  return EXIT_SUCCESS;
}
