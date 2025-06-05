#include "common.hpp"

// 题目：
// 给你二叉树的根节点 root ，返回其节点值的 锯齿形层序遍历 。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

std::vector<int> solution1(TreeNode* root) {
  std::vector<int32_t> ret;

  std::vector<TreeNode *> nodes;
  nodes.push_back(root);

  bool reverse = false;
  while (!nodes.empty()) {
    std::list<int32_t> lst;
    std::vector<TreeNode *> temp;
    for(auto &node : nodes) {
      if (reverse) {
        lst.push_front(node->val);
      } else {
        lst.push_back(node->val);
      }

      if (node->left) {
        temp.push_back(node->left);
      }
      if (node->right) {
        temp.push_back(node->right);
      }
    }
    nodes.swap(temp);
    std::copy(std::begin(lst), std::end(lst), std::back_inserter(ret));

    reverse = !reverse;
  }

  return ret;
}

std::vector<std::vector<int>> solution2(TreeNode *root) {
  std::vector<std::vector<int>> ret;

  std::list<TreeNode *> lst;
  lst.push_back(root);

  bool reverse = false;
  while (!lst.empty()) {
    std::vector<int32_t> v;

    int32_t sz = lst.size();
    while (sz > 0) {
      TreeNode *node;
      if (reverse) {
        node = lst.back();
        lst.pop_back();
        if (node->right) {
          lst.push_front(node->right);
        }
        if (node->left) {
          lst.push_front(node->left);
        }
      } else {
        node = lst.front();
        lst.pop_front();
        if (node->left) {
          lst.push_back(node->left);
        }
        if (node->right) {
          lst.push_back(node->right);
        }
      }

      v.push_back(node->val);

      sz--;
    }

    ret.emplace_back(std::move(v));
    reverse = !reverse;
  }

  return ret;
}

int main(int argc, char *argv[]) {
  TreeNode *bt = get_binary_tree(10);
  std::cout << bt << std::endl;

  std::cout << solution1(bt) << std::endl;
  std::cout << solution2(bt) << std::endl;

  return 0;
}
