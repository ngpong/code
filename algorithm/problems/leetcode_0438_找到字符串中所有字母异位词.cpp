#include "common.hpp"

std::vector<int32_t> solution1(std::string &s, std::string &p) {
  int32_t np = p.size();
  int32_t ns = s.size();

  std::string alphabet0(26, '0');
  for (int32_t i = 0; i < np; i++) {
    alphabet0[p[i] - 97]++;
  }

  std::vector<int32_t> ans;

  std::string alphabet1(26, '0');
  for (int32_t i = 0; i < np; i++) {
    alphabet1[s[i] - 97]++;
  }
  if (alphabet0 == alphabet1) {
    ans.push_back(0);
  }

  for (int32_t i = 0; i < ns - np; i++) {
    alphabet1[s[i     ] - 97]--;
    alphabet1[s[i + np] - 97]++;

    if (alphabet1 == alphabet0) {
      ans.push_back(i + 1);
    }
  }

  return ans;
}

std::vector<int32_t> solution2(std::string &s, std::string &p) {
  int32_t np = p.size();
  int32_t ns = s.size();

  std::vector<int32_t> ans;

  std::string alphabet0(26, '0');
  for (int32_t i = 0; i < np; i++) {
    alphabet0[p[i] - 97]++;
  }

  int32_t lt = 0, rt = np - 1;

  std::string alphabet1(26, '0');
  for (int32_t i = lt; i <= rt; i++) {
    alphabet1[s[i] - 97]++;
  }

  while (true) {
    if (alphabet1 == alphabet0) {
      ans.push_back(lt);
    }
    if (rt == ns - 1) {
      break;
    }

    alphabet1[s[lt++] - 97]--;
    alphabet1[s[++rt] - 97]++;
  }

  return ans;
}
