#include "common.hpp"

// 普通选择排序
void solution_1(Array &arr, int32_t size) {
  for (int32_t i = 0; i < size; i++) {
    int32_t min = i;

    for (int32_t j = i + 1; j < size; j++) {
      if (arr[min] > arr[j]) {
        min = j;
      }
    }

    std::swap(arr[min], arr[i]);
  }
}

// 鸡尾酒算法优化
void solution_2(Array &arr, int32_t size) {
  int32_t l = 0, r = size - 1;

  while (l < r) {
    int32_t min = l;
    for (int32_t i = l + 1; i <= r; i++) {
      if (arr[i] < arr[min]) {
        min = i;
      }
    }
    std::swap(arr[min], arr[l]);

    int32_t max = r;
    for (int32_t i = r - 1; i > l; i--) {
      if (arr[i] > arr[max]) {
        max = i;
      }
    }
    std::swap(arr[max], arr[r]);

    ++l;
    --r;
  }
}

// 无预测分支实现
void solution_3(Array &arr, int32_t size) {
  for (int32_t i = 0; i < size; i++) {
    int32_t min = i;

    for (int32_t j = i + 1; j < size; j++) {
      int32_t diff = arr[j] - arr[min];
      int32_t mask = diff >> 31;
      min               = (min & ~mask) | (j & mask);
    }

    std::swap(arr[i], arr[min]);
  }
}

// 稳定的快速排序
void solution_4(Array &arr, int32_t size) {
  int32_t left = 0, right = size - 1;

  while (left < right) {
    int32_t min = left, max = right;

    for (int32_t i = left; i <= right; i++) {
      if (arr[i] < arr[min]) {
        min = i;
      }

      if (arr[i] > arr[max]) {
        max = i;
      }
    }

    std::swap(arr[left], arr[min]);

    if (max == left) {
      max = min;
    }

    std::swap(arr[right], arr[max]);

    ++left;
    --right;
  }
}

int32_t main(void) {
  solution_test({
    { solution_1, "普通选择排序" },
    { solution_2, "鸡尾酒算法优化" },
    { solution_3, "无预测分支实现" },
    { solution_4, "双向选择排序" },
  });

  solution_benchmark({
    { solution_1, "普通选择排序" },
    { solution_2, "鸡尾酒算法优化" },
    { solution_3, "无预测分支实现" },
    { solution_4, "双向选择排序" },
  });

  return EXIT_SUCCESS;
}
