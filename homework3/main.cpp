#include <cassert>
#include <cstdlib>
#include <iostream>

#include "map_allocator.h"
#include "simple_list.h"

int factorial(int val) {
  auto result = 1;
  for (int i = 1; i <= val; i++) {
    result *= i;
  }
  return result;
}

int main(int argc, char const *argv[]) {
  //заполнение 10 элементами, где ключ это число от 0 до 9, а значение  -
  //факториал ключа
  {
    std::map<int, int> factMap;
    for (int i = 0; i <= 9; i++) factMap[i] = factorial(i);

    for (auto val : factMap)
      std::cout << val.first << " " << val.second << std::endl;
  }
  //заполнение 10 элементами, где ключ это число от 0 до 9, а значение -
  //факториал ключа c новым аллокатором
  {
    std::map<int, int, std::less<int>, FactMapAlloctor> factMap;
    for (int i = 0; i <= 9; i++) factMap[i] = factorial(i);

    for (auto val : factMap)
      std::cout << val.first << " " << val.second << std::endl;
  }

  //создание экземпляра своего контейнера для хранения int
  //заполнение 10 элементами от 0 до 9
  {
    SimpleList<int> v;
    for (int i = 0; i <= 9; i++) v.pushBack(i);
    v.printList();
  }

  //создание экземпляра своего контейнера для хранения int с новым
  //аллокатором
  {
    SimpleList<int, FactListAlloctor> v;
    for (int i = 0; i <= 9; i++) v.pushBack(i);
    v.printList();
  }

  //тест аллокатора на использование аллоцированной ранее памяти
  //	std::cout << "--------------------------" << std::endl;
  //	{
  //		std::list<int, FactVectorAlloctor> list;
  //		for (int i = 0; i <=19; i++)
  //			list.push_back(i);

  //		for (int i = 0; i <=19; i++)
  //			list.pop_back();

  //		for (int i = 0; i <=19; i++)
  //			list.push_back(i);

  //		for (const auto& val: list)
  //			std::cout << val << " " << &val << std::endl;
  //	}

  return 0;
}
