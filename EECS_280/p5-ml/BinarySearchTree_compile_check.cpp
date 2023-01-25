// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include "BinarySearchTree.h"

using namespace std;

class Duck {
public:
  Duck() : wealth(0) {} // tree requires default-constructible
  Duck(int wealth_in) : wealth(wealth_in) {}
  int getWealth() const { return wealth; }

private:
  int wealth;

};

class DuckWealthLess {
public:
  bool operator() (const Duck &d1, const Duck &d2) const {
    return d1.getWealth() < d2.getWealth();
  }

};

ostream &operator<<(ostream &os, const Duck &duck) {
  return os << "Duck: $" << duck.getWealth();
}

int main() {
  cout << "This test doesn't do anything interesting." << endl;
  cout << "It is just here to check for compilation issues." << endl;
  cout << "1" << endl;

  BinarySearchTree<int> tree;
  const BinarySearchTree<int> &const_tree = tree;

  // TODO: Do ducks actually live in trees?
  BinarySearchTree<Duck, DuckWealthLess> duck_tree;
  const BinarySearchTree<Duck, DuckWealthLess> &const_duck_tree = duck_tree;

  // Insert elements into trees to prevent breaking requires clauses
  tree.insert(100);
  tree.insert(1000);
  tree.insert(10000);
  duck_tree.insert(Duck(100));
  duck_tree.insert(Duck(1000));
  duck_tree.insert(Duck(10000));
  cout << "2" << endl;
  // Dummy variables
  bool b;
  size_t i;
  size_t st;
  string s;

  // Dummy iterators - should be default constructible as end iterator
  BinarySearchTree<int>::Iterator it;
  BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_it;
  cout << "3" << endl;


  // Big Three
  BinarySearchTree<int> tree_copy(const_tree);
  BinarySearchTree<Duck, DuckWealthLess> duck_tree_copy(const_duck_tree);
  cout << "3.5" << endl;
  tree_copy = const_tree;
  cout << "3.6" << endl;
  duck_tree_copy = const_duck_tree;
  cout << "4" << endl;
  // destructor tested implicitly at end of function



  // Functions that can be applied to a const tree
  b = const_tree.empty();
  b = const_duck_tree.empty();

  i = const_tree.height();
  i = const_duck_tree.height();

  st = const_tree.size();
  st = const_duck_tree.size();
  cout << "5" << endl;
  const_tree.traverse_inorder(cout);
  const_duck_tree.traverse_inorder(cout);
  cout << "6" << endl;
  const_tree.traverse_preorder(cout);
  cout << "7" << endl;
  const_duck_tree.traverse_preorder(cout);
  cout << "8" << endl;
  b = const_tree.check_sorting_invariant();
  b = const_duck_tree.check_sorting_invariant();
  cout << "9" << endl;
  it = const_tree.begin();
  duck_it = const_duck_tree.begin();
  cout << "10" << endl;
  it = const_tree.end();
  duck_it = const_duck_tree.end();
  cout << "11" << endl;
  it = const_tree.min_element();
  duck_it = const_duck_tree.min_element();
  cout << "12" << endl;
  it = const_tree.max_element();
  duck_it = const_duck_tree.max_element();
  cout << "13" << endl;
  it = const_tree.find(0);
  duck_it = const_duck_tree.find(Duck());
  cout << "14" << endl; 
  s = const_tree.to_string();
  s = const_duck_tree.to_string();
  cout << "15" << endl;
  it = const_tree.min_greater_than(0);
  duck_it = const_duck_tree.min_greater_than(Duck());
  cout << "16" << endl;


  // Functions that can't be called on a const tree
  it = tree.insert(0);
  duck_it = duck_tree.insert(Duck());
  cout << "17" << endl;


  // Using iterators

  it = tree.begin();
  duck_it = duck_tree.begin();
  cout << "18" << endl;
  *it = 50;
  *duck_it = Duck(50);
  cout << "19" << endl;
  ++++it;
  ++++duck_it;
  cout << "20" << endl;
  it = it++;
  duck_it = duck_it++;
  cout << "21" << endl;
  b = tree.end() == tree.end();
  b = duck_tree.end() == duck_tree.end();

  b = tree.end() != tree.end();
  b = duck_tree.end() != duck_tree.end();

  const auto &const_it = it;
  const auto &const_duck_it = duck_it;

  BinarySearchTree<int>::Iterator it_copy(const_it);
  BinarySearchTree<Duck, DuckWealthLess>::Iterator duck_it_copy(const_duck_it);

  cout << b << i << st << s << endl;
  cout << *it_copy << (*duck_it_copy).getWealth() << endl;
 
}
