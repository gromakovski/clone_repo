#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <iostream>
#include <map>
#include <vector>

//Идея Клаcc Matrix содержит Column<T>& operator[] который предоставляет
//    класс Column который содержит  Value& operator[]  который предоставляет
//     класс Value который предоставляет операторы присваивания, сравнения и
//     само содержимое
//  матрицы

template <typename T>
struct Value;

template <typename S>
bool operator==(Value<S> lhs, int rhs) {
  if (lhs.values.count(lhs.row_)) {
    if (lhs.values.at(lhs.row_).count(lhs.column_)) {
      //  this->val = values.at(row_).at(column_).val;
      return true;
    }
  }
  if (rhs == -1)
    return true;
  else
    return false;
}

template <typename T>
struct Value {
  Value& operator=(const T other) {  //место где ячейке присваиваеться значение

    if (other == -1) {
      values[row_].erase(column_);
      if (values[row_].size() == 0) values.erase(row_);
      size_--;
      return *this;
    }

    //создаем новое     matrix[100][100] = 314; -> Value& v = 314;
    //->  v = v.operator=(314);
    //Вобщем получается оператор возвращает тоже значение но меняет values
    //внутри него
    T& v = values[row_][column_];
    size_++;
    v = other;
    // *this = v;

    // return v;
    return *this;
  }
  void setRow(int row) { row_ = row; }
  void setColumn(int column) { column_ = column; }
  int row_;
  int column_;
  int size_ = 0;
  std::map<int /*rowindex*/, std::map<int /*columnindex*/, T>> values;

  friend bool operator==<T>(Value, int);
};

template <typename T>
struct Column {
  Column() {}
  Value<T>& operator[](std::size_t column) {
    emptyv.setRow(row_);
    emptyv.setColumn(column);
    return emptyv;
  }
  void setRow(int row) { row_ = row; }
  int row_;
  Value<T> emptyv;
};

template <typename T, int def>
class Matrix {
 public:
  int size() {
    std::cout << "Matrix::size" << std::endl;

    return emptycolumn.emptyv.size_;
  }
  Column<T>& operator[](std::size_t row) {
    std::cout << "Matrix::Column<T>& operator[]" << std::endl;
    emptycolumn.setRow(row);
    return emptycolumn;
  }

  Column<T> emptycolumn;

 private:
};

#endif  // MATRIX_H
