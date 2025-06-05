#include "common.hpp"

void solution_1(Array &arr, int32_t size) {
  int32_t max = arr[0];
  for (int32_t i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  max += 1;

  Array counter(max, 0x0);
  Array sorter(size, 0x0);

  for (int32_t i = 0; i < size; i++) {
    counter[arr[i]] += 1;
  }

  for (int32_t i = 1; i < max; i++) {
    counter[i] += counter[i - 1];
  }

  for (int32_t i = 0; i < size; i++) {
    sorter[--counter[arr[i]]] = arr[i];
  }

  for (int32_t i = 0; i < size; i++) {
    arr[i] = sorter[i];
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
