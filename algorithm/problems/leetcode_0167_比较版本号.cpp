#include "common.hpp"

int solution(std::string version1, std::string version2) {
  int32_t n = version1.size(), m = version2.size();

  int32_t i = 0, j = 0;
  while (i < n || j < m) {
    int32_t rv1 = 0;
    for (; i < n && version1[i] != '.'; i++) {
      rv1 = rv1 * 10 + (version1[i] - '0');
    }
    i++;

    int32_t rv2 = 0;
    for (; j < m && version2[j] != '.'; j++) {
      rv2 = rv2 * 10 + (version2[j] - '0');
    }
    j++;

    if (rv1 < rv2) {
      return -1;
    } else if (rv1 > rv2) {
      return 1;
    }
  }

  return 0;
}
