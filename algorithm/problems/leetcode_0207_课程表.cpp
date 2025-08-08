#include "common.hpp"

struct Vertex {
  std::unordered_set<int32_t> indegree;
  std::unordered_set<int32_t> outdegree;
};

struct Graph {
  std::vector<std::optional<Vertex>> vertexs;
  Graph(size_t length): vertexs(length, Vertex()) {}
};

bool solution(int32_t numCourses, std::vector<std::vector<int32_t>> &prerequisites) {
  Graph graph(numCourses);

  for (auto &pq : std::as_const(prerequisites)) {
    // 想要学习 pq[0] 时必须先完成 pq[1]，因此：
    //  * pq[1] --> pq[0]
    //  * pq[1] 是 pq[0] 的入度
    //  * pq[0] 是 pq[1] 的出度
    graph.vertexs[pq[0]]->indegree.insert(pq[1]);
    graph.vertexs[pq[1]]->outdegree.insert(pq[0]);
  }

  auto find_indegree0 = [&]() -> bool {
    for (int32_t i = 0; i < numCourses; i++) {
      // 顶点是否被移除
      if (!graph.vertexs[i].has_value()) {
        continue;
      }

      // 顶点入度要等于0
      if (!graph.vertexs[i]->indegree.empty()) {
        continue;
      }

      // 维护顶点出度元素的入度项
      for (auto &k : std::as_const(graph.vertexs[i]->outdegree)) {
        graph.vertexs[k]->indegree.erase(i);
      }

      // 删除顶点
      graph.vertexs[i] = std::nullopt;

      return true;
    }

    return false;
  };

  int32_t topcount = 0;
  while (find_indegree0()) {
    topcount++;
  }

  return topcount == numCourses;
}
