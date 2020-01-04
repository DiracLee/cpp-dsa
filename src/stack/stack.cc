#ifndef DIRAC_STACK_CC
#define DIRAC_STACK_CC

#include "stack.h"

namespace dirac {

template <typename T>
void Stack<T>::push(const T& e) {
  this->insert(this->size(), e);
}

template <typename T>
T Stack<T>::pop() {
  return this->remove(this->size() - 1);
}

template <typename T>
T& Stack<T>::top() {
  return (*this)[this->size() - 1];
}

}  // namespace dirac

#endif  //  DIRAC_STACK_CC