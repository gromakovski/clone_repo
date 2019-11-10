#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <array>
#include <iostream>
#include "vtype_traits.hpp"

/*! \file print_ip.h
    \brief  Функции печати ip адреса. Функции перегруженыс помощью SFINAE
     Статья про SFINAE:
     http://scrutator.me/post/2016/12/12/sfinae.aspx
*/

/*!
Выводит на печать байты любого целочисленного T в виде чисел разделенных точками
@param adress - IP адрес
*/
template <typename T>
void printIntegralAdress(T adress) {
  std::array<unsigned char, sizeof(T)> bytes;
  std::copy(
      static_cast<const char *>(static_cast<const void *>(&adress)),
      static_cast<const char *>(static_cast<const void *>(&adress)) + sizeof(T),
      bytes.begin());
  //проходим array из конца в начало так как порядок байт LItttleEndian
  //(т.е. младший байты лежат в памяти первым итд)
  for (auto it = bytes.rbegin(); it != bytes.rend(); it++) {
    if (it != bytes.rbegin()) std::cout << ".";
    std::cout << (short)*it;
  }
}

/*!
//Шаблонная перегрузка вывода на печать ip адреса для целочисленных чисел
*/
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type printIp(
    T &&adress) {
  // std::cout << "print int" << sz << std::endl;
  printIntegralAdress(adress);
  std::cout << std::endl;
}

/*!
//Шаблонная перегрузка вывода на печать ip адреса для контейнеров
*/
template <typename T>
typename std::enable_if<is_cont<T>::value, void>::type printIp(T &&adress) {
  // std::cout << "print cont" << std::endl;
  for (auto it = adress.begin(); it != adress.end(); it++) {
    if (it != adress.begin()) std::cout << ".";
    std::cout << *it;
  }
  std::cout << std::endl;
}

/*!
//Шаблонная перегрузка вывода на печать ip адреса для std::string
*/
//Работает
void printIp(const std::string &t) {
  std::cout << "print string" << std::endl;
  std::cout << t << std::endl;
}

//Так тоже рабоает
// template <typename T>
// typename std::enable_if<is_string<T>::value, void>::type printIp(T t) {
//  std::cout << "print string" << std::endl;
//  std::cout << t << std::endl;
//}

#endif  // PRINT_IP_H
