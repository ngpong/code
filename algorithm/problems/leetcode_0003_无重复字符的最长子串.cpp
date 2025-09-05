#include "common.hpp"

int32_t solution(std::string str) {
  int32_t lenght = 0;

  int32_t i = 0, j = -1, n = str.size();
  std::unordered_set<int8_t> us;
  while (j < n - 1) {
    j++;

    while (us.count(str[j])) {
      us.erase(str[i]);
      i++;
    }
    us.insert(str[j]);

    lenght = std::max(lenght, j - i + 1);
  }

  return lenght;
}
