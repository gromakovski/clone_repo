#ifndef VTYPE_TRAITS_HPP
#define VTYPE_TRAITS_HPP

#include <list>
#include <map>
#include <string>
#include <vector>

/*! \file vtype_traits.hpp
    \brief  Метафункции определения типа переменной
    Статья про полную и частичную специализацию шаблонных классов
    https://habr.com/ru/post/54762/
*/

/*!
 Метафункция для определения являеться ли тип Т контейнером
 */
//базовая шаблонная мета функция
template <typename T>
struct is_cont {
  ///= true если T является контейнером
  static constexpr bool value = false;
};

//ЧАСТИЧНАЯ специализация
template <typename... Ts>
struct is_cont<std::vector<Ts...>> {
  static constexpr bool value = true;
};
//ЧАСТИЧНАЯ специализация
template <typename T, typename Alloc>
struct is_cont<std::list<T, Alloc>> {
  static constexpr bool value = true;
};
//можно сделать такую ПОЛНУЮ специализацию
//но в таком случае при инстанцировании метафункции например так
// is_cont<std::map<int, bool>>::value , компилятор не найдет нужную
//перегрузку и вызовет базовую функцию is_cont
//ПОЛНАЯ специализация
template <>
struct is_cont<std::map<int, int>> {
  static constexpr bool value = true;
};

/*!
 Метафункция для определения являеться ли тип Т строкой
 */
//базовая шаблонная мета функция
template <typename T>
struct is_string {
  ///= true если T является строкой
  static constexpr bool value = false;
};

//ПОЛНАЯ специализация
template <>
struct is_string<std::string> {
  static constexpr bool value = true;
};

#endif  // VTYPE_TRAITS_HPP
