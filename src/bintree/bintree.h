#ifndef DIRAC_BINTREE_H
#define DIRAC_BINTREE_H

#include "btnode.cc"

namespace dirac {

template <typename T>
class BinTree {
 protected:
  BTNode<T> *_root;  // 根结点
  int _size;         // 总结点个数

  // 更新指定结点的高度
  virtual int update_height(BTNode<T> *p_node);

  // 更新指定结点及其祖先的高度
  void update_height_above(BTNode<T> *p_node);

  // 指定特定结点的左孩子
  BTNode<T> *insert_as_lc(BTNode<T> *, BTNode<T> *);

  // 指定特定结点的右孩子
  BTNode<T> *insert_as_rc(BTNode<T> *, BTNode<T> *);

 public:
  // 空构造函数
  BinTree();

  // 返回根节点
  BTNode<T> *root();

  // 返回总结点个数
  int size();

  // 二叉树判空
  bool empty();

  // 将指定元素插入到特定结点的左孩子域
  BTNode<T> *insert_as_lc(const T &, BTNode<T> *);

  // 将指定元素插入到特定结点的右孩子域
  BTNode<T> *insert_as_rc(const T &, BTNode<T> *);
};
}  // namespace dirac

#endif  // DIRAC_BINTREE_H