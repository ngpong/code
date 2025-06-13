#include "common.hpp"

struct MinheapCMP {
  bool operator()(int x, int y) {
    return x > y;
  }
};
using Maxheap = std::priority_queue<int>;
using Minheap = std::priority_queue<int, std::vector<int>, MinheapCMP>;

int main(int argc, char *argv[]) {
  std::vector<int> m_datas = {  2, 4, 3, 1, 7, 9, 5, 8, 6, 10, 0, 13 };

  Maxheap max_heap;
  Minheap min_heap;

  for (int i = 0; i < m_datas.size(); ++i) {
    // 平均分配元素
    // 将基数下标的元素纳入最小堆
    // 将复数下标的元素纳入最大堆
    //
    // 由于下标是从 0 开始的，所以最小堆的 size 是大与最小堆的
    if ((i & 1) == 1) {
      min_heap.push(m_datas[i]);
    } else {
      max_heap.push(m_datas[i]);
    }
  }

  for (int min = min_heap.top(), max = max_heap.top(); max > min; min = min_heap.top(), max = max_heap.top()) {
    min_heap.push(max);
    max_heap.pop();
    max_heap.push(min);
    min_heap.pop();
  }

  if (max_heap.size() == min_heap.size()) {
    std::cout << (max_heap.top() + min_heap.top()) / 2 << std::endl;
  } else {
    std::cout << max_heap.top() << std::endl;
  }

  return 0;
}
