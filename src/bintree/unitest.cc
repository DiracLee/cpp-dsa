#include <iostream>
#include "bintree.cc"
#include "btnode.cc"

using dirac::BinTree;
using dirac::BTNode;
using dirac::visit;
using std::cout;
using std::endl;

int main() {
  /* ----------- 测试 BTNode ------------ */
  BTNode<int> node1;  // 空构造函数
  std::cout << node1.data << std::endl;
  BTNode<int> node2(23);  // 指定元素构造函数
  std::cout << node2.data << std::endl;
  BTNode<int> node3(18);  // 指定元素构造函数
  std::cout << node3.data << std::endl;

  // 测试插入函数
  node1.insert_as_lc(&node2);
  node1.insert_as_rc(&node3);

  // 测试先序遍历
  node1.trav_pre(visit<int>);
  cout << endl;
  
  // 测试中序遍历
  node1.trav_in(visit<int>);
  cout << endl;

  // 测试后序遍历
  node1.trav_post(visit<int>);
  cout << endl;

  // 测试层序遍历
  node1.trav_level(visit<int>);
  cout << endl;

  /* ----------- 测试 BinTree ------------ */
  BinTree<int> tree(14);
  BTNode<int>* R = tree.root();
  BTNode<int>*A = tree.insert_as_lc(21, R);
  BTNode<int>*B = tree.insert_as_rc(17, R);
  BTNode<int>*C = tree.insert_as_lc(2, A);
  BTNode<int>*D = tree.insert_as_rc(29, A);
  BTNode<int>*E = tree.insert_as_lc(43, B);
  BTNode<int>*F = tree.insert_as_rc(72, B);
  cout << tree.size() << endl;
  if (tree.empty()) cout << "The tree is empty!" << endl;
  return 0;
}