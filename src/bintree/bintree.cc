#ifndef DIRAC_BINTREE_CC
#define DIRAC_BINTREE_CC
#include "bintree.h"
#include "../utils/utils.h"

namespace dirac {

template <typename T>
int stature(BTNode<T> *p_node) {
  return p_node ? p_node->height : -1;
}

template <typename T>
int BinTree<T>::update_height(BTNode<T> *p_node) {
  return p_node->height =
             1 + max<int>(stature(p_node->lchild), stature(p_node->rchild));
}

template <typename T>
void BinTree<T>::update_height_above(BTNode<T> *p_node) {
  while (p_node) {
    update_height(p_node);
    p_node = p_node->parent;
  }
}

template <typename T>
BinTree<T>::BinTree(BTNode<T> *r) : _root(r), _size(r ? 1 : 0) {}

template <typename T>
BinTree<T>::BinTree(const T &e) {
  BTNode<T> *r = new BTNode<T>(e);
  _root = r;
  _size = 1;
}

template <typename T>
BTNode<T> *BinTree<T>::root() {
  return _root;
}

template <typename T>
int BinTree<T>::size() {
  return _size;
}

template <typename T>
bool BinTree<T>::empty() {
  return _size == 0;
}

template <typename T>
BTNode<T> *BinTree<T>::insert_as_lc(const T &e, BTNode<T> *p_node) {
  ++_size;
  p_node->insert_as_lc(e);
  update_height_above(p_node);
  return p_node->lchild;
}

template <typename T>
BTNode<T> *BinTree<T>::insert_as_rc(const T &e, BTNode<T> *p_node) {
  ++_size;
  p_node->insert_as_rc(e);
  update_height_above(p_node);
  return p_node->rchild;
}

}  // namespace dirac

#endif  // DIRAC_BINTREE_CC