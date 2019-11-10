#include <fstream>
#include <iostream>
#include <string>
#include <thread>

// add custom build step
// command - ctest
// arguments -VV

#include <gtest/gtest.h>

#include "async.h"

class WriterStub : public Observer {
  void update(std::string data, std::time_t /*time*/,
              int /*commandsCount*/) override {
    bulk_.append(data);
    bulk_.append("\n");
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
  std::shared_ptr<WriterStub> writerStubPtr = std::make_shared<WriterStub>();
  async::set_observer(writerStubPtr);
  std::size_t bulk = 5;
  auto h = async::connect(bulk);
  auto h2 = async::connect(bulk);
  async::receive(h, "1", 1);
  async::receive(h2, "1\n", 2);
  async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
  async::receive(h, "b\nc\nd\n}\n89\n", 11);
  async::disconnect(h);
  async::disconnect(h2);
  //блокируем данные поток до тех пор пока очередь не станет пустой
  async::wait_queue_is_empty();
  EXPECT_EQ(writerStubPtr->bulk_,
            "bulk: 1, 2, 3, 4, 5\n"
            "bulk: 6\n"
            "bulk: a, b, c, d\n");
}

TEST_F(TestBulk, Normal) {
  std::shared_ptr<WriterStub> writerStubPtr = std::make_shared<WriterStub>();
  async::set_observer(writerStubPtr);
  std::size_t bulk = 3;
  auto h = async::connect(bulk);
  bulk = 2;
  auto h2 = async::connect(bulk);
  async::receive(h, "1\n", 1);
  async::receive(h2, "2\n", 2);

  async::receive(h, "1\n", 1);
  async::receive(h2, "2\n", 2);

  async::receive(h, "1\n", 1);
  async::receive(h2, "2\n", 2);

  async::disconnect(h);
  async::disconnect(h2);
  //останвливаем поток и ждем его завершения
  async::wait_queue_is_empty();
  EXPECT_EQ(writerStubPtr->bulk_,
            "bulk: 2, 2\n"
            "bulk: 1, 1, 1\n");
}

TEST_F(TestBulk, 3Contexts) {
  std::shared_ptr<WriterStub> writerStubPtr = std::make_shared<WriterStub>();
  async::set_observer(writerStubPtr);
  std::size_t bulk = 3;
  auto h = async::connect(bulk);
  bulk = 3;
  auto h2 = async::connect(bulk);
  async::receive(h, "1\n", 1);
  async::receive(h2, "2\n", 2);

  async::receive(h, "1\n", 1);
  async::receive(h2, "2\n", 2);

  async::receive(h, "1\n", 1);
  async::receive(h2, "2\n", 2);

  async::disconnect(h);
  async::disconnect(h2);

  auto h3 = async::connect(bulk);
  async::receive(h3, "3\n", 1);
  async::receive(h3, "3\n", 2);
  async::receive(h3, "3\n", 1);

  async::disconnect(h3);
  //останвливаем поток и ждем его завершения
  async::wait_queue_is_empty();
  EXPECT_EQ(writerStubPtr->bulk_,
            "bulk: 1, 1, 1\n"
            "bulk: 2, 2, 2\n"
            "bulk: 3, 3, 3\n");
}

TEST_F(TestBulk, Wait) {
  async::wait_queue_is_empty();
  std::cout << "wait" << std::endl;
  async::wait_queue_is_empty();
  std::cout << "wait" << std::endl;
  async::wait_queue_is_empty();
  std::cout << "wait" << std::endl;
  async::wait_queue_is_empty();
  std::cout << "wait" << std::endl;
  EXPECT_TRUE(true);
}

}  // namespace
