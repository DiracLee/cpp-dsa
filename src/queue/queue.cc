#ifndef DIRAC_QUEUE_CC
#define DIRAC_QUEUE_CC

#include "queue.h"

namespace dirac
{
// 当使用基类的成员时，必须加以 this-> 来指向

template <typename T>
void Queue<T>::enqueue(const T & e) {
  this->insert_as_last(e);
}
    
template <typename T>
void Queue<T>::dequeue() {
  return this->remove(this->first());
}

template <typename T>
T &Queue<T>::front() {
  return this->first()->data;
}

} // namespace dirac


#endif  // DIRAC_QUEUE_CC