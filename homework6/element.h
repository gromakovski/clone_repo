#ifndef ELEMENT_H
#define ELEMENT_H

#include <unordered_map>
#include "unique_element.h"

//Это Контекст - хранит внешнее изменяемое состояние
//в виде ссылки на ElementStorage<T>&
//Класс споректирован для внутреннего использования в классе Matrix
//Конструктор принимает ElementStorage<T>& storage в который заносится
//указател ьна данный элемент при присвоении ему значения operator=
//после этого владение этим Element берет на себя ElementStorage<T>&. (Он же его
//и удаляет)
//Исходя из этой особенности можно получить  "двойное удаление"
//при попытке удалить созданный Element вручную (т.к. его удалит (или попытается
//удалить) ElementStorage<T>&)

template <typename T>
struct Element;

template <typename T>
using ElementPtr = std::shared_ptr<Element<T>>;

template <typename T>
struct ElementStorage;

template <typename S>
bool operator==(Element<S> lhs, int rhs) {
  return lhs.value_->value() == rhs;
}

template <typename T>
struct Element {
  Element(ElementStorage<T>& storage, UniqueElementFactory<T>& elfactory, T def)
      : storage_(storage), elfactory_(elfactory), def_(def) {
    //создаем элемент со значением по умолчанию
    value_ = elfactory_.getElement(def_);
  }

  Element& operator=(const T other) {  //присваиваем значение
    //если значение по умолчанию
    if (other == def_) {
      if (storage_.isSet()) {
        storage_.remove();
      }
      return *this;
    }

    //заносим самого себя свежесозданного в хранилище элементов
    value_ = elfactory_.getElement(other);
    if (isNew_) {
      isNew_ = false;

      ElementPtr<T> ptr(this);
      storage_.insert(ptr);
    }

    //создаем новое     matrix[100][100] = 314; -> Element& v = 314;
    //->  v = v.operator=(314);
    //Вобщем получается оператор возвращает тоже значение но меняет values
    //внутри него
    return *this;
  }
  //возвращает указатель на легковеса хранящего значение данного элэмента
  UniqueElementPtr<T> uniqueElement() { return value_; }
  //возвращает значение элемента
  const T value() { return value_->value(); }

 private:
  UniqueElementPtr<T> value_;  //указатель на легковеса с значением
  bool isNew_ = true;
  ElementStorage<T>& storage_;  //ссылка на мапу с элементами
  UniqueElementFactory<T>& elfactory_;  //фабрика легковесов
  T def_;

  friend bool operator==<T>(Element, int);
};

//Хранит список мап на элементы матрицы
//и предоставляет функции для удаления и добавления элементов
template <typename T>
using StorageMap =
    std::map<int /*rowindex*/, std::map<int /*columnindex*/, ElementPtr<T>>>;

template <typename T>
struct ElementStorage {
  void insert(ElementPtr<T> val) {
    values_[cRow_][cColumn_] = val;
    size_++;
  }
  void remove() {
    values_[cRow_].erase(cColumn_);
    if (values_[cRow_].size() == 0) values_.erase(cRow_);
    size_--;
  }
  bool isSet() {
    if (values_.count(cRow_))
      if (values_.at(cRow_).count(cColumn_)) return true;
    return false;
  }
  ElementPtr<T> value() { return values_[cRow_][cColumn_]; }

  //
  StorageMap<T> values_;
  int size_ = 0;

  void setCurrentRow(int row) { cRow_ = row; }
  void setCurrentColumn(int column) { cColumn_ = column; }
  int cRow_;
  int cColumn_;
};

#endif  // ELEMENT_H
