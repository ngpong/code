#include "common.hpp"

bool solution(std::string &s) {
  if (s.size() % 2 == 1) {
    return false;
  }

  std::unordered_map<char, char> um = {
    { ')', '(' },
    { '}', '{' },
    { ']', '[' },
  };
  std::stack<char> sk;
  for (auto c : s) {
    if (auto it = um.find(c); it != um.end()) {
      if (!sk.empty() && sk.top() == it->second) {
        sk.pop();
      } else {
        return false;
      }
    } else {
      sk.push(c);
    }
  }

  return sk.empty();
}
