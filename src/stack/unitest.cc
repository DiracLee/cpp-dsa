#include <iostream>
#include "stack.cc"

using dirac::Stack;
using std::cout;
using std::endl;

int main() {
  Stack<int> is;
  is.push(0);
  is.push(9);
  is.push(18);
  is.push(3);
  std::cout << is.pop() << std::endl;
  std::cout << is.pop() << std::endl;
  std::cout << is.pop() << std::endl;
  std::cout << is.pop() << std::endl;
  return 0;
}