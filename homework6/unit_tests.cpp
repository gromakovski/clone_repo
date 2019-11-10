#include <fstream>
#include <iostream>
#include <string>

// add custom build step
// command - ctest
// arguments -VV

#include <gtest/gtest.h>
#include "element.h"
#include "matrix.h"
#include "matrix_iterator.h"
#include "unique_element.h"

namespace {
class TestUniqueElementFactory : public ::testing::Test {
 public:
  void SetUp() override {}
  UniqueElementFactory<char> fact;
};

TEST_F(TestUniqueElementFactory, testUniqueElementsSize) {
  fact.getElement('1');
  fact.getElement('2');
  fact.getElement('2');
  EXPECT_EQ(fact.uniqueElementsSize(), 2);
}

class TestElement : public ::testing::Test {
 public:
  void SetUp() override {
    elfactory_.getElement('1');
    elfactory_.getElement('2');
    elfactory_.getElement('2');
  }
  UniqueElementFactory<char> elfactory_;
  ElementStorage<char> elstorage_;
};

TEST_F(TestElement, testCreateElement1) {
  Element<char> emptyv(elstorage_, elfactory_, '1');
  EXPECT_EQ(emptyv.value(), '1');
}
TEST_F(TestElement, testCreateElement2) {
  //создаем на куче и не паримся о удалении т.к. владение элементом при
  //присвоении ему значения берет на себя elstorage_
  Element<char> *el = new Element<char>{elstorage_, elfactory_, '1'};
  *el = '5';
  EXPECT_EQ(el->value(), '5');
}

class TestMatrix : public ::testing::Test {
 public:
  void SetUp() override {}
  Matrix<int, -1> matrix;
};

TEST_F(TestMatrix, test1) { EXPECT_TRUE(matrix.size() == 0); }
TEST_F(TestMatrix, test2) {
  matrix[100][100] = 314;
  EXPECT_TRUE(matrix[100][100] == 314);
}
TEST_F(TestMatrix, test3) {
  matrix[100][100] = 314;
  EXPECT_TRUE(matrix.size() == 1);
}

TEST_F(TestMatrix, test4) {
  matrix[100][100] = 314;
  matrix[100][100] = -1;
  EXPECT_TRUE(matrix.size() == 0);
}

//добавляем 1 элемент потом еще 4 элемента
//из которых 1 перезаписывает предыдущий (всего получаеться 4 элемента в матрице
//уникальных значений в фабрике значений получается 3 (значение по умолчанию
//которое добавляеться всегда при индексации и 2 разных значения которые
//присваивались элементам в процессе теста)
TEST_F(TestMatrix, testCombination) {
  matrix[100][100] = 2;

  matrix[100][100] = 3;
  matrix[100][101] = 3;
  matrix[100][102] = 3;
  matrix[100][103] = 3;

  EXPECT_TRUE(matrix.size() == 4 &&
              matrix.emptycolumn.elfactory_.uniqueElementsSize() == 3);
}

TEST_F(TestMatrix, testIterator) {
  matrix[100][100] = 1;
  matrix[100][101] = 2;
  matrix[100][102] = 3;
  matrix[100][103] = 4;

  matrix[101][100] = 11;
  matrix[101][101] = 12;
  matrix[101][102] = 13;

  Matrix<int, -1>::iterator it = matrix.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  bool res1 = std::get<2>(*it) == 11;
  --it;
  --it;
  bool res2 = std::get<2>(*it) == 3;
  EXPECT_TRUE(res1 && res2);
}

}  // namespace
