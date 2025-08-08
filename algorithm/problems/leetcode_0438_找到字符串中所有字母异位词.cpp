#include "common.hpp"

std::vector<int32_t> solution1(std::string &s, std::string &p) {
  std::vector<int32_t> ans;

  int32_t np = p.size();
  int32_t ns = s.size();
  if (np > ns) {
    return ans;
  }

  std::string alphabet(26, '0'), window(26, '0');
  for (int32_t i = 0; i < np; i++) {
    alphabet[p[i] - 97]++;
    window[s[i] - 97]++;
  }
  if (alphabet == window) {
    ans.push_back(0);
  }

  for (int32_t i = 0; i < ns - np; i++) {
    window[s[i     ] - 97]--;
    window[s[i + np] - 97]++;

    if (window == alphabet) {
      ans.push_back(i + 1);
    }
  }

  return ans;
}

std::vector<int32_t> solution2(std::string &s, std::string &p) {
  int32_t np = p.size();
  int32_t ns = s.size();

  std::string alphabet0(26, '0');
  for (int32_t i = 0; i < np; i++) {
    alphabet0[p[i] - 97]++;
  }

  std::vector<int32_t> ans;

  int32_t i = 0, j = np - 1;
  while (j < ns) {
    std::string alphabet1(26, '0');
    for (int32_t k = i; k <= j; k++) {
      alphabet1[s[k] - 97]++;
    }

    if (alphabet1 == alphabet0) {
      ans.push_back(i);
    }

    i++; j++;
  }

  return ans;
}
