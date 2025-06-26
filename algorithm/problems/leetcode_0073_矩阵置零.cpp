#include "common.hpp"

void solution1(std::vector<std::vector<int32_t>> &matrix) {
  int32_t m = matrix.size();
  int32_t n = matrix[0].size();

  std::unordered_set<int32_t> zero_row;
  std::unordered_set<int32_t> zero_col;
  for (int32_t row = 0; row < m; row++) {
    for (int32_t col = 0; col < n; col++) {
      if (!matrix[row][col]) {
        zero_row.insert(row);
        zero_col.insert(col);
      }
    }
  }

  for (auto &row : zero_row) {
    for (int32_t col = 0; col < n; col++) {
      matrix[row][col] = 0;
    }
  }
  for (auto &col : zero_col) {
    for (int32_t row = 0; row < m; row++) {
      matrix[row][col] = 0;
    }
  }
}

void solution2(std::vector<std::vector<int32_t>> &matrix) {
  int32_t m = matrix.size();
  int32_t n = matrix[0].size();

  bool flg_row0 = false, flg_col0 = false;

  for (int32_t row = 0; row < m; row++) {
    for (int32_t col = 0; col < n; col++) {
      if (matrix[row][col] == 0) {
        if (row == 0) {
          flg_row0 = true;
        }
        if (col == 0) {
          flg_col0 = true;
        }

        matrix[row][0] = 0;
        matrix[0][col] = 0;
      }
    }
  }

  for (int32_t row = 1; row < m; row++) {
    if (matrix[row][0] == 0) {
      for (int32_t col = 1; col < n; col++) {
        matrix[row][col] = 0;
      }
    }
  }

  for (int32_t col = 1; col < n; col++) {
    if (matrix[0][col] == 0) {
      for (int32_t row = 1; row < m; ++row) {
        matrix[row][col] = 0;
      }
    }
  }

  if (flg_row0) {
    for (int32_t col = 1; col < n; col++) {
      matrix[0][col] = 0;
    }
  }
  if (flg_col0) {
    for (int32_t row = 1; row < m; ++row) {
      matrix[row][0] = 0;
    }
  }
}
