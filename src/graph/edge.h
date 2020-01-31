#ifndef DIRAC_EDGE_H_
#define DIRAC_EDGE_H_

namespace dirac {
// using EType = enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD };
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;

template <typename Te>
struct Edge {
  Te data;
  int weight;
  EType type;
  Edge(Te const& e = Te(), int w = 0)
      : data(e), weight(w), type(UNDETERMINED) {}
};
}  // namespace dirac

#endif  // DIRAC_EDGE_H_