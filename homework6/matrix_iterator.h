#ifndef MATRIX_ITERATOR_H
#define MATRIX_ITERATOR_H

#include <iostream>
#include <iterator>
#include <map>
#include "element.h"

//Итератор для обхода Matrix
//обходит внутренний мап из мапов
template <typename ValueType>
class MatrixIterator
    : public std::iterator<std::input_iterator_tag, ValueType> {
 public:
  MatrixIterator(StorageMap<ValueType>& storage) : storage_(storage) {
    rowIt_ = storage_.begin();
    colIt_ = rowIt_->second.begin();
  }
  // bool end - костыль для того чтобы иметь возможность сконструировать
  // итератор с разной инициализацией rowIt_
  MatrixIterator(StorageMap<ValueType>& storage, bool end) : storage_(storage) {
    rowIt_ = storage_.end();
    colIt_ = rowIt_->second.end();
  }

 public:
  MatrixIterator(const MatrixIterator& it);

  bool operator!=(MatrixIterator const& other) const;
  // typename MatrixIterator::reference operator*() const;
  std::tuple<int, int, ValueType> operator*() const;
  MatrixIterator& operator++();
  MatrixIterator& operator--();

 private:
  typename StorageMap<ValueType>::iterator rowIt_;
  typename std::map<int, ElementPtr<ValueType>>::iterator colIt_;

  int row = 0;
  int column = 0;
  StorageMap<ValueType>& storage_;
};

template <typename ValueType>
MatrixIterator<ValueType>::MatrixIterator(const MatrixIterator& it)
    : storage_(it.storage_) {}

template <typename ValueType>
bool MatrixIterator<ValueType>::operator!=(MatrixIterator const& other) const {
  bool res = rowIt_ != other.rowIt_;
  return res;
}

template <typename ValueType>
std::tuple<int, int, ValueType> MatrixIterator<ValueType>::operator*() const {
  return std::make_tuple(rowIt_->first, colIt_->first,
                         (colIt_->second)->value());
}

template <typename ValueType>
MatrixIterator<ValueType>& MatrixIterator<ValueType>::operator++() {
  colIt_++;
  if (colIt_ == rowIt_->second.end()) {
    rowIt_++;
    colIt_ = rowIt_->second.begin();
  }

  return *this;
}

template <typename ValueType>
MatrixIterator<ValueType>& MatrixIterator<ValueType>::operator--() {
  if (colIt_ == rowIt_->second.begin()) {
    rowIt_--;
    colIt_ = rowIt_->second.end();
  }
  colIt_--;

  return *this;
}

#endif  // MATRIX_ITERATOR_H
