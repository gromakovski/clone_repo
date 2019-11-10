#include <fstream>
#include <iostream>
#include <string>

#include "print_ip.h"
#include "vtype_traits.hpp"

// add custom build step
// command - ctest
// arguments -VV

#include <gtest/gtest.h>
namespace {
class TestVtypeTraits : public ::testing::Test {
 public:
  void SetUp() override {}
};

TEST_F(TestVtypeTraits, testIscontainerVector) {
  bool res = is_cont<std::vector<int>>::value;
  EXPECT_TRUE(res);
}

TEST_F(TestVtypeTraits, testIscontainerList) {
  bool res = is_cont<std::list<int>>::value;
  EXPECT_TRUE(res);
}

TEST_F(TestVtypeTraits, testIscontainerCustomType) {
  struct Custom {};
  EXPECT_FALSE(is_cont<Custom>::value);
}

TEST_F(TestVtypeTraits, testIsStringString) {
  bool res = is_string<std::string>::value;
  EXPECT_TRUE(res);
}

TEST_F(TestVtypeTraits, testIsStringInt) {
  bool res = is_string<int>::value;
  EXPECT_FALSE(res);
}

class TestPrintIp : public ::testing::Test {
 public:
  void SetUp() override {}
};

//тест на то что ничего не падает.
//еслибы у функции printIp было бы возвращаемое значение не void
//то можно было бы сделать тесты с проверкой возвращаемых значений
//но я выбрал дизайн функции printIp при котором она возвращает void
//так как в задании указано что функция именно для печати
TEST_F(TestPrintIp, printIp) {
  printIp(char{-1});
  printIp(short{0});
  printIp(int{2130706433});
  printIp(long{8875824491850138409});
  printIp(std::string{"127.0.0.1"});
  printIp(std::vector<int>{127, 0, 0, 1});
  printIp(std::list<char>{'1', '0', '0', '1'});
  EXPECT_TRUE(true);
}

}  // namespace
