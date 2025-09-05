#include "common.hpp"

bool solution1(std::string s, std::string goal) {
  int32_t n = s.size();
  if (n != goal.size()) {
    return false;
  }

  for (int32_t i = 0; i < n; i++) {
    bool ok = true;
    for (int32_t j = 0; j < n; j++) {
      if (s[(i + j) % n] != goal[j]) {
        ok = false;
        break;
      }
    }

    if (ok) {
      return true;
    }
  }

  return false;
}

bool solution2(std::string s, std::string goal) {
  return s.size() == goal.size() ? (s + s).contains(goal) : false;
}
