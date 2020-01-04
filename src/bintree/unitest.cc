#include <iostream>
#include "btnode.cc"

using dirac::BTNode;
using dirac::visit;
using std::cout;
using std ::endl;

int main() {
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
  return 0;
}