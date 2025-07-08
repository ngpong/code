#include "common.hpp"

struct TrieNode {
  bool ended;
  std::vector<TrieNode *> childs;

  TrieNode(): childs(26), ended(false) {};
};

class Trie {
  TrieNode* m_root = new TrieNode();

  TrieNode *traverse(const std::string &word, bool alloc = false) {
    TrieNode *node = m_root;
    for (auto &c : std::as_const(word)) {
      int32_t i = c - 'a';

      TrieNode **dummy = &node->childs[i];
      if (!*dummy) {
        if (alloc) {
          *dummy = new TrieNode();
        } else {
          return nullptr;
        }
      }

      node = *dummy;
    }
    return node;
  }

public:
  Trie() {}

  void insert(std::string word) {
    TrieNode *node = traverse(word, true);
    node->ended = true;
  }

  bool search(std::string word) {
    TrieNode *node = traverse(word);
    return node ? node->ended : false;
  }

  bool startsWith(std::string prefix) {
    TrieNode *node = traverse(prefix);
    return node != nullptr;
  }
};
