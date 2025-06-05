#include "common.hpp"

// 原始实现
void solution_1(Array &arr, int32_t size) {
  for (int32_t i = 0; i < size; i++) {
    for (int32_t j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

// 鸡尾酒算法优化
void solution_2(Array &arr, int32_t size) {
  int32_t left = 0, right = size - 1;

  while (left < right) {
    for (int32_t i = left; i < right; i++) {
      if (arr[i] > arr[i + 1]) {
        std::swap(arr[i], arr[i + 1]);
      }
    }
    right--;

    for (int32_t i = right; i > left; i--) {
      if (arr[i] < arr[i - 1]) {
        std::swap(arr[i], arr[i - 1]);
      }
    }
    left++;
  }
}

// 提前结束优化：避免没必要的迭代
void solution_3(Array &arr, int32_t size) {
  for (int32_t i = 0; i < size; i++) {
    bool is_swapped = false;

    for (int32_t j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
        is_swapped = true;
      }
    }

    if (!is_swapped) {
      break;
    }
  }
}

int32_t main(void) {
  solution_test({
    { solution_1, "solution_1" },
    { solution_2, "solution_2" },
    { solution_3, "solution_3" },
  });

  solution_benchmark({
    { solution_1, "solution_1" },
    { solution_2, "solution_2" },
    { solution_3, "solution_3" },
  });

  return 0;
}
