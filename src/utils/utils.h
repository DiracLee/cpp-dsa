#ifndef DIRAC_UTILS_H
#define DIRAC_UTILS_H

namespace dirac {
// 交换算法
template <typename T>
void swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}
}  // namespace dirac

#endif // DIRAC_UTILS_H