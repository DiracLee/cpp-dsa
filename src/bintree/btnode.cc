#ifndef DIRAC_BTNODE_CC
#define DIRAC_BTNODE_CC

#include "btnode.h"
#include <stdexcept>
#include "../queue/queue.cc"
#include "../stack/stack.cc"

using std::runtime_error;
namespace dirac {

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
void visit_along_left_branch(BTNode<T> *p_node, VST &visit,
                             Stack<BTNode<T> *> &S) {
  while (p_node) {
    visit(p_node->data);
    S.push(p_node->rchild);
    p_node = p_node->lchild;
  }
}

template <typename T, typename VST>
void trav_pre_v2(BTNode<T> *p_node, VST &visit) {
  Stack<BTNode<T> *> S;
  visit_along_left_branch(p_node, visit, S);
  while (!S.empty()) {
    p_node = S.pop();
    visit_along_left_branch(p_node, visit, S);
  }
}

template <typename T, typename VST>
void go_along_left_branch(BTNode<T> *p_node, VST &visit,
                          Stack<BTNode<T> *> &S) {
  while (p_node) {
    S.push(p_node);
    p_node = p_node->lchild;
  }
}

template <typename T, typename VST>
void trav_in_v1(BTNode<T> *p_node, VST &visit) {
  Stack<BTNode<T> *> S;
  go_along_left_branch(p_node, visit, S);
  while (!S.empty()) {
    p_node = S.pop();
    visit(p_node->data);
    p_node = p_node->rchild;
    go_along_left_branch(p_node, visit, S);
  }
}

template <typename T>
static void goto_HLVFL(Stack<BTNode<T> *> &S) {
  while (BTNode<T> *p_node = S.top())
    if (p_node->lchild) {
      if (p_node->rchild) S.push(p_node->rchild);
      S.push(p_node->lchild);
    } else
      S.push(p_node->rchild);

  S.pop();
}

template <typename T, typename VST>
void trav_post_v1(BTNode<T> *p_node, VST &visit) {
  Stack<BTNode<T> *> S;
  S.push(p_node);
  while (!S.empty()) {
    if (S.top() != p_node->parent) goto_HLVFL(S);
    p_node = S.pop();
    visit(p_node->data);
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
void BTNode<T>::trav_level(VST &visit) {
  Queue<BTNode<T> *> Q;
  Q.enqueue(this);
  while (!Q.empty()) {
    BTNode<T> *p_node = Q.front();
    visit(p_node->data);
    Q.dequeue();
    if (p_node->lchild) Q.enqueue(p_node->lchild);
    if (p_node->rchild) Q.enqueue(p_node->rchild);
  }
}

template <typename T>
template <typename VST>
void BTNode<T>::trav_pre(VST &visit) {
  trav_pre_v2(this, visit);
}

template <typename T>
template <typename VST>
void BTNode<T>::trav_in(VST &visit) {
  trav_in_v1(this, visit);
}

template <typename T>
template <typename VST>
void BTNode<T>::trav_post(VST &visit) {
  trav_post_v1(this, visit);
}

}  // namespace dirac

#endif  // DIRAC_BTNODE_CC