#include "common.hpp"

void solution1(std::vector<std::vector<int32_t>> &matrix) {
  for (int32_t min = 0, max = matrix.size() - 1; max > min; min++, max--) {
    std::tuple<int32_t, int32_t> tl = { min, min }; // top-left
    std::tuple<int32_t, int32_t> tr = { min, max }; // top-right
    std::tuple<int32_t, int32_t> bl = { max, min }; // bottom-left
    std::tuple<int32_t, int32_t> br = { max, max }; // bottom-right

    for (int32_t time = max - min; time > 0; time--) {
      auto &[tl_row, tl_col] = tl;
      auto &[tr_row, tr_col] = tr;
      auto &[bl_row, bl_col] = bl;
      auto &[br_row, br_col] = br;

      auto tl_v = matrix[tl_row][tl_col];
      auto tr_v = matrix[tr_row][tr_col];
      auto bl_v = matrix[bl_row][bl_col];
      auto br_v = matrix[br_row][br_col];

      matrix[tl_row][tl_col++] = bl_v;
      matrix[tr_row++][tr_col] = tl_v;
      matrix[bl_row--][bl_col] = br_v;
      matrix[br_row][br_col--] = tr_v;
    }
  }
}

void solution2(std::vector<std::vector<int32_t>> &matrix) {
  std::vector<std::vector<int32_t>> ans;

  int32_t m = matrix.size();
  int32_t n = matrix[0].size();

  int32_t row = m - 1, col = 0;
  while (col < n) {
    std::vector<int32_t> v;
    v.reserve(n);

    while (row >= 0) {
      v.push_back(matrix[row--][col]);
    }
    ans.emplace_back(std::move(v));

    row = m - 1; col++;
  }

  matrix.swap(ans);
}
