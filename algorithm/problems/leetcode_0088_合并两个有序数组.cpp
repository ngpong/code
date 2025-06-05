#include "common.hpp"

// 题目: 合并两个有序的数组
//
// 该算法参考归并排序在合并 left 和 right 时的操作即可

template <typename T>
T solution(T& larr, T& rarr) {
  T merged = {};

  int32_t lsize = larr.size(), i = 0;
  int32_t rsize = rarr.size(), j = 0;
  while (i < lsize && j < rsize) {
    if (larr[i] < rarr[j]) {
      merged.emplace_back(larr[i++]);
    } else {
      merged.emplace_back(rarr[j++]);
    }
  }

  while (i < lsize) {
    merged.emplace_back(larr[i++]);
  }

  while (j < rsize) {
    merged.emplace_back(rarr[j++]);
  }

  return merged;
}

std::int32_t main(std::int32_t argc, char* argv[]) {
  std::vector<int> left  = { 1, 2, 3 };
  std::vector<int> right = { 2, 5, 6 };

  std::cout << solution(left, right) << std::endl;

  return 0;
}
