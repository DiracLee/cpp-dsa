#ifndef DIRAC_LIST_NODE_H
#define DIRAC_LIST_NODE_H
namespace dirac {

template <typename T>
struct ListNode {
  T data;
  ListNode<T> *pred;
  ListNode<T> *succ;

  // 默认构造函数：初始化 _header 和 _trailer
  ListNode();

  // 各个元素结点的构造函数
  ListNode(const T &);

  // 默认析构函数
  //   ~ListNode();

  // 将指定结点插入到本结点的前面
  ListNode<T> *insert_aspred(ListNode<T> *);

  // 将指定结点插入到本结点的后面
  ListNode<T> *insert_assucc(ListNode<T> *);

  // 创建值为 e 的结点，并将其插入到本届点的前面
  ListNode<T> *insert_aspred(const T &e);

  // 创建值为 e 的结点，并将其插入到本届点的后面
  ListNode<T> *insert_assucc(const T &e);

  // 将本结点从链接中独立出来
  ListNode<T> *isolate();
};

}  // namespace dirac

#endif  // DIRAC_LIST_NODE_H