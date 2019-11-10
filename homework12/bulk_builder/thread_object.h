#ifndef THREAD_OBJECT_H
#define THREAD_OBJECT_H

#include <atomic>
#include <condition_variable>
#include <iostream>
#include <thread>

//Данный класс позволяет выполнять код в отдельном потоке
//для выполнения кода нужно в производном классе переопределить функцию
// runInfinitely() поместив туда код который должен выполняться в потоке
class ThreadObject {
 public:
  ThreadObject() {}
  ~ThreadObject() { stop(); }
  //Запускает поток. Сразу после запуска поток засыпает.
  //Чтобы пробудить поток и начать выполнение runInfinitely
  //необходимо вызвать notify()
  void start() {
    running_ = true;
    thread_ = std::thread(&ThreadObject::loop, this);
  }
  void stop() {
    running_ = false;
    condition_.notify_one();
    thread_.join();
  }
  //пробуждает поток после чего 1 раз выполняется runInfinitely()
  void notify() { condition_.notify_one(); }

 protected:
  virtual void runInfinitely() {}

 private:
  std::thread thread_;
  std::atomic_bool running_;
  std::condition_variable condition_;
  std::mutex conditionMutex_;

  void loop() {
    while (true) {
      std::unique_lock<std::mutex> lck{conditionMutex_};
      condition_.wait(lck);
      if (!running_) break;
      // std::cout << "loop" << std::endl;
      runInfinitely();
    }
    // std::cout << "loopexit" << std::endl;
  }
};

#endif  // THREAD_OBJECT_H
