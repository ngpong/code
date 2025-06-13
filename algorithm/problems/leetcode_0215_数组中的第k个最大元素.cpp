#include "common.hpp"

// ====================================================================================================================
// 题目：
// 给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
//
// 请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
// ====================================================================================================================

// 快速排序
//
// - 算法与思想：
// 由快速排序的实现可知，每一次的partition都能够将序列重组为[low...lt,pivot,lt+1...high]；由于后续的操作仅会针对
// 与pivot相隔的两个分区，故我们能够认为pivot此时所在的下标与序列整体排序后一致。
//
// 基于这一点事实可得到的一个简单的想法则是：不断的执行分割序列，直至pivot的下标与k一致，此时该元素则为kth元素。
// 要知道，我们只需要找到kth的位置，故在下一次分区时可以忽略掉本身就不存在kth的那个区间。为此，我们可以在开始下一
// 次分区前pivot下标距离k的相对位置以选择左分区还是右分区。同样的，当pivot的下标与k一致时，就可认为此时找到了kth元
// 素。
//
// - 复杂度分析：
// 1. 由于并没有开放额外的空间，故我们通常说空间复杂度为O(1)
// 2. 由于快速选择只需要递归一边的数组，时间复杂度小于快速排序，期望时间复杂度为 O(n)，最坏情况下的时间复杂度为 O(n^2)
std::int32_t solution1(Array datas, std::int32_t k) {
  auto fix_pivot = make_y_combinator([&](auto fix_pivot, std::int32_t low, std::int32_t high) -> void {
    std::int32_t mid = (low + high) / 2;

    std::int32_t l = datas[low];
    std::int32_t m = datas[mid];
    std::int32_t r = datas[high];

    if ((l <= m && m <= r) || (r <= m && m <= l)) {
      std::swap(datas[low], datas[mid]);
    } else if ((l <= r && r <= m) || (m <= r && r <= l)) {
      std::swap(datas[low], datas[high]);
    }
  });

  auto quick_sort = make_y_combinator([&](auto quick_sort, std::int32_t low, std::int32_t high) -> void {
    if (low >= high) {
      return;
    }

    fix_pivot(low, high);

    std::int32_t p = datas[low];

    std::int32_t lt = low, gt = high;
    while (lt < gt) {
      while (lt < gt && datas[gt] <= p) {
        --gt;
      }
      while (lt < gt && datas[lt] >= p) {
        ++lt;
      }
      if (lt < gt) {
        std::swap(datas[lt], datas[gt]);
      }
    }
    std::swap(datas[lt], datas[low]);

    if (k - 1 < lt) {
      quick_sort(low, lt - 1);
    } else if (k - 1 > lt) {
      quick_sort(lt + 1, high);
    } else {
      return;
    }
  });

  quick_sort(0, datas.size() - 1);

  return datas[k - 1];
}

std::int32_t solution2(std::vector<int32_t> &nums, std::int32_t k) {
  auto partition = [&](int32_t low, int32_t high) -> std::pair<int32_t, int32_t> {
    if (low >= high) {
      return { low, high };
    }

    int32_t pivot = nums[low];

    int32_t lt = low, gt = high + 1, i = low + 1;
    while (i < gt) {
      if (nums[i] < pivot) {
        std::swap(nums[i++], nums[lt++]);
      } else if (nums[i] > pivot) {
        std::swap(nums[i], nums[--gt]);
      } else {
        i++;
      }
    }

    return { lt, gt };
  };

  int32_t n = nums.size();
  k = n - k;

  int32_t low = 0, high = n - 1;
  while (low <= high) {
    auto [lt, gt] = partition(low, high);
    if (k == lt) {
      return nums[k];
    } else if (k >= lt && k < gt) {
      return nums[k];
    } else if (k < lt) {
      high = lt - 1;
    } else {
      low = gt;
    }
  }
  return -1;
}

// 小顶堆
//
// - 算法与思想：
// 为找到kth元素，我们可以先利用堆的思想找到排名前k的元素。以寻找最大K举例：在序列中构建一个区间为[low...k]小顶堆，此时
// 堆顶元素为该区间内的最小；向后遍历剩余区间内的元素，挑选一个大于堆顶的元素并执行替换。和堆排序的思想一样，为保证堆平
// 衡，当堆性质被破坏后都需要重新调整堆。
//
// 当完成整个序列的遍历后，此时声明为长度为k的小顶堆即为序列中前k大的所有元素。要注意的是，此时堆顶即为我们需要找到的kth
// 的元素值。这基于一点事实：小/大顶中的堆顶节点必定会大/小于其下面的所有子节点。将此特性下放到该情景时，我们就能够发现此
// 时的堆顶元素会大于下面序列为[0...k-1]叶子节点，换句话说：堆顶元素就是kth节点
//
// - 复杂度分析：
// 1. 由于并没有开放额外的空间，即便有也仅需要关注长度为k的区间。故我们通常说空间复杂度为O(1)
// 2. 与堆排序分析一致：建堆需要O(n)的时间；单次heapify需要O(logk)的时间并且需要经历n-k次迭代；故我们说时间复杂度为O(nlogk)
std::int32_t solution3(Array nums, std::int32_t k) {
  auto heapify = [&](int32_t n, int32_t i) -> void {
    while (true) {
      int32_t l = i * 2 + 1;
      int32_t r = i * 2 + 2;

      int32_t smaller = i;
      if (l <= n && nums[smaller] > nums[l]) {
        smaller = l;
      }
      if (r <= n && nums[smaller] > nums[r]) {
        smaller = r;
      }

      if (smaller == i) break;

      std::swap(nums[i], nums[smaller]);
      i = smaller;
    }
  };

  int32_t n = k - 1;
  for (int32_t i = (n - 1) / 2; i >= 0; i--) {
    heapify(n, i);
  }
  for (int32_t i = k; i < nums.size(); i++) {
    if (nums[i] > nums[0]) {
      nums[0] = nums[i];
      heapify(n, 0);
    }
  }

  return nums[0];
}

// 采用数据分片的大小，将数据再分片，然后分布式的进行运算，比如分成 10 份，每一份再执行一次 topk 运算，最后返回十份的 topk
// 数据，在这个数据的基础上再进行 topk 即可
