#include "common.hpp"

using Vertex = std::vector<int32_t>;
using Vertices = std::vector<Vertex>;

Vertices solution(Vertices &intervals) {
  std::sort(intervals.begin(), intervals.end(), [](const auto &lhs, const auto &rhs) {
    return std::tie(lhs[0], lhs[1]) < std::tie(rhs[0], rhs[1]);
  });

  std::vector<std::vector<int32_t>> merged;
  merged.push_back(intervals[0]);

  size_t n = intervals.size();
  for (int32_t i = 1; i < n; i++) {
    std::vector<int32_t> &inv0 = merged.back();
    std::vector<int32_t> &inv1 = intervals[i];

    int32_t lt0 = inv0[0];
    int32_t gt0 = inv0[1];
    int32_t lt1 = inv1[0];
    int32_t gt1 = inv1[1];

    if (lt0 <= lt1 && lt1 <= gt0) {
      inv0 = { lt0, std::max(gt0, gt1) };
    } else {
      merged.push_back(inv1);
    }
  }

  return merged;

作者：NGPONG
链接：https://leetcode.cn/problems/merge-intervals/solutions/3712506/56-he-bing-qu-jian-pai-xu-by-nick-cb-nsyk/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
}
