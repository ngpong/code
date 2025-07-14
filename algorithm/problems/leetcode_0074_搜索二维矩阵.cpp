#include "common.hpp"

bool searchMatrix(std::vector<std::vector<int32_t>> &matrix, int32_t target) {
  int32_t height = matrix.size();
  int32_t length = matrix[0].size();

  int32_t row = 0, col = matrix[0].size() - 1;
  while (row < height && col >= 0) {
    int32_t val = matrix[row][col];
    if (target > val) {
      row++;
    }
    else if (target < val) {
      col--;
    }
    else {
      return true;
    }
  }

  return false;
}
