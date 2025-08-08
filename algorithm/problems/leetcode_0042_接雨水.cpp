#include "common.hpp"

// 如果我们从头开始遍历所有的柱子，并计算每一项的储水高度(列面积)，那么储水高度
// 的由来由当前柱子的左右两边各自最高的那根柱子所决定的。
//
// 具体地，
// 左右两根最高的柱子，更短的那一根决定了当前项的理论可存储高度上限。
// 当前柱子的高度决定了实际可存储高度上限，因此可知要求的某一柱子的储水高度为：min(左边最高的柱子, 右边最高的柱子) - 当前柱子的高度。

int32_t solution1(std::vector<int32_t> &height) {
  int32_t ans = 0;
  for (int32_t i = 1; i < height.size() - 1; i++) {
    int32_t lmax = height[i];
    for (int32_t l = i - 1; l >= 0; l--) {
      lmax = std::max(lmax, height[l]);
    }

    int32_t rmax = height[i];
    for (int32_t r = i + 1; r < height.size(); r++) {
      rmax = std::max(rmax, height[r]);
    }

    if (int32_t diff = std::min(lmax, rmax) - height[i]; diff > 0) {
      ans += diff;
    }
  }

  return ans;
}
int32_t solution2(std::vector<int32_t> &height) {
  int32_t n = height.size();

  std::vector<int32_t> lmax(n);
  lmax[0] = height[0];
  for (int32_t i = 1; i < n; i++) {
    lmax[i] = std::max(lmax[i - 1], height[i]);
  }

  std::vector<int32_t> rmax(n);
  rmax[n - 1] = height[n - 1];
  for (int32_t i = n - 2; i >= 0; i--) {
    rmax[i] = std::max(rmax[i + 1], height[i]);
  }

  int32_t ans = 0;
  for (int32_t i = 1; i < n - 1; i++) { // 第一根柱子和最后一根柱子因为没有左右边界，不计算
    if (int32_t diff = std::min(lmax[i], rmax[i]) - height[i]; diff > 0) {
      ans += diff;
    }
  }

  return ans;
}


// 另一种按行面积计算需要两项要求：
//  1. 形成凹槽的两个柱子之间的高度与凹槽的高度，那么，我们要求的实际储水高度就和按列计算的方式一致
//
//     min(左边第一个最高的柱子, 右边第一个最高的柱子) - 当前柱子的高度。
//
//  2. 左右两个高的柱子之间的距离，为了求得面积的宽度
//
// 当得到高度与宽度后，水面积即为 height * width
int32_t solution3(std::vector<int32_t> &height) {
  std::stack<int32_t> sk;
  sk.push(0);

  int32_t ans = 0;
  for (int32_t i = 1; i < height.size(); i++) {
    while (!sk.empty() && height[i] > height[sk.top()]) {
      int32_t mid = sk.top();
      sk.pop();

      if (!sk.empty()) {
        int32_t h = std::min(height[i], height[sk.top()]) - height[mid];
        int32_t w = i - sk.top() - 1;
        ans += h * w;
      }
    }
    sk.push(i);
  }

  return ans;
}
