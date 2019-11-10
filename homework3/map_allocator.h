#include <deque>
#include <iostream>
#include <vector>

/*класс аллокатора работает с контейнерами которые располагают
данные в памяти  по принципу связного списка
****************Принцип работы***********************
У аллокатора есть вектор указателей на куски выделенной памяти - memBlocks
Память при потребности в ней с аллоцируется куском равным sizeof(T) * poolSize_
и заноситься в memPool. memPool это пул указателей T на куски памяти sizeof(T)
***********Последовательность работы************************
При первом вызове allocate(..) memPool пустой, и для того чтобы его пополнить
,вызывается функция reserve() которая аллоцирует большой кусок памяти равный
sizeof(T) * poolSize_ Этот кусок заноситься в memBlocks (для того чтобы потом в
деструкторе можно было освободить память каждого куска) Так же кусок памяти
разбиваеться на 10 равных частей указателями на T (для того чтобы их
использовать непосредственно в функции allocate())

*/
template <typename T>
class MemPoolAllocator {
 public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  MemPoolAllocator() {}
  ~MemPoolAllocator() {
    std::cout << "~MemPoolAllocator" << std::endl;

    for (int i = 0; i < memBlocks.size(); i++) {
      void* block = memBlocks[i];
      std::free(block);
    }
  }

  template <typename U>
  struct rebind {
    using other = MemPoolAllocator<U>;
  };

  T* allocate(std::size_t n) {
    if (memPool.size() == 0) reserve();

    T* val = memPool.front();  //берем адрес начала блока выделеной памяти
    std::cout << "allocate: [n = " << n << " " << val << "]" << std::endl;
    //извлекаем из пула количество указателей T , равное количеству элеметов n
    //для мапы и листа n всегда 1, и цикл будет срабатывать 1 раз
    //а вот для вектора при аллокации будет передаваться указатель на начало
    //блока памяти - T* val а из пула убираться память которую займут n
    //элементов вектора
    for (int i = 0; i < n; i++) {
      if (memPool.size() == 0) reserve();
      memPool.pop_front();
    }
    return val;
  }

  void deallocate(T* p, std::size_t n) {
    std::cout << "deallocate: [n  = " << n << " " << p << "] " << std::endl;

    //заносим освободившуюся память обратно в пул
    T* elem = p;
    for (int i = 0; i < n; i++) {
      memPool.push_back(elem);
      elem++;
    }
  }

  void destroy(T* p) { p->~T(); }

 private:
  std::deque<T*> memPool;  //пул указателей на куски памяти размера  sizeof(T)
  std::vector<void*>
      memBlocks;  //куски аллоцированной памяти размером sizeof(T) * poolSize_

  //захватываем куски памяти размером по 10 штук T
  void reserve() {
    int poolSize_ = 10;
    std::cout << "reserve" << std::endl;
    auto p = std::malloc(sizeof(T) * poolSize_);
    if (!p) throw std::bad_alloc();
    memBlocks.push_back(p);
    T* elem = reinterpret_cast<T*>(p);
    for (int i = 0; i < poolSize_; i++) {
      memPool.push_back(elem++);
    }
  }
};

using FactMapAlloctor = MemPoolAllocator<std::pair<const int, int> >;
using FactListAlloctor = MemPoolAllocator<int>;
