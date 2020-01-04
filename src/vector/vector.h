#ifndef DIRAC_VECROR_H
#define DIRAC_VECROR_H

namespace dirac {
using rank = int;

const rank DEFAULT_CAPACITY = 5;

template <typename T>
class Vector {
 private:
  int _capacity;
  int _size;
  T *_elements;

  // copy_from
  // 功能：拷贝构造函数与重载赋值运算符均用到的代码段，抽象出来
  void copy_from(const T *A, rank low, rank high);

  // expand
  // 功能：在向量中元素个数即将增加之前，进行判断
  //      容量未满则什么都不做并返回
  //      容量不到默认容量，则以默认容量为基础
  //      在基础上扩容一倍
  void expand();

  // shrink
  // 功能：在向量中元素个数即将减少之前，进行判断
  //      若元素个数不低于容量的1/4，或者容量低于默认容量
  //        则什么都不做并返回
  //      否则缩容为一半
  void shrink();

 public:
  // 默认构造函数
  Vector(int c = DEFAULT_CAPACITY, int s = 0);

  // 拷贝构造函数：数组区间复制
  Vector(const T *A, rank low, rank high);

  // 拷贝构造函数：数组整体复制
  Vector(const T *A, int n);

  // 拷贝构造函数：向量区间复制
  Vector(Vector<T> const &v, rank low, rank high);

  // 拷贝构造函数：向量整体复制
  Vector(Vector<T> const &v);

  // 析构函数
  ~Vector();

  // 重载赋值运算符
  // 功能：解决浅拷贝问题
  Vector<T> &operator=(Vector<T> const &v);

  // size
  // 功能：返回向量中元素个数
  int size() const;
  
  // empty
  // 功能：向量判空
  bool empty() const;

  // get
  // 功能：返回下标为 r 的元素的值
  T get(rank r) const;

  // put
  // 功能：将向量中下标为 r 的元素的值替换为 e
  void put(rank r, const T &e);

  // 重载[]运算符
  T &operator[](rank r) const;

  // insert
  // 功能：将元素 e 插入向量中下标为 r 的位置，其后元素下标依次加一
  void insert(rank r, T e);

  // remove
  // 功能：删除秩在区间 [low, high) 的所有元素，返回被删除元素的个数
  int remove(rank low, rank high);

  // remove
  // 功能：删除一个秩为 r 的元素
  T remove(rank r);

  // find
  // 功能：在向量[first, last]范围内查找值为 e 的元素
  //      若有多个，则返回最右侧目标元素的下标
  //      若无此元素，则返回 first-1
  rank find(T e, rank first, rank last) const;

  // find
  // 功能：在向量中查找值为 e 的元素
  //      若有多个，则返回最右侧目标元素的下标
  //      若无此元素，则返回 -1
  rank find(T e) const;

  // deduplicate
  // 功能：去重
  int deduplicate();

  // traverse
  // 适用：函数指针
  // 功能：遍历
  void traverse(void (*visit)(T &));

  // traverse
  // 适用：可调用类模板的实例、模板函数
  // 功能：遍历
  template <typename VST>
  void traverse(VST &visit);

  // 重载 < 运算符
  bool operator<(const Vector<T> &v) const;

  // 重载 >= 运算符
  bool operator>=(const Vector<T> &v) const;

  // 重载 > 运算符
  bool operator>(const Vector<T> &v) const;

  // 重载 <= 运算符
  bool operator<=(const Vector<T> &v) const;

  // disordered
  // 适用：元素类型能够进行大小判断
  // 功能：衡量向量的无序程度，数值越大越无序
  int disordered() const;

  // ordered
  // 适用：元素类型能够进行大小判断
  // 功能：判断向量是否有序
  bool ordered() const;

  // uniquify
  // 适用：有序向量
  // 功能：去重
  int uniquify();

  // search:
  // 适用：有序向量[low, high)
  // 功能：返回值为 e 的元素下标，
  //      若无此元素，则返回不超过 e 的最大元素的下标，
  //      若 e 小于向量中最小元素，则返回 low-1
  rank search(T e, rank low, rank high);

  // search:
  // 适用：有序向量
  // 功能：返回值为 e 的元素下标，
  //      若无此元素，则返回不超过 e 的最大元素的下标，
  //      若 e 小于向量中最小元素，则返回 -1
  rank search(T e);

  // sort
  // 适用：元素类型能够进行大小判断
  // 功能：对向量进行增序排序
  void sort();
};

}  // namespace dirac
#endif  // dirac_vector_h