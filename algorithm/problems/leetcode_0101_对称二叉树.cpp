#include <ranges>

#include "common.hpp"

bool solution1(TreeNode *root) {
  if (!root) {
    return false;
  }

  std::vector<TreeNode *> vec;
  vec.push_back(root->left);
  vec.push_back(root->right);
  do {
    int n = vec.size();
    if (n % 2 > 0) {
      return false;
    }

    int i = 0, j = n - 1;
    while (i < j) {
      if (vec[i] && vec[j]) {
        if (vec[i]->val != vec[j]->val) {
          return false;
        }
      } else if (vec[i] != vec[j]) {
        return false;
      }

      i++, j--;
    }

    int leaf = 0;
    std::vector<TreeNode *> newvec;
    for (auto *node : vec) {
      if (!node) {
        leaf++;
      } else {
        newvec.push_back(node->left);
        newvec.push_back(node->right);
      }
    }
    if (leaf == vec.size()) {
      break;
    }

    vec.swap(newvec);
  } while(true);

  return true;
}

bool solution2(TreeNode *root) {
  if (!root) {
    return false;
  }

  auto check = [](this const auto &check, TreeNode *t1, TreeNode *t2) -> bool {
    if (!t1 && !t2) {
      return true;
    }

    if (!t1 || !t2) {
      return false;
    }

    if (t1->val != t2->val) {
      return false;
    }

    return check(t1->left, t2->right) && check(t1->right, t2->left);
  };

  return check(root->left, root->right);
}
