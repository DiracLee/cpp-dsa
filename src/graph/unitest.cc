#include <iostream>
#include "edge.h"
#include "graph_matrix.cc"
#include "vertex.h"

using namespace dirac;

int main() {
  /* ----------------- 测试 Vertex --------------------- */
  Vertex<int> v;
  std::cout << v.data << " " << v.in_degree << " " << v.out_degree << " "
            << v.f_time << " " << v.d_time << " " << v.parent << " "
            << v.priority << " " << v.status << std::endl;

  /* ----------------- 测试 Edge --------------------- */
  Edge<int> e;
  std::cout << e.data << " " << e.type << " " << e.weight << std::endl;

  /* --------------- 测试 GraphMatrix ---------------- */
  GraphMatrix<int, int> G;
  std::cout << G.first_nbr(0) << std::endl;
  std::cout << G.next_nbr(0, 8) << std::endl;

  try {
    std::cout << G.vertex(0) << std::endl;
    std::cout << G.in_degree(0) << std::endl;
    std::cout << G.out_degree(0) << std::endl;
    std::cout << G.status(0) << std::endl;
    std::cout << G.f_time(0) << std::endl;
    std::cout << G.d_time(0) << std::endl;
    std::cout << G.parent(0) << std::endl;
    std::cout << G.priority(0) << std::endl;

    std::cout << G.edge(0, 0) << std::endl;
    std::cout << G.type(0, 0) << std::endl;
    std::cout << G.weight(0, 0) << std::endl;
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }
  std::cout << G.exist(0, 0) << std::endl;

  G.insert(0);
  G.insert(1);
  G.insert(2);
  G.insert(3);
  G.insert(4);
  G.insert(5);

  G.insert(3, 8, 1, 4);
  std::cout << G.edge(1, 4) << std::endl;
  std::cout << G.weight(1, 4) << std::endl;
  return 0;
}