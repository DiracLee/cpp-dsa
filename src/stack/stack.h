#ifndef DIRAC_STACK_H
#define DIRAC_STACK_H

#include "../vector/vector.cc"

namespace dirac {

template <typename T>
class Stack : public Vector<T> {
 public:
  void push(const T &);
  T pop();
  T &top();
};

}  // namespace dirac

#endif  //  DIRAC_STACK_H