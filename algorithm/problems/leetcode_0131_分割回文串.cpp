#include "common.hpp"

bool is_palindrome(const std::string &s) {
  bool ret = true;
  for (int32_t i = 0, j = s.size() - 1; i < j; i++, j--) {
    if (s[i] != s[j]) {
      ret = false;
      break;
    }
  }
  return ret;
}

std::vector<std::vector<std::string>> solution(std::string s) {
  std::vector<std::vector<std::string>> ans;

  [&](this const auto &backtrack, auto &&track, auto sit) -> void {
    if (sit == s.end()) {
      ans.push_back(track);
      return;
    }

    for (auto start = sit, ended = sit; ended != s.end(); ended++) {
      std::string part(sit, ended + 1);
      if (!is_palindrome(part)) {
        continue;
      }

      track.emplace_back(std::move(part));

      backtrack(track, ended + 1);

      track.pop_back();
    }
  }(std::vector<std::string>{}, s.begin());

  return ans;
}
