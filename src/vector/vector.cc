#ifndef DIRAC_VECTOR_CC
#define DIRAC_VECTOR_CC

#include "vector.h"
#include "../utils/utils.h"

namespace dirac {

/*------------------- Declarations -----------------*/
template <typename T>
void swap(T&, T&);

/*--------------------- Outliers -------------------*/

// 作为函数指针供 traverse 接口调用
template <typename T>
void print(T& e) {
  std::cout << e << " ";
}

// 作为函数模板供 traverse 接口调用
template <typename T>
struct Print {
  virtual void operator()(T& e) { std::cout << e << " "; };
};

// 二分查找方案 A
// 缺点：1. “返回不小于 e 的最后一个元素所在位置” 的目标未能达成
//      2. 向左与向右查找，代价不同，导致效率未达到最高
template <typename T>
rank bin_search_A(T* A, const T& e, rank low, rank high) {
  while (low < high) {
    rank mid = (low + high) >> 1;
    if (e < A[mid])
      high = mid;
    else if (A[mid < e])
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

// 二分查找方案 B
// 优点：解决了向左向右查找代价不同的问题
// 缺点：“返回不小于 e 的最后一个元素所在位置” 的目标未能达成
template <typename T>
rank bin_search_B(T* A, const T& e, rank low, rank high) {
  while (1 < high - low) {
    rank mid = (low + high) >> 1;
    (e < A[mid]) ? high = mid : low = mid;
  }
  return (e == A[low]) ? low : -1;
}

// 二分查找方案 C
// 优点：1. 解决了向左向右查找代价不同的问题
//      2. 达成了“返回不小于 e 的最后一个元素所在位置” 目标
template <typename T>
rank bin_search_C(T* A, const T& e, rank low, rank high) {
  while (low < high) {
    rank mid = (low + high) >> 1;
    (e < A[mid]) ? high = mid : low = mid + 1;
  }
  return --low;
}

// 斐波拉契查找
// 优点：解决了向左向右查找代价不同的问题
// 缺点：“返回不小于 e 的最后一个元素所在位置” 的目标未能达成
template <typename T>
rank fib_search(T* A, const T& e, rank low, rank high) {
  // TODO
  return -1;
}

// 插值查找
// 适用：近似均匀分布的有序向量
// 优点：时间复杂度最优可达 O(1)，平均也可达 O(loglogn)
// 缺点：1. 时间复杂度最坏情况下 O(n)
//      2. 容易受到局部不均匀的影响
template <typename T>
rank interpolation_sort(T* A, const T& e, rank low, rank high) {
  while (low < high) {
    rank mid = low + (high - low) * (e - A[low]) / (A[high] - A[low]);
    (e < A[mid]) ? high = mid : low = mid + 1;
  }
  return --low;
}

// 排序算法
// 适用：元素类型能够进行大小判断

// 起泡排序：稳定 O(n^2)

// 起泡方案 A
// 优点：及时判断出不在需要继续起泡的情况
template <typename T>
bool bubble_A(T* A, rank low, rank high) {
  bool ordered = true;
  while (++low < high)
    if (A[low - 1] > A[low]) {
      swap(A[low - 1], A[low]);
      ordered = false;
    }
  return ordered;
}
template <typename T>
void bubble_sort_A(T* A, rank low, rank high) {
  while (!bubble_A(A, low, high--))
    ;
}
// 起泡方案 B
// 优点：聪明地找到无需起泡的后缀，从而及时降低了问题规模
template <typename T>
rank bubble_B(T* A, rank low, rank high) {
  rank last = low;
  while (++low < high)
    if (A[low - 1] > A[low]) {
      swap(A[low - 1], A[low]);
      last = low;
    }
  return last;
}
template <typename T>
void bubble_sort_B(T* A, rank low, rank high) {
  while (low < (high = bubble_B(A, low, high)))
    ;
}

// 二路归并排序
template <typename T>
void merge(T* arr, rank low, rank mid, rank high) {
  int lb = mid - low, lc = high - mid;
  T* A = arr + low;
  T* B = new T[lb];
  for (rank i = 0; i < lb; ++i) B[i] = A[i];
  T* C = arr + mid;
  for (rank i = 0, j = 0, k = 0; j < lb;) {
    if ((k >= lc) || B[j] < C[k]) A[i++] = B[j++];
    if ((k < lc && C[k] < B[j])) A[i++] = C[k++];
  }
  delete[] B;
}
template <typename T>
void merge_sort(T* arr, rank low, rank high) {
  if (high - low < 2) return;
  rank mid = (low + high) >> 1;
  merge_sort(arr, low, mid);
  merge_sort(arr, mid, high);
  merge(arr, low, mid, high);
}

/*-------------------- Private -----------------------*/

template <typename T>
void Vector<T>::copy_from(const T* A, rank low, rank high) {
  _capacity = (high - low) << 1;
  _elements = new T[_capacity];
  _size = 0;
  while (low < high) _elements[_size++] = A[low++];
}

template <typename T>
void Vector<T>::expand() {
  if (_size < _capacity) return;
  if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
  T* old = _elements;
  _elements = new T[_capacity <<= 1];
  for (rank i = 0; i < _size; ++i) _elements[i] = old[i];
  delete[] old;
}

template <typename T>
void Vector<T>::shrink() {
  if (_size > _capacity >> 2 || _capacity < DEFAULT_CAPACITY) return;
  T* old = _elements;
  _elements = new T[_capacity >>= 1];
  for (rank i = 0; i < _size; ++i) _elements[i] = old[i];
  delete[] old;
}

/*-------------------- Public ----------------------*/

template <typename T>
Vector<T>::Vector(int c, int s) {
  _elements = new T[_capacity = c];
  _size = s;
}

template <typename T>
Vector<T>::Vector(const T* A, rank low, rank high) {
  copy_from(A, low, high);
}

template <typename T>
Vector<T>::Vector(const T* A, int n) {
  copy_from(A, 0, n);
}

template <typename T>
Vector<T>::Vector(Vector<T> const& v, rank low, rank high) {
  copy_from(v._elements, low, high);
}

template <typename T>
Vector<T>::Vector(Vector<T> const& v) {
  copy_from(v._elements, 0, v._size);
}

template <typename T>
Vector<T>::~Vector() {
  delete[] _elements;
  _size = 0;
  _capacity = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& v) {
  if (this != &v) {
    if (_elements != nullptr) delete[] _elements;
    copy_from(v._elements, 0, v._size);
  }
  return *this;
}

template <typename T>
int Vector<T>::size() const {
  return _size;
}

template <typename T>
bool Vector<T>::empty() const {
  return _size == 0;
}

template <typename T>
T Vector<T>::get(rank r) const {
  if (r >= _size || r < 0) {  // assert: 0 <= r < _size
    throw std::range_error("\nOut of range when call 'get'");
    return T();
  }
  return _elements[r];
}

template <typename T>
void Vector<T>::put(rank r, const T& e) {
  if (r >= _size || r < 0) {  // assert: 0 <= r < _size
    throw std::range_error("\nOut of range when call 'put'");
    return;
  }
  _elements[r] = e;
}

template <typename T>
T& Vector<T>::operator[](rank r) {
  if (r >= _size || r < 0) {  // assert: 0 <= r < _size
    throw std::range_error("\nOut of range when call 'operator[]'");
  }
  return _elements[r];
}

template <typename T>
void Vector<T>::insert(rank r, T e) {
  if (r > _size || r < 0) {  // assert: 0 <= r <= _size
    throw std::range_error("\nOut of range when call 'insert'");
    return;
  }
  expand();
  for (rank i = _size; i > r; --i) _elements[i] = _elements[i - 1];
  _elements[r] = e;
  ++_size;
}

template <typename T>
int Vector<T>::remove(rank low, rank high) {
  // assert: 0 <= low < high <= _size
  if (low < 0 || low >= _size || high <= 0 || high > _size || low >= high) {
    throw std::range_error("\nOut of range when call 'remove'");
    return -1;
  }
  while (high < _size) _elements[low++] = _elements[high++];
  _size = low;
  shrink();
  return high - low;
}

/*
template <typename T>
T& Vector<T>::remove(rank r) {
  // 此处返回值不能为引用，否则 e 必须定义为引用，
  // 这样的话 e 将会变成删除之后的秩为r的元素
  // 如原向量为：1, 8, 3, 4, 7, 9
  T& e = _elements[r];
  std::cout << "e = " << e << std::endl;  // 输出 3
  remove(r, r + 1);
  std::cout << "e = " << e << std::endl;  // 输出 4
  return e;
}
*/

template <typename T>
T Vector<T>::remove(rank r) {
  T e = _elements[r];
  remove(r, r + 1);
  return e;
}

template <typename T>
rank Vector<T>::find(T e, rank first, rank last) const {
  // assert: 0 <= first <= last < _size
  if (first < 0 || first >= _size || last < 0 || last >= _size ||
      first > last) {
    throw std::range_error("\nOut of range when call 'find'");
    return first - 1;
  }
  while (first <= last && _elements[last] != e) --last;
  return last;
}

template <typename T>
rank Vector<T>::find(T e) const {
  return find(e, 0, _size - 1);
}

template <typename T>
int Vector<T>::deduplicate() {
  int old_size = _size;
  rank i = 1;
  while (i < _size)
    if (find(_elements[i], 0, i - 1) < 0)
      ++i;
    else
      remove(i);
  return old_size - _size;
}
// deduplicate 的优化方案：
//    1.仿照 uniquify() 高效版的思路，元素移动的次数可降至O(n)
//      但比较次数依然是0(n^2)；而且，稳定性将被破坏
//    2.先对需删除的重复元素做标记，然后再统一删除
//      稳定性保持，但因查找长度更长，从而导致更多的比对操作
//    3.V.sort().uniquify()：简明实现最优的 O(nlogn)

template <typename T>
void Vector<T>::traverse(void (*visit)(T&)) {
  for (rank i = 0; i < _size; ++i) visit(_elements[i]);
}

template <typename T>
template <typename VST>
void Vector<T>::traverse(VST& visit) {
  for (rank i = 0; i < _size; ++i) visit(_elements[i]);
}

template <typename T>
bool Vector<T>::operator<(const Vector<T>& v) const {
  return _size < v._size;
}

template <typename T>
bool Vector<T>::operator>=(const Vector<T>& v) const {
  return _size >= v._size;
}

template <typename T>
bool Vector<T>::operator>(const Vector<T>& v) const {
  return _size > v._size;
}

template <typename T>
bool Vector<T>::operator<=(const Vector<T>& v) const {
  return _size <= v._size;
}

template <typename T>
int Vector<T>::disordered() const {
  int cnt;
  for (rank i = 1; i < _size; ++i)
    if (_elements[i - 1] > _elements[i]) ++cnt;
  return cnt;
}

template <typename T>
bool Vector<T>::ordered() const {
  return disordered() == 0;
}

// template <typename T>
// int Vector<T>::uniquify() {
//   // 此方案效率过低!
//   // 考虑极端情况：1, 1, 2, 2, 3, 3, 4, 4, ..., n, n
//   // 每经 2 轮迭代，就要进行一次 remove 操作
//   // 时间复杂度高达 O(n^2)
//   int old_size = _size;
//   rank i = 0, j = 1;
//   while (j < _size) {
//     if (_elements[i] == _elements[j])
//       ++j;
//     else {
//       ++i;
//       remove(i, j);
//       j = i + 1;
//     }
//   }
//   return old_size - _size;
// }

template <typename T>
int Vector<T>::uniquify() {
  rank i = 0, j = 0;
  while (++j < _size)
    if (_elements[i] != _elements[j]) _elements[++i] = _elements[j];
  _size = ++i;
  shrink();
  return j - i;
}

template <typename T>
rank Vector<T>::search(T e, rank low, rank high) {
  return bin_search_C(_elements, e, low, high);
}

template <typename T>
rank Vector<T>::search(T e) {
  return search(e, 0, _size);
}

template <typename T>
void Vector<T>::sort() {
  merge_sort(_elements, 0, _size);
}

}  // namespace dirac

#endif  // DIRAC_VECTOR_CC