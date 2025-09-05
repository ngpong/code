#include "common.hpp"

bool solution(std::string s) {
  auto cvrt = [](int8_t c) -> int8_t {
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
      return c;
    } else if (c >= 'A' && c <= 'Z') {
      return c += 32;
    } else {
      return -1;
    }
  };

  int32_t i = 0, j = s.size() - 1;
  while (i <= j) {
    int8_t code0 = cvrt(s[i]);
    if (code0 < 0) {
      i++;
      continue;
    }

    int8_t code1 = cvrt(s[j]);
    if (code1 < 0) {
      j--;
      continue;
    }

    if (code0 != code1) {
      return false;
    }
    i++; j--;
  }

  return true;
}
