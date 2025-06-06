#include "common.hpp"

class LRUCache {
  using List = std::list<std::pair<int, int>>;
  using Hash = std::unordered_map<int32_t, List::iterator>;

  int32_t m_capacity;
  List m_list;
  Hash m_hash;

public:
  LRUCache(int32_t capacity): m_capacity(capacity) {};

  int32_t get(int32_t k) {
    if (auto hash_it = m_hash.find(k); hash_it != m_hash.end()) {
      auto list_it = hash_it->second;
      m_list.splice(m_list.begin(), m_list, list_it);
      return list_it->second;
    } else {
      return -1;
    }
  }

  void put(int32_t k, int32_t v) {
    if (auto hash_it = m_hash.find(k); hash_it != m_hash.end()) {
      auto list_it = hash_it->second;
      list_it->second = v;
      m_list.splice(m_list.begin(), m_list, list_it);
    } else {
      m_list.emplace_front(k, v);
      m_hash.emplace(k, m_list.begin());

      if (m_list.size() > m_capacity) {
        m_hash.erase(m_list.back().first);
        m_list.pop_back();
      }
    }
  }
};

void solution() {
  LRUCache cache(2);
  cache.put(1, 1);
  cache.put(2, 2);
  std::cout << cache.get(1) << std::endl;
  cache.put(3, 3);
  std::cout << cache.get(2) << std::endl;
  cache.put(4, 4);
  std::cout << cache.get(1) << std::endl;
  std::cout << cache.get(3) << std::endl;
  std::cout << cache.get(4) << std::endl;
}

int main(int argc, char *argv[]) {
  solution();

  return 0;
}
