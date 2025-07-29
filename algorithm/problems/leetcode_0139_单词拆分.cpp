#include "common.hpp"

bool solution1(std::string s, std::vector<std::string>& wordDict) {
  std::unordered_set<std::string> words(wordDict.begin(), wordDict.end());

  std::vector<int32_t> mem(s.size(), -1);
  return [&](this const auto &dfs, int32_t i) -> bool {
    if (i < 0) {
      return true;
    }

    if (mem[i] != -1) {
      return mem[i];
    }

    bool match = false;
    for (int32_t j = i; j >= 0; j--) {
      if (match) {
        break;
      }

      std::string sub = s.substr(j, i - j + 1);
      if (words.count(sub)) {
        match = dfs(j - 1);
      }
    }
    mem[i] = match;

    return match;
  }(s.size() - 1);
}

bool solution2(std::string s, std::vector<std::string>& wordDict) {
  std::unordered_set<std::string> words(wordDict.begin(), wordDict.end());

  std::vector<bool> dp(s.size(), false);
  for (int32_t i = 0; i < s.size(); i++) {
    for (int32_t j = 0; j <= i; j++) {
      std::string sub = s.substr(j, i - j + 1);
      if (words.count(sub) && (j == 0 ? true : dp[j - 1])) {
        dp[i] = true;
        break;
      }
    }
  }

  return dp[s.size() - 1];
}
