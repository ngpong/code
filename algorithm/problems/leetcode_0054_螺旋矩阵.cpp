#include "common.hpp"

std::vector<int32_t> solution(std::vector<std::vector<int32_t>>& matrix) {
  enum class DIRECTION : int8_t {
    RIGHT,
    DOWN,
    LEFT,
    UP,
  };

  std::vector<int32_t> ans;

  int32_t m = matrix.size();
  int32_t n = matrix[0].size() + 1;

  DIRECTION dit = DIRECTION::RIGHT;

  int32_t row = 0, col = 0;
  while (m && n) {
    switch (dit) {
    case DIRECTION::RIGHT: {
      for (int32_t i = --n; i > 0; i--) {
        ans.push_back(matrix[row][col++]);
      }
      col--;

      row++;
      dit = DIRECTION::DOWN;
      break;
    }
    case DIRECTION::DOWN: {
      for (int32_t i = --m; i > 0; i--) {
        ans.push_back(matrix[row++][col]);
      }
      row--;

      col--;
      dit = DIRECTION::LEFT;
      break;
    }
    case DIRECTION::LEFT: {
      for (int32_t i = --n; i > 0; i--) {
        ans.push_back(matrix[row][col--]);
      }
      col++;

      row--;
      dit = DIRECTION::UP;
      break;
    }
    case DIRECTION::UP: {
      for (int32_t i = --m; i > 0; i--) {
        ans.push_back(matrix[row--][col]);
      }
      row++;

      col++;
      dit = DIRECTION::RIGHT;
      break;
    }
    };
  }

  return ans;
}

std::vector<int> solution2(std::vector<std::vector<int32_t>>& matrix) {
  std::vector<int> ans;
  if (matrix.empty()) {
    return ans;
  }

  //           T
  //   →----------------→
  //   ↑                ↓
  //   |                |
  // L |                | R
  //   |                |
  //   ↑                ↓
  //   ←----------------←
  //           B

  int32_t L = 0, R = matrix[0].size() - 1;
  int32_t T = 0, B = matrix.size() - 1;

  while (true) {
    for (int32_t i = L; i <= R; i++) ans.push_back(matrix[T][i]); // left to right
    if (++T > B) break;
    for (int32_t i = T; i <= B; i++) ans.push_back(matrix[i][R]); // top to bottom
    if (L > --R) break;
    for (int32_t i = R; i >= L; i--) ans.push_back(matrix[B][i]); // right to left
    if (T > --B) break;
    for (int32_t i = B; i >= T; i--) ans.push_back(matrix[i][L]); // bottom to top
    if (++L > R) break;
  }

  return ans;
}
