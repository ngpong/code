#include "common.hpp"

// 题目: 求得二叉树的最大深度
//
// 采用后序遍历的方式，当搜索到一个叶子节点的时候，则代表该节点的深度为 1，然后以
// 这个节点的深度的基础上再返回其父节点的位置，其父节点再依据这个节点再 +1，以此递归

int solution_1(TreeNode *root) {
  if (root == nullptr) {
    return 0;
  }

  int l_deep = solution_1(root->left);
  int r_deep = solution_1(root->right);

  return std::max(l_deep, r_deep) + 1;
}

int solution_2(TreeNode *root) {
  if (!root) {
    return 0;
  }

  std::queue<TreeNode *> q;
  q.push(root);

  int32_t depth = 0;
  while (!q.empty()) {
    int32_t sz = q.size();
    while (sz > 0) {
      TreeNode *node = q.front();
      q.pop();

      if (node->left) {
        q.push(node->left);
      }

      if (node->right) {
        q.push(node->right);
      }

      sz--;
    }

    depth++;
  }

  return depth;
}

int main(int argc, char *argv[]) {
  TreeNode *bt = get_binary_tree();
  std::cout << bt << std::endl;

  std::cout << solution_1(bt) << std::endl;
  std::cout << solution_2(bt) << std::endl;

  return 0;
}
