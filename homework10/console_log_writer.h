#ifndef CONSOLE_LOG_WRITER_H
#define CONSOLE_LOG_WRITER_H

#include <mutex>

#include "observer.h"
#include "thread_object.h"

class ConsoleLogWriter : public Observer, public ThreadObject {
 public:
  ConsoleLogWriter() { start(); }
  void update(std::string data, std::time_t time, int commandsCount) override {
    std::lock_guard<std::mutex> guard(mutexdata_);
    std::get<0>(counters)++;
    std::get<1>(counters) += commandsCount;
    data_ = data;
    notify();
  }
  void runInfinitely() override {
    std::lock_guard<std::mutex> guard(mutexdata_);
    std::cout << data_ << std::endl;
  }

 private:
  std::string data_;
  std::mutex mutexdata_;

 public:
  std::tuple<int, int> counters;
};

#endif  // CONSOLE_LOG_WRITER_H
