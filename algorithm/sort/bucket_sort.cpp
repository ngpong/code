#include "common.hpp"

// 桶排序
//  * avg  ：O(n+k)
//  * worst: O(n^2 * k)
//  * best :
//
//

void solution_1(Array &arr, int32_t size) {
  int32_t max = arr[0];
  for (int32_t i = 1; i < size; i++) {
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  max++;

  Array bucket(max, 0x0);
  for (int32_t i = 0; i < size; i++) {
    bucket[arr[i]]++;
  }

  int32_t k = 0;
  for (int32_t i = 0; i < max; i++) {
    for (int32_t j = 0; j < bucket[i]; j++) {
      arr[k++] = i;
    }
  }
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
