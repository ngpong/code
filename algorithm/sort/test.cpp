#include <iostream>
#include <vector>
#include <memory>
#include <cstring>

void printarr(int32_t *arr, int32_t size) {
  for (int32_t i = 0; i < size; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

void radix_count(int32_t *arr, int32_t size, int32_t exp) {
  std::vector<int32_t> sorter(size, 0x0);
  std::vector<int32_t> bucket(10, 0x0);

  for (int32_t i = 0; i < size; i++) {
    bucket[(arr[i] / exp) % 10]++;
  }

  for (int32_t i = 1; i < 10; i++) {
    bucket[i] += bucket[i - 1];
  }

  // for (int32_t i = 0; i < size; i++) {
  for (int32_t i = size - 1; i >= 0; i--) {
    sorter[--bucket[(arr[i] / exp) % 10]] = arr[i];
  }
  // printarr(sorter, 10);

  for (int32_t i = 0; i < size; i++) {
    arr[i] = sorter[i];
  }
}

void radix_sort(int32_t *arr, int32_t size) {
  int32_t max = arr[0];
  for (int32_t i = 0; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }

  for (int32_t exp = 1; max / exp > 0; exp *= 10) {
    radix_count(arr, size, exp);
  }
}

int32_t main (int32_t argc, char *argv[]) {
  int32_t arr[] = { 9, 34, 9, 65, 11, 1, 5, 12, 89, 42 };
  int32_t size = sizeof(arr) / sizeof(*arr);
  printarr(arr, size);
  radix_sort(arr, size);
  printarr(arr, size);

  return 0;
}
