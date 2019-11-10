#include <fstream>
#include <iostream>
#include <string>

// add custom build step
// command - ctest
// arguments -VV

#include <gtest/gtest.h>

#include "bulk_builder.h"
#include "observer.h"

class WriterStub : public Observer {
  void update(std::string data, std::time_t /*time*/,
              int /*commandsCount*/) override {
    bulk_.append(data);
  }

 public:
  std::string bulk_;
};

namespace {
class TestBulk : public ::testing::Test {
 public:
  void SetUp() override {}
};

TEST_F(TestBulk, Simple) {
  WriterStub wstub;
  BulkBuilder builder{3};
  builder.addObserver(&wstub);

  builder.processCommand("cmd1");
  builder.processCommand("cmd2");
  builder.processCommand("cmd3");

  EXPECT_EQ(wstub.bulk_, "bulk: cmd1, cmd2, cmd3");
}

TEST_F(TestBulk, UnexceptedDataEnd) {
  WriterStub wstub;
  BulkBuilder builder{3};
  builder.addObserver(&wstub);

  builder.processCommand("cmd1");
  builder.processCommand("cmd2");
  builder.processCommand("");

  EXPECT_EQ(wstub.bulk_, "bulk: cmd1, cmd2");
}

TEST_F(TestBulk, DynamicBlockSize) {
  WriterStub wstub;
  BulkBuilder builder{3};
  builder.addObserver(&wstub);

  builder.processCommand("cmd1");
  builder.processCommand("cmd2");
  builder.processCommand("cmd3");

  builder.processCommand("{");
  builder.processCommand("cmd4");
  builder.processCommand("cmd5");
  builder.processCommand("cmd6");
  builder.processCommand("cmd7");
  builder.processCommand("}");

  EXPECT_EQ(wstub.bulk_, "bulk: cmd1, cmd2, cmd3bulk: cmd4, cmd5, cmd6, cmd7");
}

TEST_F(TestBulk, DynamicBlockSize2) {
  WriterStub wstub;
  BulkBuilder builder{3};
  builder.addObserver(&wstub);

  builder.processCommand("cmd1");
  builder.processCommand("cmd2");

  builder.processCommand("{");
  builder.processCommand("cmd4");
  builder.processCommand("cmd5");
  builder.processCommand("cmd6");
  builder.processCommand("cmd7");
  builder.processCommand("}");

  EXPECT_EQ(wstub.bulk_, "bulk: cmd1, cmd2bulk: cmd4, cmd5, cmd6, cmd7");
}

TEST_F(TestBulk, DynamicNestedBlocks) {
  WriterStub wstub;
  BulkBuilder builder{3};
  builder.addObserver(&wstub);

  builder.processCommand("{");
  builder.processCommand("cmd1");
  builder.processCommand("cmd2");
  builder.processCommand("{");
  builder.processCommand("cmd3");
  builder.processCommand("cmd4");
  builder.processCommand("}");
  builder.processCommand("cmd5");
  builder.processCommand("cmd6");
  builder.processCommand("}");

  EXPECT_EQ(wstub.bulk_, "bulk: cmd1, cmd2, cmd3, cmd4, cmd5, cmd6");
}

TEST_F(TestBulk, DynamicUnexceptBlocks) {
  WriterStub wstub;
  BulkBuilder builder{3};
  builder.addObserver(&wstub);

  builder.processCommand("cmd1");
  builder.processCommand("cmd2");
  builder.processCommand("cmd3");
  builder.processCommand("{");
  builder.processCommand("cmd4");
  builder.processCommand("cmd5");

  EXPECT_EQ(wstub.bulk_, "bulk: cmd1, cmd2, cmd3");
}

}  // namespace
