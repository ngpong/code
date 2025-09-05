#include "common.hpp"

int32_t solution(std::vector<int32_t> &stones) {
  std::priority_queue<int32_t> heap(stones.begin(), stones.end());

  while (heap.size() > 1) {
    int32_t s0 = heap.top(); heap.pop();
    int32_t s1 = heap.top(); heap.pop();

    if (s0 > s1) {
      heap.push(s0 - s1);
    }
  }

  return heap.empty() ? 0 : heap.top();
}
