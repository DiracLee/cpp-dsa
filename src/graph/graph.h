#ifndef DIRAC_GRAPH_H_
#define DIRAC_GRAPH_H_

#include "edge.h"
#include "vertex.h"

namespace dirac {

template <typename Tv, typename Te>
class Graph {
 protected:
  int n;
  int e;
  void reset() {
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

 public:
  Graph() : n(0), e(0) {}
  ~Graph();
  virtual VStatus &status(int i);
  virtual int &d_time(int i);
  virtual int &f_time(int i);
  virtual int &parent(int i);
  virtual int &priority(int i);
  virtual bool exist(int i, int j);
  virtual EType &type(int i, int j);
};

}  // namespace dirac

#endif  // DIRAC_GRAPH_H_