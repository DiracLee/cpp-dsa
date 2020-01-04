#ifndef DIRAC_BTNODE_CC
#define DIRAC_BTNODE_CC

#include "btnode.h"
#include <stdexcept>
#include "../stack/stack.cc"

using std::runtime_error;
namespace dirac {

/* ------------ external ----------- */

template <typename T>
void visit(const T & e) {
  std::cout << e << " ";
}

/* ------------- Tools ------------ */
template <typename T, typename VST>
void trav_pre_v1(BTNode<T> *root, VST &visit) {
  Stack<BTNode<T> *> S;
  S.push(root);
  while (!S.empty()) {
    BTNode<T> *p_node = S.pop();
    visit(p_node->data);
    if (p_node->rchild) S.push(p_node->rchild);
    if (p_node->lchild) S.push(p_node->lchild);
  }
}

template <typename T, typename VST>
void visit_along_left_branch(BTNode<T> *root, VST &visit,
                             Stack<BTNode<T> *> &S) {
  while (root) {
    visit(root->data);
    S.push(root->rchild);
    root = root->lchild;
  }
}

template <typename T, typename VST>
void trav_pre_v2(BTNode<T> *root, VST &visit) {
  Stack<BTNode<T> *> S;
  visit_along_left_branch(root, visit, S);
  while (!S.empty()) {
    root = S.pop();
    visit_along_left_branch(root, visit, S);
  }
}

/* ------------- internal ------------ */
template <typename T>
BTNode<T>::BTNode(const T &e, BTNode<T> *p, BTNode<T> *lc, BTNode<T> *rc)
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
  if (lchild) {
    throw std::runtime_error("ERROR: lchild exists but reinsert!");
    return nullptr;
  }
  p_node->parent = this;
  return lchild = p_node;
}

template <typename T>
BTNode<T> *BTNode<T>::insert_as_rc(BTNode<T> *p_node) {
  if (rchild) {
    throw std::runtime_error("ERROR: rchild exists but reinsert!");
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
void BTNode<T>::trav_pre(VST &visit) {
  trav_pre_v2(this, visit);
}

template <typename T>
template <typename VST>
void BTNode<T>::trav_in(VST &visit) {}

template <typename T>
template <typename VST>
void BTNode<T>::trav_post(VST &visit) {}

}  // namespace dirac

#endif  // DIRAC_BTNODE_CC