#include <fstream>
#include "common.hpp"

void qsort(std::fstream &logger, std::vector<int32_t> &arr, int32_t low, int32_t high) {
  if (low >= high) {
    // logger << "low >= high; " << "low: " << low << ", high: " << high << std::endl;
    return;
  }

  int32_t pivot = arr[low];

  int32_t lt = low + 1, gt = high;
  while (true) {
    while (lt <= gt && pivot < arr[gt]) {
      --gt;
    }
    while (lt <= gt && pivot > arr[lt]) {
      ++lt;
    }
    if (lt >= gt) {
      break;
    }

    // logger << "std::swap; " << "left: " << lt << ", right: " << gt << std::endl;
    std::swap(arr[lt], arr[gt]);
    lt++;
    gt--;
  }
  // logger << "std::swap; " << "left: " << gt << ", right: " << low << std::endl;
  std::swap(arr[gt], arr[low]);

  // logger << "qsort; " << "low: " << low << ", high: " << gt -1 << std::endl;
  qsort(logger, arr, low, gt - 1);
  // logger << "qsort; " << "low: " << gt + 1 << ", high: " << high << std::endl;
  qsort(logger, arr, gt + 1, high);
}

int32_t main (int32_t argc, char *argv[]) {
  std::vector<int32_t> nums = {};
  std::ifstream f("nums");
  int32_t num;
  while (f >> num) {
    nums.push_back(num);
  }
  f.close();

  std::fstream logger("test2.log", std::ios::out);
  qsort(logger, nums, 0, nums.size() - 1);
  logger.close();

  return 0;
}
