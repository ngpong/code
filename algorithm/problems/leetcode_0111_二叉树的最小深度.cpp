// 题目: 求得二叉树的最小深度
//
// 该题采用广度优先遍历写法，层级从左往右的方式去遍历每个节点，并且每个子节点要在
// 其父节点所维护的 depth 的基础上 +1，切记一条特性是，由于是层级从左往右遍历节点
// 所以当最先出现某个节点为叶子节点的时候，则代表从根节点到该节点的深度最小，那么
// 我们返回维护的这个 depth 即可

#include "common.hpp"

int32_t solution1(TreeNode *root) {
  int32_t min = 0;
  [&](this const auto &self, TreeNode *node, int32_t depth = 0) -> void {
    if (!node) {
      return;
    }

    depth++;

    if (!node->left && !node->right) {
      min = !min ? depth : std::min(depth, min);
    } else {
      self(node->left, depth);
      self(node->right, depth);
    }
  }(root);

  return min;
}

int32_t solution2(TreeNode *root) {
  int32_t min = 0;

  if (!root) {
    return min;
  }

  int32_t dp = 0;
  std::stack<std::pair<TreeNode *, int32_t>> s;

  for (TreeNode *it = root; it || !s.empty();) {
    while (it) {
      dp++;

      if (it->left) {
        s.push(std::make_pair(it, dp));
        it = it->left;
      } else if (it->right) {
        it = it->right;
      } else {
        min = !min ? dp : std::min(min, dp);
        it = nullptr;
      }
    }

    if (!s.empty()) {
      auto &pair = s.top();

      it = pair.first->right;
      dp = pair.second;

      s.pop();
    }
  }

  return min;
}

int32_t main(int32_t argc, char *argv[]) {
  TreeNode *bt = get_binary_tree();
  std::cout << bt << std::endl;

  std::cout << solution1(bt) << std::endl;
  std::cout << solution2(bt) << std::endl;

  return 0;
}
