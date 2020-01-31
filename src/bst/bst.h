#ifndef DIRAC_BST_H_
#define DIRAC_BST_H_

#include "../bintree/bintree.cc"

namespace dirac {

template <typename T>
class BST : public BinTree<T> {
 public:
  // 查找元素值为 e 的结点
  // 返回值为指向命中结点(哨兵)的指针，并更新_hot指向命中结点(哨兵)的父亲
  virtual BTNode<T> *search(const T &);  // 邓老师设计的指针的引用太fansy，我改成纯指针的了
  virtual BTNode<T> *insert(const T &);  // 没有指针的引用，这里只能再判断一次插入的左右方向
  virtual bool remove(const T &);

 protected:
  BTNode<T> *_hot = nullptr;
  BTNode<T> *connect34(BTNode<T> *, BTNode<T> *, BTNode<T> *, BTNode<T> *,
                       BTNode<T> *, BTNode<T> *, BTNode<T> *);
  BTNode<T> *rotate_at(BTNode<T> *);
};

}  // namespace dirac

#endif  // DIRAC_BST_H_