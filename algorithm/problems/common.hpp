#include <algorithm>
#include <array>
#include <bit>
#include <cstdlib>
#include <cmath>
#include <bitset>
#include <chrono>
#include <iomanip>
#include <cstring>
#include <ctime>
#include <functional>
#include <future>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <sstream>
#include <stack>
#include <thread>
#include <vector>
#include <benchmark/benchmark.h>

#define MAX_TEST_CASE 100000

using Array = std::vector<int32_t>;

using pair_i_i = std::pair<int32_t, int32_t>;

template <class F>
struct y_combinator {
  F f;

  template <class... Args>
  decltype(auto) operator()(Args &&...args) const {
    return f(*this, std::forward<Args>(args)...);
  }
};

template <class F>
y_combinator<std::decay_t<F>> make_y_combinator(F &&f) {
  return { std::forward<F>(f) };
}

struct ListNode {
  int32_t val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int32_t x) : val(x), next(nullptr) {}
  ListNode(int32_t x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
  int32_t val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int32_t x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int32_t x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &datas) {
  for (const auto &data : datas) {
    std::cout << data << " ";
  }

  return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::list<T> &datas) {
  for (const auto &data : datas) {
    std::cout << data << " ";
  }

  return os;
}

std::ostream &operator<<(std::ostream &os, TreeNode *root) {
  auto PrintBT = make_y_combinator([&](auto PrintBT, const std::string &prefix, TreeNode *node, bool isLeft, bool isRoot) -> void {
    if (node != nullptr) {
      std::cout << prefix;

      std::cout << (isRoot ? "ROOT:" : (isLeft ? "├── L:" : "└── R:"));

      // print the value of the node
      std::cout << node->val << std::endl;

      // enter the next tree level - left and right branch
      PrintBT(prefix + (isLeft ? "│   " : "    "), node->left, true, false);
      PrintBT(prefix + (isLeft ? "│   " : "    "), node->right, false, false);
    }
  });

  PrintBT("", root, false, true);

  return os;
}

std::ostream &operator<<(std::ostream &os, ListNode *list) {
  auto it = list;
  while (it) {
    const void *address = static_cast<void *>(it);
    std::stringstream ss;
    ss << address;
    const std::string& pointer = ss.str();
    const std::string& msg = "[" + pointer + "] " + std::to_string(it->val);

    std::cout << msg << std::endl;
    if (it->next) {
      std::cout << std::setw(14) << "⬇️" << std::endl;
    }

    it = it->next;
  }

  return os;
}

Array get_partially_array() {
  static Array ret;

  if (ret.empty()) {
    ret = std::vector<int32_t>(MAX_TEST_CASE, 0x0);

    std::mt19937 rng(std::random_device{}());

    // 前70%部分有序
    int32_t orderedPartSize = MAX_TEST_CASE * 0.7;
    for (int32_t i = 0; i < orderedPartSize; ++i) {
      ret[i] = i;
    }

    // 剩余30%部分随机
    std::uniform_int_distribution<int32_t> dist(0, MAX_TEST_CASE * 2);
    for (int32_t i = orderedPartSize; i < MAX_TEST_CASE; ++i) {
      ret[i] = dist(rng);
    }

    // 在有序部分中随机交换少量元素（10%）
    int32_t swapCount = orderedPartSize * 0.1;
    for (int32_t i = 0; i < swapCount; ++i) {
      int32_t idx1 = rng() % orderedPartSize;
      int32_t idx2 = rng() % orderedPartSize;
      std::swap(ret[idx1], ret[idx2]);
    }
  }

  return ret;
}

Array &get_total_random_array() {
  static Array ret;

  if (ret.empty()) {
    ret = std::vector<int32_t>(MAX_TEST_CASE, 0x0);

    for (int32_t i = 0; i < MAX_TEST_CASE; ++i) {
      ret[i] = i;
    }

    std::mt19937 rng(std::random_device{}());
    std::shuffle(ret.begin(), ret.end(), rng);
  }

  return ret;
}

ListNode *get_list_desc(int32_t begin = 10, int32_t end = -2) {
  if (begin < end) {
    return nullptr;
  } else {
    ListNode *node = new ListNode(begin);
    node->next     = get_list_desc(--begin, end);

    return node;
  }
}

ListNode *get_list(int32_t end = 10, int32_t idx = 0) {
  if (idx > end) {
    return nullptr;
  } else {
    ListNode *node = new ListNode(idx);
    node->next     = get_list(end, ++idx);

    return node;
  }
}

TreeNode *get_binary_tree(int32_t size) {
  std::queue<TreeNode *> s;

  int32_t idx = 1;

  TreeNode *root = new TreeNode(idx++);
  s.push(root);

  while (idx <= 10) {
    TreeNode *node = s.front();
    s.pop();

    node->left  = new TreeNode(idx++);
    node->right = new TreeNode(idx++);

    s.push(node->left);
    s.push(node->right);
  }

  return root;
}

TreeNode *get_binary_tree() {
  TreeNode *root                       = new TreeNode(1);
  root->left                           = new TreeNode(2);
  root->right                          = new TreeNode(3);
  root->left->left                     = new TreeNode(4);
  root->left->right                    = new TreeNode(5);
  root->right->left                    = new TreeNode(6);
  root->right->right                   = new TreeNode(7);
  root->left->left->right              = new TreeNode(8);
  root->right->left->left              = new TreeNode(9);
  root->right->right->left             = new TreeNode(10);
  root->right->right->right            = new TreeNode(11);
  root->left->left->right->left        = new TreeNode(12);
  root->left->left->right->right       = new TreeNode(13);
  root->right->left->left->right       = new TreeNode(14);
  root->left->left->right->right->left = new TreeNode(15);

  // TreeNode *root                   = new TreeNode(1);
  // root->right                      = new TreeNode(2);
  // root->right->right               = new TreeNode(3);
  // root->right->right->right        = new TreeNode(4);
  // root->right->right->right->right = new TreeNode(5);

  // TreeNode *root     = new TreeNode(3);
  // root->left         = new TreeNode(9);
  // root->right        = new TreeNode(20);
  // root->right->left  = new TreeNode(15);
  // root->right->right = new TreeNode(7);

  return root;
}
