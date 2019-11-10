#ifndef BULK_BUILDER_H
#define BULK_BUILDER_H

#include <chrono>
#include <iostream>
#include "observable.h"

const std::string EMPTYCMD = "";
const std::string STARTDYNBLOCKCMD = "{";
const std::string ENDDYNBLOCKCMD = "}";

using namespace std::chrono;

class BulkBuilder : public Observable {
 public:
  BulkBuilder(short bulkSize) : bulkSize_(bulkSize) {}
  ~BulkBuilder() { /*std::cout << "~BulkBuilder\n"; */
  }
  void processCommand(const std::string &command);

 private:
  //обработка динамических блоков
  void processDynamicCommand(const std::string &command);
  //обработка фисированных блоков
  void processFixedCommand(const std::string &command);

  short bulkSize_;
  short commandsCount = 0;

  bool dynamicBlockFlag = false;
  //счетчик открывающихся и закрывающихся скобок.
  //инкрементируеться при команде открытой скобки и декрементируется при
  //команде закрытой скобки. Таким образом если счетчик 0 то либо еще не
  //попадалось команд со скобками
  //либо последняя завершающая скобка блока команд обрпботалась
  int startendCmdCounter = 0;
  const std::string bulkHeader{"bulk: "};
  std::string bulkBody;
  std::time_t firstCommandTime = 0;

 public:
  std::tuple<int, int, int, int> counters;
  int ll = 5;
};

#endif  // BULK_BUILDER_H
