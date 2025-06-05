#include "common.hpp"

void solution_1(Array &arr, int32_t size) {
  for (int32_t gs = size / 2; gs > 0; gs /= 2) {
    for (int32_t i = gs; i < size; i++) {
      int32_t k = arr[i];

      int32_t j = i;
      for (; j >= gs && k < arr[j - gs]; j -= gs) {
        arr[j] = arr[j - gs];
      }
      arr[j] = k;
    }
  }
}

int main(int argc, char *argv[]) {
  solution_test({
    { solution_1, "solution_1" },
  });

  solution_benchmark({
    { solution_1, "solution_1" },
  });

  return EXIT_SUCCESS;
}
