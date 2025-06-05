#include "common.hpp"

void solution_1(Array &arr, int32_t size) {
  for (int32_t i = 1; i < size; i++) {
    int32_t k = arr[i];

    int32_t j = i - 1;
    for (; j >= 0 && k < arr[j]; j--) {
      arr[j + 1] = arr[j];
    }
    arr[j + 1] = k;
  }
}

void solution_2(Array &arr, int32_t size) {
  auto insert_sort = make_y_combinator(
    [&](auto insert_sort, int32_t i = 1) -> void {
      if (i >= size) {
        return;
      }

      int32_t key = arr[i];

      int32_t j = i - 1;
      for (; j >= 0 && key < arr[j]; --j) {
        arr[j + 1] = arr[j];
      }
      arr[j + 1] = key;

      insert_sort(++i);
    });

  insert_sort();
}

int32_t binarySearch(Array &arr, int32_t k, int32_t low, int32_t high) {
  if (high <= low)
    return (k > arr[low]) ? (low + 1) : low;

  int32_t mid = (low + high) / 2;

  if (k == arr[mid])
    return mid + 1;
  if (k > arr[mid])
    return binarySearch(arr, k, mid + 1, high);

  return binarySearch(arr, k, low, mid - 1);
}

void solution_3(Array &arr, int32_t size) {
  for (int32_t i = 1; i < size; ++i) {
    int32_t k = arr[i];

    int32_t j = i - 1;

    int32_t loc = binarySearch(arr, k, 0, j);
    while (j >= loc) {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = k;
  }
}

int main(void) {
  solution_test({
    { solution_1, "普通实现" },
    { solution_2, "递归实现" },
    { solution_3, "二分查找优化" },
  });

  solution_benchmark({
    { solution_1, "普通实现" },
    { solution_2, "递归实现" },
    { solution_3, "二分查找优化" },
  });

  return EXIT_SUCCESS;
}
