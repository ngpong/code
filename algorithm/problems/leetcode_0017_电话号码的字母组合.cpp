#include "common.hpp"

std::map<char, std::vector<char>> keypad = {
  { '2', { 'a', 'b', 'c' } },
  { '3', { 'd', 'e', 'f' } },
  { '4', { 'g', 'h', 'i' } },
  { '5', { 'j', 'k', 'l' } },
  { '6', { 'm', 'n', 'o' } },
  { '7', { 'p', 'q', 'r', 's' } },
  { '8', { 't', 'u', 'v' } },
  { '9', { 'w', 'x', 'y', 'z' } },
};

std::vector<std::string> solution(std::string digits) {
  std::vector<std::string> ans;

  [&](this const auto &backtrack, int32_t pos, auto &&track) -> void {
    if (track.size() == digits.size() && track != "") {
      ans.push_back(track);
      return;
    }

    if (auto it = keypad.find(digits[pos]); it != keypad.end()) {
      auto &[_, letter] = *it;

      for (int32_t i = 0; i < letter.size(); i++) {
        track.push_back(letter[i]);
        backtrack(pos + 1, track);
        track.pop_back();
      }
    }
  }(0, std::string());

  return ans;
}
