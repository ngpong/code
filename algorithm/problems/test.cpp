#include "common.hpp"

int32_t solution(TreeNode *root) {
  if (!root) {
    return 0;
  }

  std::list<TreeNode *> lst;
  lst.push_back(root);

  int32_t depth = 0;
  while (!lst.empty()) {
    depth++;

    int32_t sz = lst.size();
    while (sz > 0) {
      TreeNode *node = lst.front();
      lst.pop_front();

      if (!node->left && !node->right) {
        return depth;
      }

      if (node->left) {
        lst.push_back(node->left);
      }

      if (node->right) {
        lst.push_back(node->right);
      }

      sz--;
    }
  }

  return depth;
}

int32_t main(int32_t argc, char *argv[]) {
  TreeNode *bt = get_binary_tree(10);
  std::cout << bt << std::endl;
  std::cout << solution(bt) << std::endl;

  return 0;
}
