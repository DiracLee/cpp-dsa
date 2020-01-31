#ifndef DIRAC_GRAPH_MATRIX_H_
#define DIRAC_GRAPH_MATRIX_H_

#include "../vector/vector.cc"
#include "edge.h"
#include "vertex.h"

namespace dirac {

template <typename Tv, typename Te>
class GraphMatrix {
 private:
  int n;
  int e;
  Vector<Vertex<Tv>> V;
  Vector<Vector<Edge<Te> *>> E;
  void reset();

 public:
  GraphMatrix();
  ~GraphMatrix();
  int num_vex();
  int num_edge();
  /* -------------- 顶点操作 --------------- */
  Tv &vertex(int i);       // 返回第 i 个顶点的元素值
  int in_degree(int i);    // 返回第 i 个顶点的入度
  int out_degree(int i);   // 返回第 i 个顶点的出度
  VStatus &status(int i);  // 返回第 i 个顶点的状态
  int &d_time(int i);      // 返回第 i 个顶点的
  int &f_time(int i);      // 返回第 i 个顶点的
  int &parent(int i);      // 返回第 i 个顶点的
  int &priority(int i);    // 返回第 i 个顶点的优先级
  void insert(Tv const &v); // 插入值为 v 的顶点

  /* -------------- 边操作 --------------- */

  // 返回第 i 个顶点的下一个邻接顶点(当前访问到它的第 j 个顶点)
  int next_nbr(int i, int j);

  int first_nbr(int i);  // 返回第 i 个顶点的第一个邻接顶点

  bool exist(int i, int j);  // 判断从顶点 i 到顶点 j 是否存在边

  Te &edge(int i, int j);  // 返回从顶点 i 到顶点 j 的边的元素值

  EType type(int i, int j);  // 返回从顶点 i 到顶点 j 的边的类型

  int weight(int i, int j);  // 返回从顶点 i 到顶点 j 的边的权重

  // 向顶点 i 与顶点 j 之间插入值为 edge, 权为 w 的边
  void insert(Te const &e, int w, int i, int j);

  // 删除顶点 i 与顶点 j 之间的边
  Te remove(int i, int j);
};

}  // namespace dirac

#endif  // DIRAC_GRAPH_MATRIX_H_