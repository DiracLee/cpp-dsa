#ifndef DIRAC_LIST_CC
#define DIRAC_LIST_CC

#include "list.h"
#include "../utils/utils.h"

namespace dirac {

/* ------------Outliers ------------- */
template <typename T>
void visit(const T& e) {
  std::cout << e << " ";
}

/* ------------ Private ------------- */
template <typename T>
void List<T>::init() {
  _header = new ListNode<T>;
  _trailer = new ListNode<T>;
  _header->succ = _trailer;
  _trailer->pred = _header;
  _size = 0;
}

template <typename T>
bool List<T>::valid(ListNode<T>* p_node) const {
  return p_node && p_node != _header && p_node != _trailer;
}

template <typename T>
ListNode<T>* List<T>::select_max(ListNode<T>* p_node, int n) const {
  ListNode<T>*p_max = p_node, *p_cur = p_node;
  while (valid(p_cur = p_cur->succ) && --n > 0)
    if (p_cur->data >= p_max->data) p_max = p_cur;
  return p_max;
}

template <typename T>
void List<T>::selection_sort(ListNode<T>* p_node, int n) {
  ListNode<T>*p_head = p_node->pred, *p_tail = p_node;
  for (int i = 0; i < n; ++i) p_tail = p_tail->succ;
  while (1 < n) {
    insert_before(select_max(p_head->succ, n)->isolate(), p_tail);
    p_tail = p_tail->pred;
    --n;
  }
}

template <typename T>
void List<T>::insertion_sort(ListNode<T>* p_node, int n) {
  for (int r = 0; r < n && valid(p_node); ++r) {
    ListNode<T>* p_next = p_node->succ;
    insert_after(p_node->isolate(), search(p_node->data, r, p_node));
    p_node = p_next;
  }
}

/* ------------ Public -------------- */
template <typename T>
List<T>::List() {
  init();
}

template <typename T>
List<T>::List(const List<T>& l) {
  init();
  ListNode<T>* p_node = l._header;
  while (l.valid(p_node = p_node->succ)) insert_as_last(p_node->data);
  _size = l._size;
}

template <typename T>
List<T>::~List() {}

template <typename T>
ListNode<T>* List<T>::first() const {
  return (_header->succ != _trailer) ? _header->succ : nullptr;
}

template <typename T>
ListNode<T>* List<T>::last() const {
  return (_trailer->pred != _header) ? _trailer->pred : nullptr;
}

template <typename T>
int List<T>::size() const {
  return _size;
}

template <typename T>
bool List<T>::empty() const {
  return _size == 0;
}

template <typename T>
ListNode<T>* List<T>::find(const T& e, int n, ListNode<T>* p_posi) const {
  ListNode<T>* p_node = p_posi;
  while (n-- > 0 && valid(p_node = p_node->pred))
    if (p_node->data == e) return p_node;
  return nullptr;
}

template <typename T>
ListNode<T>* List<T>::find(const T& e, ListNode<T>* p_posi, int n) const {
  ListNode<T>* p_node = p_posi;
  while (n-- > 0 && valid(p_node = p_node->succ))
    if (p_node->data == e) return p_node;
  return nullptr;
}

template <typename T>
ListNode<T>* List<T>::find(const T& e) const {
  return find(e, _header, _size);
}

template <typename T>
ListNode<T>* List<T>::insert_before(ListNode<T>* p_node, ListNode<T>* p_posi) {
  ++_size;
  return p_posi->insert_aspred(p_node);
}

template <typename T>
ListNode<T>* List<T>::insert_after(ListNode<T>* p_node, ListNode<T>* p_posi) {
  ++_size;
  return p_posi->insert_assucc(p_node);
}

template <typename T>
ListNode<T>* List<T>::insert_before(const T& e, ListNode<T>* p_posi) {
  ListNode<T>* p_node = new ListNode<T>(e);
  return insert_before(p_node, p_posi);
}

template <typename T>
ListNode<T>* List<T>::insert_after(const T& e, ListNode<T>* p_posi) {
  ListNode<T>* p_node = new ListNode<T>(e);
  return insert_after(p_node, p_posi);
}

template <typename T>
ListNode<T>* List<T>::insert_as_first(ListNode<T>* p_node) {
  return insert_after(p_node, _header);
}

template <typename T>
ListNode<T>* List<T>::insert_as_last(ListNode<T>* p_node) {
  return insert_before(p_node, _trailer);
}

template <typename T>
ListNode<T>* List<T>::insert_as_first(const T& e) {
  return insert_after(e, _header);
}

template <typename T>
ListNode<T>* List<T>::insert_as_last(const T& e) {
  return insert_before(e, _trailer);
}

template <typename T>
void List<T>::remove(ListNode<T>* p_node) {
  p_node->isolate();
  delete p_node;
  p_node = nullptr;
  --_size;
}

template <typename T>
int List<T>::deduplicate() {
  ListNode<T>* p_ashore = last();
  ListNode<T>* p_drown = nullptr;
  int n = _size, old_size = _size;
  while (--n > 0)
    (p_drown = find(p_ashore->data, n, p_ashore)) ? remove(p_drown)
                                                    : p_ashore = p_ashore->pred;
  return old_size - _size;
}

template <typename T>
ListNode<T>* List<T>::search(const T& e, int n, ListNode<T>* p_posi) const {
  ListNode<T>* p_node = p_posi;
  while (n-- > 0 && valid(p_node = p_node->pred))
    if (p_node->data <= e) return p_node;
  return _header;
}

template <typename T>
ListNode<T>* List<T>::search(const T& e, ListNode<T>* p_posi, int n) const {
  ListNode<T>* p_node = p_posi;
  while (n-- > 0 && valid(p_node = p_node->succ))
    if (p_node->data >= e) return p_node;
  return _trailer;
}

template <typename T>
ListNode<T>* List<T>::search(const T& e) const {
  return search(e, _header, _size);
}

template <typename T>
int List<T>::uniquify() {
  int old_size = _size;
  ListNode<T>* p_ashore = first();
  ListNode<T>* p_swim;
  while (valid(p_swim = p_ashore->succ))
    if (p_swim->data == p_ashore->data)
      remove(p_swim);
    else
      p_ashore = p_swim;
  return old_size - _size;
}

template <typename T>
void List<T>::sort() {
  // selection_sort(first(), _size);
  insertion_sort(first(), _size);
}

template <typename T>
template <typename VST>
void List<T>::traverse(VST& visit) {
  for (ListNode<T>* p_node = first(); valid(p_node); p_node = p_node->succ)
    visit(p_node->data);
}

template <typename T>
void List<T>::traverse(void (*visit)(const T&)) {
  for (ListNode<T>* p_node = first(); valid(p_node); p_node = p_node->succ)
    visit(p_node->data);
}

}  // namespace dirac

#endif  // DIRAC_LIST_CC