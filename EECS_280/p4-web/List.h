#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  //Default Ctor
  List(): first(nullptr), last(nullptr), num_nodes(0){};

  //Copy Ctor
  List(const List &other): first(nullptr), last(nullptr), num_nodes(0) {
    copy_all(other);
  }

  //Dtor
  ~List() {
    clear();
  }

  //Assignment Operator
  List & operator=(const List &rhs){
    if(this == &rhs){
      return *this;
    }
    this->clear();
    //clear old list, make new list, copy elements over
    this->copy_all(rhs);
    return *this;
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return (0 == this->num_nodes);
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //         with a private member variable.  That's how std::list does it.
  int size() const {
    return this->num_nodes;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node *n = new Node;
    n->datum = datum;
    if(empty()) {
      first = n;
      last = n;
      n->next = nullptr;
      n->prev = nullptr;
    }
    else {
    first->prev = n;
    n->next = first;
    n->prev = nullptr;
    first = n;
    }
    num_nodes++;
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node *n = new Node;
    n->datum = datum;
    if(empty()) {
      first = n;
      last = n;
      n->next = nullptr;
      n->prev = nullptr;
    }
    else{
    last->next = n;
    n->prev = last;
    n->next = nullptr;
    last = n;
    }
    num_nodes++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node *victim = first;
    if(size() == 1) {
      delete victim;
      num_nodes--;
      first = nullptr;
      last = nullptr;
    }
    else{
    first->next->prev = nullptr;
    first = first->next;
    delete victim;
    num_nodes--;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node *victim = last;
    if(size() == 1) {
      delete victim;
      this->num_nodes--;
      first = nullptr;
      last = nullptr;
    }
    else {
    last->prev->next = nullptr;
    last = last->prev;
    delete victim;
    this->num_nodes--;
    }
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear() {
    while(!empty()){
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    for (Node *nds = other.first; nds != nullptr; nds = nds->next){
      this->push_back(nds->datum);
    }
  }


  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty

  int num_nodes;

public:
  ////////////////////////////////////////
  class Iterator {
    friend class List;
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:

    //default ctor
    Iterator(): node_ptr(nullptr) {}

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

    Iterator& operator++() {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    T & operator*() {
      assert(node_ptr);
      return node_ptr->datum;
    }

    bool operator==(const Iterator &rhs) const{
      return node_ptr == rhs.node_ptr;
    }

    bool operator!=(const Iterator &rhs) const{
      return node_ptr != rhs.node_ptr;
    }

    
  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here

    // construct an Iterator at a specific position
    Iterator(Node *p): node_ptr(p) {} 

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i) {
    
    if(size() == 1) {
      first = nullptr;
      last = nullptr;
      delete i.node_ptr;
      num_nodes--;
    }
    else if(i.node_ptr == first && size() != 1) {
      pop_front();
    }
    else if(i.node_ptr == last && size() != 1) {
      pop_back();
    }
    else if( size() != 1){
      i.node_ptr->prev->next = i.node_ptr->next;
      i.node_ptr->next->prev = i.node_ptr->prev;
      delete i.node_ptr;
      num_nodes--;
    }
    
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum) {
    
   
    if(i.node_ptr == nullptr) {
      push_back(datum);
    }
    else if(i.node_ptr == first) {
      push_front(datum);
    }
    else {
      Node *n = new Node;
      n->datum = datum;
      n->next = i.node_ptr;
      n->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = n;
      i.node_ptr->prev = n;
      num_nodes++;
    }
    
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
