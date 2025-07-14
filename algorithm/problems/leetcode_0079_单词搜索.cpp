#include "common.hpp"

bool solution(std::vector<std::vector<char>> &board, std::string word) {
  int32_t height = board.size();
  int32_t length = board[0].size();

  bool found = false;

  auto backtrack = [&](this const auto &backtrack, int32_t row, int32_t col, int32_t i = 0) -> void {
    // 如果已找到
    if (found) {
      return;
    }

    // 是否超出边界
    if ((row < 0 || row >= height) || (col < 0 || col >= length)) {
      return;
    }

    // 是否被访问过
    if (board[row][col] == '\0') {
      return;
    }

    // 是否匹配字符
    if (board[row][col] != word[i]) {
      return;
    }

    // 是否为最后一个字符
    if (i == word.size() - 1) {
      found = true;
      return;
    }

    board[row][col] = '\0';

    backtrack(row - 1, col, i + 1); // top
    backtrack(row + 1, col, i + 1); // bottom
    backtrack(row, col - 1, i + 1); // left
    backtrack(row, col + 1, i + 1); // right

    board[row][col] = word[i];
  };

  for (int32_t row = 0; row < height; row++) {
    for (int32_t col = 0; col < length; col++) {
      backtrack(row, col);
    }
  }

  return found;
}
