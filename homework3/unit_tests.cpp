#include <fstream>
#include <iostream>
#include <string>

#include "map_allocator.h"
#include "simple_list.h"

// add custom build step
// command - ctest
// arguments -VV

int factorial(int val) {
  auto result = 1;
  for (int i = 1; i <= val; i++) {
    result *= i;
  }
  return result;
}

#include <gtest/gtest.h>
namespace {
class Test1 : public ::testing::Test {
 public:
  void SetUp() override {}
};

TEST_F(Test1, testMap) {
  {
    std::map<int, int, std::less<int>, FactMapAlloctor> factMap;
    for (int i = 0; i <= 9; i++) factMap[i] = factorial(i);

    for (auto val : factMap)
      std::cout << val.first << " " << val.second << std::endl;
  }
  EXPECT_TRUE(true);
}

TEST_F(Test1, testCustomList) {
  {
    SimpleList<int, FactListAlloctor> v;
    for (int i = 0; i <= 9; i++) v.pushBack(i);
    v.printList();
  }
  EXPECT_TRUE(true);
}

TEST_F(Test1, testAllocate) {
  MemPoolAllocator<int> alloc;
  int *memPtr = alloc.allocate(1);
  ASSERT_NE(memPtr, nullptr);
}

}  // namespace
