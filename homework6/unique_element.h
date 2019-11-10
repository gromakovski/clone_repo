#ifndef UNIQUE_ELEMENT_H
#define UNIQUE_ELEMENT_H

#include <algorithm>
#include <list>
#include <memory>

//Легковес - внутреннее не изменяемое состояние value_
//Хранит в себе уникальное значение для использования
//в любом элементе
template <typename T>
struct UniqueElement {
  UniqueElement(T value) : value_(value) {}
  const T& value() const { return value_; }

 private:
  T value_;
};

template <typename T>
using UniqueElementPtr = std::shared_ptr<UniqueElement<T>>;

//при запросе значения создает уникальное значения для элемента,
// сохраняет его в себе, и возвращает. Если значение уже есть то просто
// возвращает его
template <typename T>
class UniqueElementFactory {
 public:
  UniqueElementFactory() {}
  //Возвращает указатель на уникальный элемент
  UniqueElementPtr<T> getElement(T val) {
    UniqueElementPtr<T> el;
    auto iter = std::find_if(
        uniqueElements.begin(), uniqueElements.end(),
        [&val](const UniqueElementPtr<T> el) { return el->value() == val; });
    if (iter == uniqueElements.end()) {
      UniqueElement<T>* ss = new UniqueElement<T>(val);
      el.reset(ss);
      uniqueElements.emplace_back(el);
    } else {
      el = *iter;
    }
    return el;
  }
  int uniqueElementsSize() { return uniqueElements.size(); }

 private:
  std::list<UniqueElementPtr<T>> uniqueElements;
};

#endif  // UNIQUE_ELEMENT_H
