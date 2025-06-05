#include "common.hpp"

// parent: (i - 1) / 2
// left_c: i * 2 + 1
// righ_c: i * 2 + 2

void solution_1(Array &arr, int32_t size) {
  auto heapify = [&](int32_t n, int32_t i) {
    while (true) {
      int32_t l = i * 2 + 1;
      int32_t r = i * 2 + 2;

      int32_t max = i;
      if (l <= n && arr[l] > arr[max]) {
        max = l;
      }
      if (r <= n && arr[r] > arr[max]) {
        max = r;
      }

      if (max == i) {
        break;
      }

      std::swap(arr[max], arr[i]);
      i = max;
    }
  };

  int32_t n = size - 1;
  for (int32_t i = (n - 1) / 2; i >= 0; i--) {
    heapify(n, i);
  }
  for (int32_t i = n; i > 0; i--) {
    std::swap(arr[0], arr[i]);
    heapify(i - 1, 0);
  }
}

int32_t main(int32_t argc, char *argv[]) {
  solution_test({
    { solution_1, "solution_1" },
  });

  solution_benchmark({
    { solution_1, "solution_1" },
  });

  return 0;
}
