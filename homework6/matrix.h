#ifndef MATRIX2_H
#define MATRIX2_H

//Основная некрасивость в том что  Element хранит ссылку на  ElementStorage
//так как вынужден сам заносить  и удалять себя в ElementStorage так
//как эти действия происходят через его operator=
//Может быть есть возможность убрать ElementStorage& из Element?

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>

#include "element.h"
#include "matrix_iterator.h"

//Предоставляет оператор [] в котором
//либо создается новое Element (если такого элемента нет) либо извлекается
//ссылка на существующий
template <typename T, T def>
struct Column {
  Column() {}
  Element<T>& operator[](std::size_t column) {
    //при обращении к элементу устанавливаем cRow_ и cColumn_
    // ElementStorage в значение места текущего элемента
    //чтобы ElementStorage& , когда его будет дергать  Element знал где этот
    //элемент лежит в нем
    elstorage_.setCurrentRow(row_);
    elstorage_.setCurrentColumn(column);
    //если есть значение то возвращаем его
    if (elstorage_.isSet()) {
      return *elstorage_.value();
      //если нет то создаем новое
    } else {
      //утечка памяти. (если потом элементу не
      //присвоили значение он не удалится) (т.к. удаляются только те элементы
      //которые оборачиваются в ElementPtr<T> и попадают в elstorage_).
      //А пока не произошел факт вызова оператора =, мы не знаем попадет ли
      //элемент в elstorage_ или нет. (Вернее в ДАННОМ месте мы не знаем вызовет
      //ли пользователь оператор = или  оставит просто такой вызов matrix[0][0])
      //Пока не могу придумать как решить эту
      //проблему в текущей архитектуре. Вся надежда на ревьюверов
      Element<T>* emptyv = new Element<T>(elstorage_, elfactory_, def);
      return *emptyv;
    }
  }
  void setRow(int row) { row_ = row; }
  int row_;
  ElementStorage<T> elstorage_;
  UniqueElementFactory<T> elfactory_;
};

template <typename T, T def>
class Matrix {
 public:
  using iterator = MatrixIterator<T>;
  using const_iterator = MatrixIterator<const T>;
  int size() { return emptycolumn.elstorage_.size_; }
  Column<T, def>& operator[](std::size_t row) {
    // std::cout << "Matrix::Column<T>& operator[]" << std::endl;
    emptycolumn.setRow(row);
    return emptycolumn;
  }

  Column<T, def> emptycolumn;

  iterator begin() { return iterator(emptycolumn.elstorage_.values_); }
  iterator end() { return iterator(emptycolumn.elstorage_.values_, true); }

 private:
};

#endif  // MATRIX2_H
