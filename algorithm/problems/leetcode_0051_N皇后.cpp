#include "common.hpp"

std::vector<std::vector<std::string>> solution(int32_t n) {
  std::vector<std::string> board(n, std::string(n, '.'));

  std::function<bool(int32_t, int32_t)> isvalid = [&](int32_t row, int32_t col) -> bool {
    // 正上方是否存在皇后
    for (int32_t i = row - 1; i >= 0; i--) {
      if (board[i][col] == 'Q') {
        return false;
      }
    }

    // 左上方是否存在皇后
    for (int32_t i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
      if (board[i][j] == 'Q') {
        return false;
      }
    }

    // 右上方是否存在皇后
    for (int32_t i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
      if (board[i][j] == 'Q') {
        return false;
      }
    }

    return true;
  };

  std::vector<std::vector<std::string>> ans;

  std::function<void(int32_t)> backtrack = [&](int32_t row) -> void {
    if (row == n) {
      ans.push_back(board);
      return;
    }

    for (int32_t col = 0; col < n; col++) {
      if (!isvalid(row, col)) {
        continue;
      }

      board[row][col] = 'Q';
      backtrack(row + 1);
      board[row][col] = '.';
    }
  };
  backtrack(0);

  return ans;
}
