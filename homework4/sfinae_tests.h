#ifndef SFINAE_TESTS_H
#define SFINAE_TESTS_H

#include <iostream>
#include <list>
#include <type_traits>
#include <vector>

template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value, void>::type>
void print_ip(T ip) {
  int bytes[sizeof(T)];

  for (size_t i = sizeof(T); i > 0;) {
    bytes[--i] = static_cast<uint8_t>(ip & 0xff);
    ip >>= 8;
  }

  std::cout << "integral:  ";
  std::cout << bytes[0];
  for (size_t i = 1; i < sizeof(T); ++i) {
    std::cout << "." << bytes[i];
  }
  std::cout << std::endl;
}

// template <typename T, typename = decltype(cbegin(std::declval<T>()),
//                                          cend(std::declval<T>()), void())>
// void print_ip(const T& ip) {
//  std::cout << "container: ";
//  auto cit = ip.cbegin();
//  std::cout << *cit;
//  for (++cit; cit != ip.cend(); ++cit) {
//    std::cout << "." << *cit;
//  }
//  std::cout << std::endl;
//}

template <typename T, typename = bool>
void print_ip(const T& ip) {}

template <>
void print_ip<std::string>(const std::string& ip) {
  std::cout << "string:    " << ip << std::endl;
}

#endif  // SFINAE_TESTS_H
