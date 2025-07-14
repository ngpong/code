#include "common.hpp"

bool is_number(char c) {
  uint8_t code = c - '0';
  return 0 <= code && code <= 9;
}

bool is_letter(char c) {
  uint8_t code = c - 'a';
  return 0 <= code && code <= 26;
}

std::string repeat_str(const std::string &s, unsigned int n) {
  std::stringstream out;
  while (n--)
    out << s;
  return out.str();
}

std::string solution(std::string s) {
  std::string ans;

  std::stack<std::pair<int32_t, std::string>> sk;

  std::string tmp;
  for (auto &c : std::as_const(s)) {
    // 如果是数字，则放入缓存，因为后面可能还有数字，需要统计
    if (is_number(c)) {
      tmp.push_back(c);
    // 此刻代表数字结束，将数字放入栈中
    } else if (c == '[') {
      sk.push(std::make_pair(std::stoi(tmp), ""));
      tmp.clear();
    // 此刻代表需要开始处理需要被重复的字符
    } else if (c == ']') {
      auto &[count, letter] = sk.top();

      std::string rs = repeat_str(letter, count);
      sk.pop();

      if (!sk.empty()) {
        sk.top().second.append(std::move(rs));
      } else {
        ans.append(std::move(rs));
      }
    }
    // 普通字母
    else if (is_letter(c)) {
      // 栈顶为空则代表目前没有需要处理重复的字符，直接追加到答案中
      if (sk.empty()) {
        ans.push_back(c);
      } else {
        sk.top().second.push_back(c);
      }
    }
  }

  return ans;
}
