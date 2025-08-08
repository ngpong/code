#include "common.hpp"

std::string solution(std::string s, std::string t) {
  std::unordered_map<char, int32_t> um_s;
  std::unordered_map<char, int32_t> um_t;

  for (int32_t i = 0; i < t.size(); i++) {
    um_t[t[i]]++;
  }

  int32_t match = 0;
  int32_t ans_start = 0, ans_len = INT32_MAX;
  for (int32_t i = 0, j = 0; j < s.size(); ) {
    if (um_t.count(s[j])) {
      um_s[s[j]]++;
      if (um_s[s[j]] == um_t[s[j]]) {
        match++;
      }
    }

    while (match == um_t.size()) {
      if (ans_len > j - i + 1) {
        ans_start = i;
        ans_len = j - i + 1;
      }

      if (um_t.count(s[i])) {
        um_s[s[i]]--;
        if (um_t[s[i]] > um_s[s[i]]) { // 不满足匹配了
          match--;
        }
      }

      i++;
    }

    j++;
  }

  if (ans_len == INT32_MAX) {
    return "";
  } else {
    return s.substr(ans_start, ans_len);
  }
}
