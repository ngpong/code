#include "common.hpp"

bool solution1(std::string s) {
  int ans = 0, left = 0, n = s.size();
  for (int i = 0; i < n; ++i) {
    if (s[i] == '(') ++left;
    else {
      if (i + 1 < n && s[i + 1] == ')') {
        ++i;
      } else {
        ++ans;
      }

      if (left > 0) {
        --left;
      } else {
        ++ans;
      }
    }
  }
  ans += left * 2;
  return ans;
};

int main(int argc, char *argv[]) {
  std::cout << solution1("))())(") << std::endl;
}
