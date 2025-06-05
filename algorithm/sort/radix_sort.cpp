#include "common.hpp"

// 基数排序

void solution_1(Array &arr, int32_t size) {
  auto digit = [&](int32_t num, int32_t exp) -> int32_t {
    return (num / exp) % 10;
  };

  auto radix_count = [&](int32_t exp) -> void {
    Array sorter(size, 0x0);
    Array bucket(10, 0x0);

    for (int32_t i = 0; i < size; i++) {
      bucket[digit(arr[i], exp)]++;
    }

    for (int32_t i = 1; i < 10; i++) {
      bucket[i] += bucket[i - 1];
    }

    for (int32_t i = size - 1; i >= 0; i--) {
      sorter[--bucket[digit(arr[i], exp)]] = arr[i];
    }

    for (int32_t i = 0; i < size; i++) {
      arr[i] = sorter[i];
    }
  };

  int32_t max = arr[0];
  for (int32_t i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  for (int32_t exp = 1; max / exp > 0; exp *= 10) {
    radix_count(exp);
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
