#include <exception>
#include <iostream>
#include "list.cc"
#include "list_node.cc"

using dirac::List;
using dirac::ListNode;

int main() {
  /* --------- 测试 list_node ----------*/
  ListNode<int> *p_node0 = new ListNode<int>;
  ListNode<int> *p_node1 = new ListNode<int>(1);
  ListNode<int> *p_node2 = new ListNode<int>(2);
  ListNode<int> *p_node3 = new ListNode<int>(3);
  p_node1->insert_aspred(p_node2);
  p_node2->insert_assucc(p_node3);
  p_node3->insert_aspred(10);
  p_node3->insert_assucc(8);

  /* ------------ 测试 list ------------*/
  // 测试空构造函数
  List<int> il1;

  // 测试拷贝构造函数
  List<int> il2(il1);

  // 测试 first
  bool is_null = il1.first();

  // 测试 insert_as_last
  il2.insert_as_last(2);
  il2.insert_as_last(4);
  il2.insert_as_last(7);
  il2.insert_as_last(1);
  il2.insert_as_last(10);
  il2.insert_as_last(19);
  il2.insert_as_last(12);

  std::cout << il2.first()->data << std::endl;
  std::cout << il2.size() << std::endl;
  ListNode<int> *p_node4 = il2.search(2);
  il2.remove(p_node4);
  std::cout << il2.size() << std::endl;
  for (auto iter = il2.first(); il2.valid(iter); iter = iter->succ) {
    std::cout << iter->data << " ";
  }
  il2.sort();
  std::cout << std::endl;
  il2.traverse(dirac::visit);
  std::cout << std::endl;
  il2.traverse(dirac::visit<int>);

  return 0;
}