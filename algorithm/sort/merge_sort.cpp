#include "common.hpp"

void solution_1(Array &arr, int32_t size) {
  auto merge = [&](int32_t l, int32_t m, int32_t r) -> void {
    int32_t lsize = m - l;
    int32_t larr[lsize];
    for (int32_t i = l; i < m; i++) {
      larr[i - l] = arr[i];
    }

    int32_t rsize = r - m + 1;
    int32_t rarr[rsize];
    for (int32_t i = m; i <= r; i++) {
      rarr[i - m] = arr[i];
    }

    int32_t i = 0, j = 0;
    int32_t k = l;
    while (i < lsize && j < rsize) {
      if (larr[i] < rarr[j]) {
        arr[k++] = larr[i++];
      } else {
        arr[k++] = rarr[j++];
      }
    }

    while (i < lsize) {
      arr[k++] = larr[i++];
    }

    while (j < rsize) {
      arr[k++] = rarr[j++];
    }
  };

  make_y_combinator([&](auto merge_sort, int32_t low, int32_t high) -> void {
    if (low == high) {
      return;
    }

    int32_t mid = (low + high) / 2;
    merge_sort(low, mid);
    merge_sort(mid + 1, high);
    merge(low, mid + 1, high);
  })(0, size - 1);
}

int32_t main (int32_t argc, char *argv[]) {
  solution_test({
    { solution_1, "solution_1" },
  });

  solution_benchmark({
    { solution_1, "solution_1" },
  });

  return 0;
}
