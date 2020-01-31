#include <exception>
#include <iostream>
#include "vector.cc"
using dirac::DEFAULT_CAPACITY;
using dirac::rank;
using dirac::Vector;

int main() {
  // 测试默认构造函数
  Vector<int> ivec1;

  // 测试拷贝构造函数：来自数组
  int A[] = {0b11010101, 12, 4, 9, 2};
  Vector<int> ivec2(A, 1, 3);

  // 测试拷贝构造函数：来自数组
  Vector<int> ivec3(A, 5);

  // 测试拷贝构造函数：来自向量
  Vector<int> ivec4(ivec1);

  // 测试同值构造函数
  Vector<int> ivec5(10, 5, 4);
  std::cout << "\nivec5.traverse(dirac::print) 的测试结果为：\n\t";
  ivec5.traverse(dirac::print);
  std::cout << std::endl;

  // 测试将向量作为元素的默认构造函数
  Vector<Vector<int>> vvec0;

  // 测试将向量作为元素的拷贝构造函数：来源数组
  // 失效！
  // 原因：vector 的数组与 vector 的向量共用元素内存空间
  //      当析构向量之后，析构数组出现重复析构的问题
  // 根源：当对象中有指针时，赋值运算符默认浅拷贝该指针
  // 解决方案：重载赋值运算符，实现深拷贝
  // Done！
  Vector<int> B[] = {ivec1, ivec1, ivec1};
  Vector<Vector<int>> vvec1(B, 3);

  // 测试将向量作为元素的拷贝构造函数：来源向量
  Vector<Vector<int>> vvec2(vvec1);

  // 测试 size 函数
  std::cout << "vvec2.size() = " << vvec2.size() << std::endl;

  try {
    // 测试 get 函数
    std::cout << "ivec3.get(i): ";
    for (rank i = 0; i < ivec3.size(); ++i) std::cout << ivec3.get(i) << ", ";
    std::cout << std::endl;

    // 测试 put 函数
    ivec3.put(2, 4);
    std::cout << "After ivec3.put(2, 3)\n\t";
    std::cout << "ivec3.get(i): ";
    for (rank i = 0; i < ivec3.size(); ++i) std::cout << ivec3.get(i) << ", ";
    std::cout << std::endl;

    // 测试 [] 操作符
    std::cout << "ivec3[i]: ";
    for (rank i = 0; i < ivec3.size(); ++i) std::cout << ivec3[i] << ", ";
    std::cout << std::endl;

    // 测试 insert 函数
    std::cout << "After ivec3.insert(1, 8)\n\t";
    ivec3.insert(4, 1);
    std::cout << "ivec3[i]: ";
    for (rank i = 0; i < ivec3.size(); ++i) std::cout << ivec3[i] << ", ";
    std::cout << std::endl;

    // 测试 remove
    int e = ivec3.remove(2);
    std::cout << "After ivec3.remove(2), that is, " << e
              << " have been removed\n\t";
    std::cout << "ivec3[i]: ";
    for (rank i = 0; i < ivec3.size(); ++i) std::cout << ivec3[i] << ", ";
    std::cout << std::endl;

    // 测试 find
    rank r = ivec3.find(4);
    std::cout << "ivec3.find(4) = " << r;
  } catch (std::range_error e) {
    std::cerr << e.what() << std::endl;
  }

  // 测试 deduplicate
  ivec3.deduplicate();
  std::cout << "After ivec3.deduplicate()\n\t";
  std::cout << "ivec3[i]: ";
  for (rank i = 0; i < ivec3.size(); ++i) std::cout << ivec3[i] << ", ";

  // 测试 traverse：函数指针实现
  std::cout << "\nivec3.traverse(dirac::print) 的测试结果为：\n\t";
  ivec3.traverse(dirac::print);

  // 测试 traverse：可调用类模板的实例实现
  dirac::Print<int> pr;
  std::cout << "\nivec3.traverse(pr) 的测试结果为：\n\t";
  ivec3.traverse(pr);

  // 测试 traverse：模板函数实现
  std::cout << "\nivec3.traverse(dirac::print<int>) 的测试结果为：\n\t";
  ivec3.traverse(dirac::print<int>);

  // 测试 sort
  ivec3.sort();
  std::cout << "\nAfter ivec3.sort(),\n\t"
            << "ivec3[i]: ";
  ivec3.traverse(dirac::print);

  // 测试[][]

  vvec0.insert(vvec0.size(), Vector<int>(A, 5));
  vvec0.insert(vvec0.size(), Vector<int>(A, 5));
  vvec0.insert(vvec0.size(), Vector<int>(A, 5));
  vvec0.insert(vvec0.size(), Vector<int>(A, 5));
  std::cout << "\nvvec0:,\n";
  for (int i = 0; i < vvec0.size(); ++i) {
    Vector<int> ivec = vvec0[i];
    for (int j = 0; j < ivec.size(); ++j) {
      std::cout << vvec0[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}