#include "common.hpp"

std::vector<int32_t> solution1(std::string letters) {
  std::vector<std::string> bucket;

  for (char c : letters) {
    int32_t n = bucket.size();

    int32_t i = 0;
    for (; i < n; i++) {
      if (bucket[i].find(c) != std::string::npos) {
        break;
      }
    }

    if (i == n) {
      bucket.push_back(std::string{ c });
    } else {
      for (int32_t j = bucket.size() - 1; j > i; j--) {
        auto &s1 = bucket[j];
        auto &s0 = bucket[j - 1];

        s0.append(s1);

        bucket.pop_back();
      }

      bucket.back() += c;
    }
  }

  std::vector<int32_t> ans;
  ans.reserve(bucket.size());

  for (auto &s : bucket) {
    ans.push_back(s.size());
  }

  return ans;
}

std::vector<int32_t> solution2(std::string s) {
  int32_t n = s.size();

  std::unordered_map<char, int32_t> um;
  for (int32_t i = 0; i < n; i++) {
    um[s[i]] = i;
  }

  std::vector<int32_t> partition;

  int32_t start = 0, end = 0;
  for (int32_t i = 0; i < n; i++) {
    end = std::max(end, um[s[i]]);
    if (end == i) {
      partition.push_back(end - start + 1);
      start = end + 1;
    }
  }

  return partition;
}
