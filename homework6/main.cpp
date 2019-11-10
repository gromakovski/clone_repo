#include <cassert>
#include <iostream>

#include "matrix.h"

int main(int argc, char const* argv[]) {
  //заполняем матрицу
  Matrix<int, 0> matrix2;
  for (int i = 0; i <= 9; i++) {
    matrix2[i][i] = i;
  }
  for (int j = 9, i = 0; j >= 0; j--, i++) {
    matrix2[i][j] = j;
  }

  //выводим фрагмент
  int from = 1;
  int to = 8;
  for (int i = from; i <= to; i++) {
    for (int j = from; j <= to; j++) {
      std::cout << matrix2[i][j].value() << " ";
    }
    std::cout << std::endl;
  }

  std::cout << "Size - " << matrix2.size() << std::endl
            << "UniqueElements (легковесов) - "
            << matrix2.emptycolumn.elfactory_.uniqueElementsSize() << std::endl;

  //выводим все элементы
  for (auto val : matrix2) {
    int x;
    int y;
    int v;
    std::tie(x, y, v) = val;
    std::cout << "" << x << " " << y << " " << v << std::endl;
  }
  return 0;
}
