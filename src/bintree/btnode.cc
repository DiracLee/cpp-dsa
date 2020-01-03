#ifndef DIRAC_BTNODE_CC
#define DIRAC_BTNODE_CC

#include "btnode.h"

namespace dirac {

template <typename T>
BTNode<T>::BTNode(const T &e = T, BTNode<T> *p = nullptr,
                  BTNode<T> *lc = nullptr, BTNode<T> *rc = nullptr)
    : data(e), parent(p), lchild(lc), rchild(rc) {}

template <typename T>
int BTNode<T>::size() {
  int s = 1;
  if (lchild) s += lchild->size();
  if (rchild) s += rchild->size();
  return s;
}

template <typename T>
BTNode<T> *BTNode<T>::insert_as_lc(BTNode<T> *p_node) {
  if (!lchild) {
    throw std::run_time_error("ERROR: lchild exists but reinsert!");
    return nullptr;
  }
  p_node->parent = this;
  return lchild = p_node;
}

template <typename T>
BTNode<T> *BTNode<T>::insert_as_rc(BTNode<T> *p_node) {
  if (!rchild) {
    throw std::run_time_error("ERROR: rchild exists but reinsert!");
    return nullptr;
  }
  p_node->parent = this;
  return rchild = p_node;
}

template <typename T>
BTNode<T> *BTNode<T>::insert_as_lc(const T &e) {
  return insert_as_lc(new BTNode<T>(e));
}

template <typename T>
BTNode<T> *BTNode<T>::insert_as_rc(const T &e) {
  return insert_as_rc(new BTNode<T>(e));
}

template <typename T>
BTNode<T> *BTNode<T>::succ() {}

template <typename T>
template <typename VST>
void BTNode<T>::trav_level(VST &visit) {}

template <typename T>
template <typename VST>
void BTNode<T>::trav_pre(VST &visit) {}

template <typename T>
template <typename VST>
void BTNode<T>::trav_in(VST &visit) {}

template <typename T>
template <typename VST>
void BTNode<T>::trav_post(VST &visit) {}

}  // namespace dirac

#endif  // DIRAC_BTNODE_CC