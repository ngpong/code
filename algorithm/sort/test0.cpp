#include "common.hpp"

int findKthLargest(std::vector<int32_t> &nums, int k) {
  auto partition = [&](int32_t low, int32_t high) -> std::pair<int32_t, int32_t> {
    if (low >= high) {
      return { low, high };
    }

    int32_t pivot = nums[low];

    int32_t lt = low, gt = high + 1, i = low + 1;
    while (i < gt) {
      if (nums[i] < pivot) {
        std::swap(nums[i++], nums[lt++]);
      } else if (nums[i] > pivot) {
        std::swap(nums[i], nums[--gt]);
      } else {
        i++;
      }
    }

    return { lt, gt };
  };

  int32_t n = nums.size();
  k = n - k;

  int32_t low = 0, high = n - 1;
  while (low <= high) {
    auto [lt, gt] = partition(low, high);
    if (k == lt) {
      return nums[k];
    } else if (k >= lt && k < gt) {
      return nums[k];
    } else if (k < lt) {
      high = lt - 1;
    } else {
      low = gt;
    }
  }
  return -1;
}

int32_t main(int32_t argc, char *argv[]) {
  //                           {1, 2, 2, 3, 3, 4, 5 ,5, 6 }
  std::vector<int32_t> nums = { 3, 2, 3, 1, 2, 4, 5, 5, 6 };
  std::cout << findKthLargest(nums, 4) << std::endl;

  return 0;
}
