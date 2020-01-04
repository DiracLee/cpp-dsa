#ifndef DIRAC_QUEUE_H
#define DIRAC_QUEUE_H

#include "../list/list.cc"

namespace dirac {

template <typename T>
class Queue : public List<T> {
 public:
  void enqueue(const T &);
  void dequeue();
  T &front();
};

}  // namespace dirac

#endif  // DIRAC_QUEUE_H