#include "common.hpp"

void solution_quicksort_02(Array &arr, int32_t n) {
  auto partition = [&](int32_t low, int32_t high) -> int32_t {
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
    std::swap(arr[lt], arr[low]);

    return lt;
  };

  std::stack<std::tuple<int32_t, int32_t>> s;
  s.push({ 0, n - 1 });
  while (!s.empty()) {
    auto [low, high] = s.top(); s.pop();
    if (low >= high) {
      continue;
    }

    int32_t mid = partition(low, high);
    s.push({ mid + 1, high });
    s.push({ low, mid - 1});
  }
}

int32_t main(void) {
  std::vector<int32_t> arr = {
    9, 8, 7, 6, 5, 5, 5, 5, 4, 3, 2, 1
  };
  solution_quicksort_02(arr, arr.size());

  return EXIT_SUCCESS;
}
