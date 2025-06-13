#include "common.hpp"

// * 题目：
//  给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

using Hash  = std::unordered_map<int32_t, int32_t>;
using Map   = std::map<int32_t, std::list<int32_t>>;
using Pair  = std::pair<int32_t, int32_t>;
using Array = std::vector<int32_t>;
using Bucket = std::vector<Array>;
template <typename CMP>
using Heap  = std::priority_queue<Pair, std::vector<Pair>, CMP>;

// 堆实现
Array solution1(Array &nums, int32_t k) {
  // 0x1 统计元素出现的次数至map当中
  Hash um;
  for(auto &num : nums) {
    ++um[num];
  }

  // 0x2: 初始化优先队列（小顶堆）
  auto cmp = [&](Pair& lhs, Pair& rhs) {
    return lhs.second > rhs.second;
  };
  Heap<decltype(cmp)> minheap(cmp);

  // 0x3: 遍历map
  for(auto &[num, cnt] : um) {
    if (minheap.size() >= k) {
      // 0x5: 如果存在元素比堆顶元素大，则替换堆顶元素并重新执行heapify以将新的最小元素放置在堆顶
      auto &[_, __cnt] = minheap.top();
      if (cnt > __cnt) {
        minheap.pop();
        minheap.push({num, cnt});
      }
    } else {
      // 0x4: 使用前K个元素去构建小顶堆；当构建完毕后堆顶为前K个元素最小
      minheap.push({ num, cnt });
    }
  }

  Array ret;
  while (!minheap.empty()) {
    ret.push_back(minheap.top().first);
    minheap.pop();
  }

  return ret;
}

Array solution2(Array &nums, int32_t k) {
  Hash um;
  for(auto &num : nums) {
    ++um[num];
  }

  Map m;
  for(auto &[num, cnt] : um) {
    m[cnt].push_back(num);
  }

  Array ret;
  for (auto it = m.rbegin(); it != m.rend(); ++it) {
    auto &[cnt, lst] = *it;

    for(auto &num : lst) {
      if (ret.size() == k) {
        return ret;
      }

      ret.push_back(num);
    }
  }

  return ret;
}

Array solution3(Array &nums, int32_t k) {
  Array ret;

  [&](this const auto &qsort, int32_t low, int32_t high) -> void {
    if (low >= high) {
      return;
    }

    int32_t pivot = nums[low];

    int32_t lt = low, i = low + 1;
    while (i <= high) {
      if (nums[i] >= pivot) {
        std::swap(nums[i], nums[++lt]);
      }
      i++;
    }
    std::swap(nums[lt], nums[low]);

    if (k <= lt - low) {
      qsort(low, lt - 1);
    } else {
      for (int32_t i = low; i <= lt; i++) {
        ret.push_back(nums[i]);
      }

      if (k > lt + 1 - low) {
        qsort(lt + 1, k - (lt + 1 - low));
      }
    }
  }(0, nums.size() - 1);

  return ret;
}

Array solution4(Array &nums, int32_t k) {
  Hash cntmap;
  int32_t max_cnt = 0;
  for(auto &num : nums) {
    ++cntmap[num];
    max_cnt = std::max(max_cnt, cntmap[num]);
  }
  max_cnt++;

  Bucket bucket(max_cnt);
  for(auto &[num, cnt] : cntmap) {
    bucket[num].push_back(num);
  }

  Array ret;
  for (int32_t i = bucket.size() - 1; i >= 0 && ret.size() < k; i--) {
    for (int32_t j = 0; j < bucket[i].size(); j++) {
      ret.push_back(bucket[i][j]);
    }
  }

  return ret;
}
