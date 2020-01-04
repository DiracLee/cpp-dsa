#include <iostream>
#include "queue.cc"

using dirac::Queue;
using std::cout;
using std::endl;

int main() {
  Queue<int> iq;
  iq.enqueue(10);
  iq.enqueue(1);
  iq.enqueue(17);
  iq.enqueue(17);
  std::cout << iq.front() << std::endl;
  iq.dequeue();
  std::cout << iq.front() << std::endl;
  iq.dequeue();
  std::cout << iq.front() << std::endl;
  iq.dequeue();
  std::cout << iq.front() << std::endl;
  iq.dequeue();
  return 0;
}