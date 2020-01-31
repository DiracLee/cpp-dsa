#ifndef DIRAC_VERTEX_H_
#define DIRAC_VERTEX_H_

namespace dirac {
// using VStatus = enum { UNDISCOVERED, DISCOVERED, VISITED };
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;

template <typename Tv>
struct Vertex {
  Tv data;
  int in_degree;
  int out_degree;
  VStatus status;
  int d_time;
  int f_time;
  int parent;
  int priority;

  Vertex(Tv const &d = Tv())
      : data(d),
        in_degree(0),
        out_degree(0),
        status(UNDISCOVERED),
        d_time(-1),
        f_time(-1),
        parent(-1),
        priority(__INT_MAX__) {}
};
}  // namespace dirac

#endif  // DIRAC_VERTEX_H_