#ifndef DIRAC_LIST_NODE_CC
#define DIRAC_LIST_NODE_CC

#include "list_node.h"
#include "../utils/utils.h"

namespace dirac {

template <typename T>
ListNode<T>::ListNode() {
  data = T();
  pred = nullptr;
  succ = nullptr;
}

template <typename T>
ListNode<T>::ListNode(const T &e) {
  data = e;
  pred = nullptr;
  succ = nullptr;
}

template <typename T>
ListNode<T> *ListNode<T>::insert_aspred(ListNode<T> *p_node) {
  if (pred) pred->succ = p_node;
  p_node->succ = this;
  p_node->pred = pred;
  pred = p_node;
  return p_node;
}

template <typename T>
ListNode<T> *ListNode<T>::insert_assucc(ListNode<T> *p_node) {
  if (succ) succ->pred = p_node;
  p_node->pred = this;
  p_node->succ = succ;
  succ = p_node;
  return p_node;
}

template <typename T>
ListNode<T> *ListNode<T>::insert_aspred(const T &e) {
  ListNode<T> *p_node = new ListNode<T>(e);
  return insert_aspred(p_node);
}
template <typename T>
ListNode<T> *ListNode<T>::insert_assucc(const T &e) {
  ListNode<T> *p_node = new ListNode<T>(e);
  return insert_assucc(p_node);
}

template <typename T>
ListNode<T> *ListNode<T>::isolate() {
  pred->succ = succ;
  succ->pred = pred;
  return this;
}

}  // namespace dirac

#endif  // DIRAC_LIST_NODE_CC