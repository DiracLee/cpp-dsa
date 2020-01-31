#ifndef DIRAC_BST_CC_
#define DIRAC_BST_CC_

#include "bst.h"

namespace dirac {

template <typename T>
BTNode<T> *BST<T>::search(const T &e) {
  BTNode<T> *p_node = this->root();
  while (p_node) {
    if (e == p_node->data) break;
    _hot = p_node;
    if (e < p_node->data)
      p_node = p_node->lchild;
    else
      p_node = p_node->rchild;
  }
  return p_node;
}

template <typename T>
BTNode<T> *BST<T>::insert(const T &e) {
  BTNode<T> *x = search(e);
  if (!x) {
    x = new BTNode<T>(e, _hot);
    if (!_hot)
      this->_root = x;
    else {
      if (e < _hot->data)
        _hot->lchild = x;
      else
        _hot->rchild = x;
    }
    ++this->_size;
    this->update_height_above(x);
  }
  return x;
}

template <typename T>
BTNode<T> *remove_at(BTNode<T> *x, BTNode<T> *&hot) {
  BTNode<T> *w = x;
  BTNode<T> *succ = nullptr;
  if (!x->lchild)
    succ = x->rchild;
  else if (!x->rchild)
    succ = x->lchild;
  else {
    w = w->succ();
    swap(x->data, w->data);
    BTNode<T> *u = w->parent;
    (u == x ? u->rchild : u->lchild) = succ = w->rchild;
  }
  hot = w->parent;
  if (succ) succ->parent = hot;
  delete w;
  return succ;
}

template <typename T>
bool BST<T>::remove(const T &e) {
  BTNode<T> *x = search(e);
  if (!x) return false;
  remove_at(x, _hot);
  --this->_size;
  if (!_hot)
    this->_root = nullptr;
  else
    this->update_height_above(_hot);

  return true;
}

}  // namespace dirac

#endif  //  DIRAC_BST_CC_