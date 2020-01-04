#ifndef DIRAC_BTNODE_H
#define DIRAC_BTNODE_H

namespace dirac {

template <typename T>
struct BTNode {
  BTNode<T> *parent, *lchild, *rchild;  // 指针域
  T data;  // 数据域
  int height;  // 在树中的高度
  
  // 默认构造函数(默认参数只在定义中声明，在实现中不再声明)
  BTNode(const T &e = T(), BTNode<T> *p = nullptr, BTNode<T> *lc = nullptr,
         BTNode<T> *rc = nullptr);
  
  // 以本结点为根的二叉树的结点个数
  int size();
  
  // 将指定结点设置为本结点的左孩子
  BTNode<T> *insert_as_lc(BTNode<T> *);
  
  // 将指定结点设置为本结点的右孩子
  BTNode<T> *insert_as_rc(BTNode<T> *);

  // 根据指定元素构造新结点，并将其设置为本结点的左孩子
  BTNode<T> *insert_as_lc(const T &);
  
  // 根据指定元素构造新结点，并将其设置为本结点的右孩子
  BTNode<T> *insert_as_rc(const T &);
  
  // 返回本结点的中序后继
  BTNode<T> *succ();
  
  // 层次遍历
  template <typename VST>
  void trav_level(VST &);
  
  // 先序遍历
  template <typename VST>
  void trav_pre(VST &);
  
  // 中序遍历
  template <typename VST>
  void trav_in(VST &);
  
  // 后序遍历
  template <typename VST>
  void trav_post(VST &);
};

}  // namespace dirac

#endif  // DIRAC_BTNODE_H