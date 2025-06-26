#include "common.hpp"

using Vertex = std::vector<int32_t>;
using Vertices = std::vector<Vertex>;

Vertices solution(Vertices &vs) {
  std::sort(vs.begin(), vs.end(), [](const auto &lhs, const auto &rhs) {
    return std::tie(lhs[0], lhs[1]) < std::tie(rhs[0], rhs[1]);
  });

  size_t n = vs.size();
  size_t k = n - 1;
  while (k > 0) {
    auto &vi = vs[k];
    auto &vj = vs[k - 1];

    if (vi[0] >= vj[0] && vi[0] <= vj[1]) {
      vj = { vj[0], vi[1] > vj[1] ? vi[1] : vj[1] };
    } else if (vj[0] >= vi[0] && vj[0] <= vi[1]) {
      vj = { vi[0], vj[1] > vi[1] ? vj[1] : vi[1] };
    }

    k--;
    vs.pop_back();
  }

  return vs;
}
