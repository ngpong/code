#include "common.hpp"

struct Position {
  int32_t row;
  int32_t col;
};

int32_t solution1(std::vector<std::vector<char>> &grid) {
  int32_t ans = 0;
  if (grid.empty()) {
    return ans;
  }

  int32_t height = grid.size();
  int32_t length = grid[0].size();

  std::vector<std::vector<bool>> visited(height, std::vector<bool>(length, false));
  auto isvalid = [&](Position pos) {
    int32_t row = pos.row;
    int32_t col = pos.col;

    return (row >= 0 && row < height) &&
           (col >= 0 && col < length) &&
           (grid[row][col] == '1') &&
           (!visited[row][col]);
  };
  auto BFS = [&](Position cur) -> void {
    std::queue<Position> q;
    q.push(cur);
    visited[cur.row][cur.col] = true;

    while (!q.empty()) {
      auto [row, col] = q.front(); q.pop();

      Position top = { row - 1, col };
      if (isvalid(top)) {
        q.push(top);
        visited[top.row][top.col] = true;
      }

      Position bottom = { row + 1, col };
      if (isvalid(bottom)) {
        q.push(bottom);
        visited[bottom.row][bottom.col] = true;
      }

      Position left = { row, col - 1 };
      if (isvalid(left)) {
        q.push(left);
        visited[left.row][left.col] = true;
      }

      Position right = { row, col + 1 };
      if (isvalid(right)) {
        q.push(right);
        visited[right.row][right.col] = true;
      }
    }
  };

  for (int32_t row = 0; row < height; row++) {
    for (int32_t col = 0; col < length; col++) {
      if (grid[row][col] == '1' && !visited[row][col]) {
        BFS({ row, col });
        ans++;
      }
    }
  }

  return ans;
}

int32_t solution2(std::vector<std::vector<char>> &grid) {
  int32_t ans = 0;
  if (grid.empty()) {
    return ans;
  }

  int32_t height = grid.size();
  int32_t length = grid[0].size();

  std::vector<std::vector<bool>> visited(height, std::vector<bool>(length, false));
  auto dfs = [&](this const auto &dfs, Position pos) -> void {
    int32_t row = pos.row;
    int32_t col = pos.col;

    if (row < 0 || row >= height) {
      return;
    }
    if (col < 0 || col >= length) {
      return;
    }
    if (grid[row][col] == '0') {
      return;
    }
    if (visited[row][col]) {
      return;
    }

    visited[row][col] = true;

    dfs({ row - 1, col }); // ↑
    dfs({ row + 1, col }); // ↓
    dfs({ row, col - 1 }); // ←
    dfs({ row, col + 1 }); // →
  };

  for (int32_t row = 0; row < height; row++) {
    for (int32_t col = 0; col < length; col++) {
      if (grid[row][col] == '1' && !visited[row][col]) {
        dfs({ row, col });
        ans++;
      }
    }
  }

  return ans;
}
