// 题目: 求得二叉树的最小深度
//
// 该题采用广度优先遍历写法，层级从左往右的方式去遍历每个节点，并且每个子节点要在
// 其父节点所维护的 depth 的基础上 +1，切记一条特性是，由于是层级从左往右遍历节点
// 所以当最先出现某个节点为叶子节点的时候，则代表从根节点到该节点的深度最小，那么
// 我们返回维护的这个 depth 即可

#include "common.hpp"

int solution1(TreeNode *root) {
  int min = 0;

  auto _solution = make_y_combinator([&](auto _solution, TreeNode *node, int depth = 0) -> void {
    if (!node) {
      return;
    }

    depth++;

    if (!node->left && !node->right) {
      min = !min ? depth : std::min(depth, min);
    } else {
      _solution(node->left, depth);
      _solution(node->right, depth);
    }
  });

  _solution(root);

  return min;
}

int solution2(TreeNode *root) {
  int min = 0;

  if (!root) {
    return min;
  }

  int dp = 0;
  std::stack<std::pair<TreeNode *, int>> s;

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

int solution3(TreeNode *root) {
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

int main(int argc, char *argv[]) {
  TreeNode *bt = get_binary_tree();
  std::cout << bt << std::endl;

  std::cout << solution1(bt) << std::endl;
  std::cout << solution2(bt) << std::endl;

  return 0;
}
