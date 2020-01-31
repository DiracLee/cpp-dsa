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

template <typename T>
T& max(T a, T b) {
  return a > b ? a : b;
}

// 访问模板函数
template <typename T>
void visit(const T& e) {
  std::cout << e << " ";
}

}  // namespace dirac

#endif  // DIRAC_UTILS_H