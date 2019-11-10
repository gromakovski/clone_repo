#ifndef FILE_WRITER_H
#define FILE_WRITER_H
#include <fstream>
#include <map>
#include <mutex>

#include "ThreadPool.h"
#include "observer.h"

class FileWriter : public Observer {
 public:
  FileWriter() {
    for (const auto& th : pool.getWorkers()) {
      countersMap[th.get_id()];
    }
  }

 private:
  void update(std::string data, std::time_t time, int commandsCount) override {
    bulkCounter_++;
    std::string time_count =
        std::to_string(time) + "_" + std::to_string(bulkCounter_);
    //помещает в пулл потоков на выполнение
    //следующий пакет для записи в файл
    auto result = pool.enqueue(
        [this](std::string data, std::string time_count, int commandsCount) {
          // std::this_thread::sleep_for(5000ms);
          std::ofstream fout("bulk" + time_count + ".log");
          fout << data;
          std::get<0>(countersMap[std::this_thread::get_id()])++;
          std::get<1>(countersMap[std::this_thread::get_id()]) += commandsCount;
        },
        data, time_count, commandsCount);
  }

 private:
  int bulkCounter_{0};  //уникальный счетчик пакетов
  std::mutex mutexdata_;
  ThreadPool pool{2};

 public:
  std::map<std::thread::id /*thread id*/, std::tuple<int, int>> countersMap;
};

#endif  // FILE_WRITER_H
