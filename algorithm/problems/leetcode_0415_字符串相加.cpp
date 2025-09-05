#include "common.hpp"

std::string solution(std::string num1, std::string num2) {
  std::string ans;

  bool carry1 = false;
  for (int32_t i = num1.size() - 1, j = num2.size() - 1; i >= 0 || j >= 0; i--, j--) {
    int32_t n1 = i >= 0 ? num1[i] - '0' : 0;
    int32_t n2 = j >= 0 ? num2[j] - '0' : 0;

    int32_t n3 = n1 + n2 + carry1;
    carry1 = false;

    if (n3 >= 10) {
      n3 %= 10;
      carry1 = true;
    }

    ans.insert(0, std::to_string(n3));
  }
  if (carry1) {
    ans.insert(0, "1");
  }

  return ans;
}
