#include <iostream>
#include "bst.cc"

using dirac::BST;

int main(int argc, char const *argv[]) {
  BST<int> bst;
  bst.insert(11);
  bst.search(11);
  bst.remove(11);
  return 0;
}
