#ifndef CONSOLE_LOG_WRITER_H
#define CONSOLE_LOG_WRITER_H

#include "observer.h"

class ConsoleLogWriter : public Observer {
  void update(std::string data, std::time_t /*time*/) override {
    std::cout << data << std::endl;
  }
};

#endif  // CONSOLE_LOG_WRITER_H
