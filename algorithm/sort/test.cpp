#include "common.hpp"

void solution_quicksort_03(Array &arr, int32_t n) {
  std::function<void(int32_t, int32_t)> qsort = [&](int32_t low, int32_t high) -> void {
    if (low >= high) {
      return;
    }

    int32_t pivot = arr[low];

    int32_t lt = low, gt = high;
    while (lt < gt) {
      while (lt < gt && arr[gt] >= pivot) {
        gt--;
      }
      while (lt < gt && arr[lt] <= pivot) {
        lt++;
      }
      if (lt < gt) {
        std::swap(arr[lt], arr[gt]);
      }
    }
    std::swap(arr[low], arr[lt]);

    qsort(low, lt - 1);
    qsort(lt + 1, high);
  };
  qsort(0, n - 1);
}

int32_t main(void) {
  std::vector<int32_t> arr = {
    9, 8, 7, 6, 5, 5, 5, 5, 4, 3, 2, 1
  };
  solution_quicksort_03(arr, arr.size());

  return EXIT_SUCCESS;
}
