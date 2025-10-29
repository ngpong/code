#include "common.hpp"

void solution_counting_sort(Array &arr, int32_t size) {
  int32_t max = arr[0];
  for (int32_t i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  max++;

  Array bucket(max, 0x0);
  Array sorter(size, 0x0);

  for (int32_t i = 0; i < size; i++) {
    bucket[arr[i]]++;
  }

  for (int32_t i = 1; i < max; i++) {
    bucket[i] += bucket[i - 1];
  }

  for (int32_t i = 0; i < size; i++) {
    sorter[--bucket[arr[i]]] = arr[i];
  }

  arr.swap(sorter);
}

int32_t main(void) {
  std::vector<int32_t> arr = {
    9, 8, 7, 6, 5, 5, 5, 5, 4, 3, 2, 1
  };
  solution_counting_sort(arr, arr.size());

  return EXIT_SUCCESS;
}
