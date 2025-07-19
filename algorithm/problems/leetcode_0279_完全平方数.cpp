#include "common.hpp"

int32_t solution(int32_t n) {
  int32_t root = std::ceil(std::sqrt(n));

  std::vector<int32_t> squares;
  for (int32_t i = root; i > 0; i--) {
    squares.push_back(std::pow(i, 2));
  }

  std::unordered_map<int32_t, int32_t> mem;
  return [&](this const auto &dfs, int32_t n) -> int32_t {
    if (auto it = mem.find(n); it != mem.end()) {
      return it->second;
    }

    if (n == 0) {
      return 0;
    }

    int32_t count = INT32_MAX;
    for (auto &sq : squares) {
      if (n >= sq) {
        int32_t opt = dfs(n - sq);
        count = std::min(count, opt);
      }
    }

    count = count != INT32_MAX ? count + 1 : INT32_MAX;
    mem[n] = count;

    return count;
  }(n);
}
