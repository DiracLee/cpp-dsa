#ifndef DIRAC_LIST_H
#define DIRAC_LIST_H

#include "list_node.cc"

namespace dirac {

template <typename T>
class List {
 private:
  ListNode<T>* _header;   // 表头结点指针
  ListNode<T>* _trailer;  // 表尾结点指针
  int _size;              // 列表长度

  // 初始化出一个空列表
  void init();
  // 在 [p_node, p_node+n) 之间寻找元素值最大的结点
  ListNode<T>* select_max(ListNode<T>* p_node, int n) const;

  // 选择排序
  void selection_sort(ListNode<T>* p_node, int n);

  // 插入排序
  void insertion_sort(ListNode<T>* p_node, int n);

 public:
  // 默认构造函数
  List();

  // 拷贝构造函数
  List(const List<T>& l);

  // 析构函数
  ~List();

  // 判断本列表操作的指针是否指向本列表中的元素结点
  bool valid(ListNode<T>* p_node) const;

  // 返回第一个结点指针
  ListNode<T>* first() const;

  // 返回最后一个结点指针
  ListNode<T>* last() const;

  // 返回列表长度
  int size() const;

  // 列表判空
  bool empty() const;

  // 在无序列表 [p_posi-n, p_posi) 之间从后向前查找值为 e 的结点
  // 若有多个匹配目标，返回下标最大的那个
  // 若未找到，返回 nullptr
  ListNode<T>* find(const T& e, int n, ListNode<T>* p_posi) const;

  // 在无序列表 (p_posi, p_posi+n] 之间从前向后查找值为 e 的结点
  // 若有多个匹配目标，返回下标最小的那个
  // 若未找到，返回 nullptr
  ListNode<T>* find(const T& e, ListNode<T>* p_posi, int n) const;

  // 在无序列表中从前向后查找值为 e 的结点
  // 若有多个匹配目标，返回下标最小的那个
  // 若未找到，返回 nullptr
  ListNode<T>* find(const T& e) const;

  // 在 p_posi 之前插入独立结点 p_node
  ListNode<T>* insert_before(ListNode<T>* p_node, ListNode<T>* p_posi);

  // 在 p_posi 之后插入独立结点 p_node
  ListNode<T>* insert_after(ListNode<T>* p_node, ListNode<T>* p_posi);

  // 在 p_posi 之前插入值为 e 的结点
  ListNode<T>* insert_before(const T& e, ListNode<T>* p_posi);

  // 在 p_posi 之后插入值为 e 的结点
  ListNode<T>* insert_after(const T& e, ListNode<T>* p_posi);

  // 将结点 p_node 作为第一个结点插入列表中
  ListNode<T>* insert_as_first(ListNode<T>* p_node);

  // 将结点 p_node 作为最后一个结点插入列表中
  ListNode<T>* insert_as_last(ListNode<T>* p_node);

  // 创建值为 e 的结点，并将其作为第一个结点插入列表中
  ListNode<T>* insert_as_first(const T& e);

  // 创建值为 e 的结点，并将其作为最后一个结点插入列表中
  ListNode<T>* insert_as_last(const T& e);

  // 将结点 p_node 从列表中删除
  void remove(ListNode<T>* p_node);

  // 无序列表去重
  int deduplicate();

  // 在有序列表的 [p_posi-n, p_posi) 之间从后向前查找值为 e 的结点
  // 若有多个目标，返回下标最大的那个
  // 若未找到，返回 _header
  // 配合 insert_after 使用
  ListNode<T>* search(const T& e, int n, ListNode<T>* p_posi) const;

  // 在有序列表的 (p_posi, p_posi+n] 之间从前向后查找值为 e 的结点
  // 若有多个目标，返回下标最小的那个
  // 若未找到，返回 _trailer
  // 配合 insert_before 使用
  ListNode<T>* search(const T& e, ListNode<T>* p_posi, int n) const;

  // 在有序列表中从前向后查找值为 e 的结点
  // 若有多个目标，返回下标最小的那个
  // 若未找到，返回 _trailer
  // 配合 insert_before 使用
  ListNode<T>* search(const T& e) const;

  // 有序列表去重
  int uniquify();

  // 列表排序
  void sort();

  // 列表遍历：模板函数
  template <typename VST>
  void traverse(VST& visit);

  // 列表遍历：函数指针
  void traverse(void (*visit)(const T& e));

  // << 运算符重载
};

}  // namespace dirac

#endif  // DIRAC_LIST_H