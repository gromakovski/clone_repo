#pragma once

#include <set>
#include <thread>

class BulkBuilder;

#include "bulk_builder/bulk_builder.h"
#include "bulk_builder/console_log_writer.h"
#include "bulk_builder/file_writer.h"

enum class Event { Command, Stop, Disconnect };

//при создании запускает поток в котором запущена очередь событий типа Event
//очередь событий общая. В зависимости от типа события данные для обработки
//кладутся либо в commands_ либо в disconnects_
// bulk_builders_ - это список контекстов. Смысл списка контекстов в том
//что каждый контекст живет своей жизнью (т.е. добавление комманд в 1 контекст
//не влияет на логику работы других контекстов)
class CommandQueue {
 public:
  CommandQueue() {
    workerThread_ = std::thread(&CommandQueue::workerThread, this);
    //устанавливаем обсервером по умолчанию ConsoleLogWriter
    setObserver(std::make_shared<ConsoleLogWriter>());
  }
  ~CommandQueue() {
    // Stop-and-join idiom
    stop();

    // std::cout << "~CommandQueue\n";
  }
  void setObserver(ObserverSPtr observer) { observer_ = observer; }
  //  void start() {
  //    workerThread_ = std::thread(&CommandQueue::workerThread, this);
  //  }
  void stop() {
    {
      std::unique_lock<std::mutex> guard{mutex_};
      events_.push(Event::Stop);
    }
    if (workerThread_.joinable()) workerThread_.join();
  }
  BulkBuilder* connect(std::size_t bulk) {
    auto res = bulk_builders_.emplace(new BulkBuilder(bulk));
    (*res.first)->addObserver(&fwriter_);
    (*res.first)->addObserver(observer_.get());

    return *res.first;
  }
  void disconnect(BulkBuilder* b) {
    std::unique_lock<std::mutex> guard{mutex_};
    events_.push(Event::Disconnect);
    disconnects_.push(b);
  }
  void pushCommand(BulkBuilder* context, std::string command) {
    std::unique_lock<std::mutex> guard{mutex_};
    events_.push(Event::Command);
    commands_.push(std::make_pair(context, command));
  }

 private:
  void workerThread() {
    Event event;
    do {
      // std::cout << "workerThread" << std::endl;
      {
        std::unique_lock<std::mutex> guard{mutex_};
        if (events_.empty()) {
          isEmptyCondition_.notify_one();  //уведомляет о том что оченредь пуста
          guard.unlock();
          std::this_thread::sleep_for(std::chrono::milliseconds(1000));

          continue;
        }
      }

      event = events_.front();
      events_.pop();

      switch (event) {
        case Event::Command: {
          BulkBuilder* builder_ptr = commands_.front().first;
          std::string command = commands_.front().second;
          commands_.pop();

          auto builder = bulk_builders_.find(builder_ptr);
          if (builder != bulk_builders_.end()) {
            // std::cout << "processCommand" << command << std::endl;
            (*builder)->processCommand(command);

            //если закомментировать то вывод на консоль не происходит
            std::this_thread::sleep_for(std::chrono::milliseconds(1));

          } else {
            // std::cout << "Обработчик с handle - " << builder_ptr
            //            << "не найден\n";
          }

        } break;
        case Event::Stop: {
          // std::cout << "workerThread::stop";
        } break;
        case Event::Disconnect: {
          BulkBuilder* bb = disconnects_.front();
          bulk_builders_.erase(bb);
          disconnects_.pop();
          delete bb;
        } break;
      }
    } while (event != Event::Stop);

    // std::cout << "workerThread finished\n";
  }

  std::thread workerThread_;

  std::queue<std::pair<BulkBuilder* /*context*/, std::string /*command*/>>
      commands_;
  std::queue<BulkBuilder* /*context*/> disconnects_;
  // events queue
  std::queue<Event> events_;
  std::mutex mutex_;

  std::set<BulkBuilder*> bulk_builders_;
  ObserverSPtr observer_;
  FileWriter fwriter_;

 public:
  //условие освобождается всегда когда очередь становиться пустой
  std::condition_variable isEmptyCondition_;
  std::mutex conditionMutex_;
};
