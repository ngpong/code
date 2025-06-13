#include "common.hpp"

// 题目: 在一个无序数组中寻找中位数
//
// 将数据平均分配到最大堆和最小堆中，并且保证最小堆中的数据存放的数据都比
// 最大堆中是数据大，那么此时最小堆堆顶的元素一定是中位数
//
// 如何平均分配元素?
//  * 遍历数组，将基数下标的元素纳入最小堆，将复数下标的元素纳入最大堆

class MedianFinder {
  std::priority_queue<int, std::vector<int>, std::less<int>> m_maxheap;
  std::priority_queue<int, std::vector<int>, std::greater<int>> m_minheap;

public:
  void addNum(int num) {
    // 平均分配元素，使小顶堆和大顶堆的增长趋同
    if (m_maxheap.size() == m_minheap.size()) {
      m_maxheap.push(num);
    } else {
      m_minheap.push(num);
    }

    if (m_maxheap.empty() || m_minheap.empty()) {
      return;
    }

    // 交换大小堆顶种的内容
    //
    // 使最小堆中装载最大堆的最大
    // 使最大堆中装载最小堆的最小
    //
    // 简而言之，就是使最小堆中的数据都比最大堆中的大
    int min = m_minheap.top(), max = m_maxheap.top();
    if (min < max) {
      m_minheap.push(max);
      m_maxheap.pop();
      m_maxheap.push(min);
      m_minheap.pop();
    }
  }

  double findMedian() {
    if (m_maxheap.size() == m_minheap.size()) {
      // 当大小顶堆的长度相同时，证明数组的长度是偶数，此时并不存在中间值，需要取
      // 边界的两个值之和除以 2
      return (double)(m_maxheap.top() + m_minheap.top()) / 2;
    } else {
      // 数组的长度是奇数，存在中间值
      return m_maxheap.top();
    }
  }
};


int main(void) {
  std::vector<int> m_datas = {  2, 4, 3, 1, 7, 9, 5, 8, 6, 10, 0, 13 };

  while (!min_heap.empty() && !max_heap.empty()) {
    int min = min_heap.top(), max = max_heap.top();
    if (max > min) {
      min_heap.push(max);
      max_heap.pop();
      max_heap.push(min);
      min_heap.pop();
      min = min_heap.top(), max = max_heap.top();
    } else {
      break;
    }
  }

  if (max_heap.size() == min_heap.size()) {
    std::cout << (max_heap.top() + min_heap.top()) / 2 << std::endl;
  } else {
    std::cout << max_heap.top() << std::endl;
  }

  return EXIT_SUCCESS;
}
