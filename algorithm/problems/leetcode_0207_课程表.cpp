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
    int32_t tail = pq[0];
    int32_t head = pq[1];

    graph.vertexs[tail].value().indegree.insert(head);
    graph.vertexs[head].value().outdegree.insert(tail);
  }

  auto find_indegree0 = [&]() -> bool {
    for (int32_t i = 0; i < numCourses; i++) {
      auto &vertex = graph.vertexs[i];

      // 顶点是否被移除
      if (!vertex.has_value()) {
        continue;
      }

      // 顶点入度要等于0
      if (!vertex->indegree.empty()) {
        continue;
      }

      // 维护顶点出度元素的入度项
      for (auto &k : std::as_const(vertex->outdegree)) {
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
