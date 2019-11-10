#include <iostream>
#include <map>
#include <vector>
// int s
template <typename T>
class Node;

template <typename T, typename _Alloc = std::allocator<T>>
class SimpleList {
 public:
  ~SimpleList() {
    //деаллоцируем память в которой лежали данные и удалчяем узлы.
    Node<T>* node = first;
    while (node != nullptr) {
      allocator.deallocate(node->data_, 1);
      node = node->next_;
      if (node != nullptr) delete node->previous_;
    }
  }
  void pushBack(T& value) {
    size_++;
    T* val = allocator.allocate(1);
    *val = value;  //копируем в память по аллоцированному адресу новый элемент

    //создаем узел иинициализируем его
    //указатель на выделенную память проинициализированную значением
    Node<T>* temp = new Node<T>{head, val};
    if (head) head->next_ = temp;
    head = temp;

    if (first == nullptr) first = head;
  }
  void printList() {
    Node<T>* node = first;
    while (node != nullptr) {
      std::cout << *node->data_ << std::endl;
      node = node->next_;
    }
  }
  int size() { return size_; }

 private:
  int size_ = 0;
  Node<T>* first = nullptr;
  Node<T>* head = nullptr;
  _Alloc allocator;
};

template <typename T>
struct Node {
  Node(Node* previous, T* data) : previous_(previous), data_(data) {}
  ~Node() {
    // std::cout << "~Node" << std::endl;
  }
  Node<T>* previous_ = nullptr;
  Node<T>* next_ = nullptr;
  T* data_;
};
