#include "common.hpp"

std::vector<std::string> solution(int32_t n) {
  std::vector<std::string> ans;

  [&](this const auto &backtrack, auto &&track, int32_t i = 0) -> void {
    if (n == 0) {
      return ans.push_back(track);
    }

    for (; i <= track.size(); i++) {
      track.insert(i, "()");
      n--;

      backtrack(track, i + 1);

      n++;
      //                        + i + 1 - 1                + i + 1 + 1);
      track.erase(track.begin() + i        , track.begin() + i + 2);
    }
  }(std::string());

  return ans;
}
