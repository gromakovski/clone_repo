#ifndef FILE_WRITER_H
#define FILE_WRITER_H
#include <fstream>

#include "observer.h"

class FileWriter : public Observer {
  void update(std::string data, std::time_t time) override {
    std::ofstream fout("bulk" + std::to_string(time) + ".log");
    fout << data;
  }
};

#endif  // FILE_WRITER_H
