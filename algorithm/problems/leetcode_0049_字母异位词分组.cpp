#include "common.hpp"

std::vector<std::vector<std::string>> solution1(std::vector<std::string> &strs) {
  std::unordered_map<std::string, std::vector<std::string>> hash;
  for (auto &str : strs) {
    std::string cpy = str;
    std::sort(cpy.begin(), cpy.end());
    hash[cpy].emplace_back(std::move(str));
  }

  std::vector<std::vector<std::string>> ans;
  for (auto it = hash.begin(); it != hash.end(); ) {
    auto nh = hash.extract(it++);
    ans.emplace_back(std::move(nh.mapped()));
  }

  return ans;
}

std::vector<std::vector<std::string>> solution2(std::vector<std::string> &strs) {
  std::unordered_map<std::string, std::vector<std::string>> hash;
  for (auto &str : strs) {
    std::string k(26, '0');
    for (auto &c : str) {
      k[c - 97]++;
    }
    hash[k].emplace_back(std::move(str));
  }

  std::vector<std::vector<std::string>> ans;
  for (auto it = hash.begin(); it != hash.end(); ) {
    auto nh = hash.extract(it++);
    ans.emplace_back(std::move(nh.mapped()));
  }

  return ans;
}
