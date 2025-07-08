#include "common.hpp"

struct Position {
  int32_t row;
  int32_t col;
};

int32_t solution(std::vector<std::vector<int32_t>>& grid) {
  int32_t ans = 0;
  if (grid.empty()) {
    return ans;
  }

  int32_t height = grid.size();
  int32_t length = grid[0].size();

  int32_t fresh_oranges_count = 0;
  std::queue<Position> rotten_oranges;

  for (int32_t row = 0; row < height; row++) {
    for (int32_t col = 0; col < length; col++) {
      int32_t orange = grid[row][col];
      if (orange == 1) {
        fresh_oranges_count++;
      }
      else if (orange == 2) {
        rotten_oranges.push({ row, col });
      }
    }
  }

  auto rotting = [&](Position &pos) -> void {
    if (pos.row < 0 || pos.row >= height) {
      return;
    }
    if (pos.col < 0 || pos.col >= length) {
      return;
    }
    if (grid[pos.row][pos.col] != 1) {
      return;
    }

    rotten_oranges.push(pos);
    grid[pos.row][pos.col] = 2;
    fresh_oranges_count--;
  };
  while (!rotten_oranges.empty()) {
    for (int32_t n = rotten_oranges.size(); n > 0; n--) {
      Position pos = rotten_oranges.front(); rotten_oranges.pop();

      Position top = { pos.row - 1, pos.col };
      rotting(top);

      Position bottom = { pos.row + 1, pos.col };
      rotting(bottom);

      Position left = { pos.row, pos.col - 1 };
      rotting(left);

      Position right = { pos.row, pos.col + 1 };
      rotting(right);
    }

    if (!rotten_oranges.empty()) {
      ans++;
    }
  }

  if (fresh_oranges_count > 0) {
    return -1;
  } else {
    return ans;
  }
}
