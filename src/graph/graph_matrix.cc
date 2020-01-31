#ifndef DIRAC_GRAPH_MATRIX_CC_
#define DIRAC_GRAPH_MATRIX_CC_

#include "graph_matrix.h"

namespace dirac {

template <typename Tv, typename Te>
void GraphMatrix<Tv, Te>::reset() {
  for (int i = 0; i < n; ++i) {
    status(i) = UNDISCOVERED;
    d_time(i) = f_time(i) - 1;
    parent(i) = -1;
    priority(i) = __INT_MAX__;

    for (int j = 0; j < n; ++j) {
      if (exist(i, j)) type(i, j) = UNDISCOVERED;
    }
  }
}

template <typename Tv, typename Te>
GraphMatrix<Tv, Te>::GraphMatrix() : n(0), e(0) {}

template <typename Tv, typename Te>
GraphMatrix<Tv, Te>::~GraphMatrix() {
  for (int i = 0; i < num_vex(); i++) {
    for (int j = 0; j < num_vex(); j++) {
      delete E[i][j];
    }
  }
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::num_vex() {
  return this->n;
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::num_edge() {
  return this->e;
}

template <typename Tv, typename Te>
Tv &GraphMatrix<Tv, Te>::vertex(int i) {
  if (i < n)
    return V[i].data;
  else
    throw std::range_error("\nOut of range when call 'vertex'");
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::in_degree(int i) {
  if (i < n)
    return V[i].in_degree;
  else
    throw std::range_error("\nOut of range when call 'in_degree'");
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::out_degree(int i) {
  if (i < n)
    return V[i].out_degree;
  else
    throw std::range_error("\nOut of range when call 'outdegree'");
}

template <typename Tv, typename Te>
VStatus &GraphMatrix<Tv, Te>::status(int i) {
  if (i < n)
    return V[i].status;
  else
    throw std::range_error("\nOut of range when call 'status'");
}

template <typename Tv, typename Te>
int &GraphMatrix<Tv, Te>::d_time(int i) {
  if (i < n)
    return V[i].d_time;
  else
    throw std::range_error("\nOut of range when call 'd_time'");
}

template <typename Tv, typename Te>
int &GraphMatrix<Tv, Te>::f_time(int i) {
  if (i < n)
    return V[i].f_time;
  else
    throw std::range_error("\nOut of range when call 'f_time'");
}

template <typename Tv, typename Te>
int &GraphMatrix<Tv, Te>::parent(int i) {
  if (i < n)
    return V[i].parent;
  else
    throw std::range_error("\nOut of range when call 'parent'");
}

template <typename Tv, typename Te>
int &GraphMatrix<Tv, Te>::priority(int i) {
  if (i < n)
    return V[i].priority;
  else
    throw std::range_error("\nOut of range when call 'priority'");
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::next_nbr(int i, int j) {
  while (-1 < j && !exist(i, --j))
    ;
  return j;
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::first_nbr(int i) {
  return next_nbr(i, num_vex());
}

template <typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(Tv const &v) {
  for (int i = 0; i < n; ++i) E[i].insert(n, nullptr);
  ++n;
  E.insert(Vector<Edge<Te> *>(n << 1, n, nullptr));
  V.insert(Vertex<Tv>(v));
}

template <typename Tv, typename Te>
bool GraphMatrix<Tv, Te>::exist(int i, int j) {
  return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != nullptr;
}

template <typename Tv, typename Te>
Te &GraphMatrix<Tv, Te>::edge(int i, int j) {
  if (exist(i, j))
    return E[i][j]->data;
  else
    throw std::range_error("\nOut of range when call 'edge'");
}

template <typename Tv, typename Te>
EType GraphMatrix<Tv, Te>::type(int i, int j) {
  if (exist(i, j))
    return E[i][j]->type;
  else
    throw std::range_error("\nOut of range when call 'type'");
}

template <typename Tv, typename Te>
int GraphMatrix<Tv, Te>::weight(int i, int j) {
  if (exist(i, j))
    return E[i][j]->weight;
  else
    throw std::range_error("\nOut of range when call 'weight'");
}

template <typename Tv, typename Te>
void GraphMatrix<Tv, Te>::insert(Te const &edge, int w, int i, int j) {
  if (exist(i, j)) return;
  E[i][j] = new Edge<Te>(edge, w);
  ++e;
  ++V[i].out_degree;
  ++V[j].in_degree;
}

template <typename Tv, typename Te>
Te GraphMatrix<Tv, Te>::remove(int i, int j) {
  if (exist(i, j)) {
    Te e_bak = edge(i, j);
    delete E[i][j];
    E[i][j] = nullptr;
    --e;
    --V[i].out_degree;
    --V[j].in_degree;
    return e_bak;
  } else
    throw std::range_error("\nOut of range when call 'remove'");
}

}  // namespace dirac

#endif  // DIRAC_GRAPH_MATRIX_CC_