#include "common.hpp"

void solution_radix_sort(Array &arr, int32_t n) {
  auto digit = [](int32_t num, int32_t exp) -> int32_t {
    return (num / exp) % 10;
  };

  auto radix_count = [&](int32_t exp) -> void {
    Array sorter(n, 0x0);
    Array bucket(10, 0x0);

    for (int32_t i = 0; i < n; i++) {
      bucket[digit(arr[i], exp)]++;
    }

    for (int32_t i = 1; i < 10; i++) {
      bucket[i] += bucket[i - 1];
    }

    for (int32_t i = n - 1; i >= 0; i--) {
      sorter[--bucket[digit(arr[i], exp)]] = arr[i];
    }

    arr.swap(sorter);
  };

  int32_t max = arr[0];
  for (int32_t i = 1; i < n; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  for (int32_t exp = 1; max / exp > 0; exp *= 10) {
    radix_count(exp);
  }
}

int32_t main(void) {
  std::vector<int32_t> arr = {
    1, 15, 9, 12, 7, 3, 5, 4, 6, 21
  };
  solution_radix_sort(arr, arr.size());

  std::cout << arr << std::endl;

  return EXIT_SUCCESS;
}
