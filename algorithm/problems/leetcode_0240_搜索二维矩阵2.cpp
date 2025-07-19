#include "common.hpp"

bool searchMatrix(std::vector<std::vector<int32_t>> &matrix, int32_t target) {
  if (matrix.empty()) {
    return false;
  }

  int32_t m = matrix.size();
  int32_t n = matrix[0].size();
  for (int32_t row = 0; row < m; row++) {
    if (matrix[row][0] > target) {
      break;
    }

    if (matrix[row][n - 1] < target) {
      continue;
    }

    int32_t lt = 0, gt = n - 1;
    while (lt <= gt) {
      int32_t mid = (lt + gt) >> 1;

      int32_t num = matrix[row][mid];
      if (target > num) {
        lt = mid + 1;
      } else if (target < num) {
        gt = mid - 1;
      } else {
        return true;
      }
    }
  }

  return false;
}
