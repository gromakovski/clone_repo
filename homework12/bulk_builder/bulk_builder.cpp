#include "bulk_builder.h"

void BulkBuilder::processCommand(const std::string &command) {
  std::get<0>(counters)++;
  //запоминаем время первой команды блока
  if (bulkBody.empty())
    firstCommandTime = system_clock::to_time_t(system_clock::now());

  if (command == STARTDYNBLOCKCMD) {
    startendCmdCounter++;
    dynamicBlockFlag = true;
    //если не завершено формирование обычного блока то завершаем его
    if (commandsCount != 0) processFixedCommand(EMPTYCMD);
  }

  if (dynamicBlockFlag) {
    processDynamicCommand(command);
  } else {
    processFixedCommand(command);
  }
}

//обработка динамических блоков
void BulkBuilder::processDynamicCommand(const std::string &command) {
  if (command == ENDDYNBLOCKCMD) {
    startendCmdCounter--;
  }
  if (startendCmdCounter == 0) {
    dynamicBlockFlag = false;
    bulkBody.pop_back();
    bulkBody.pop_back();
    // std::cout << "notifyUpdate" << bulkBody;
    notifyUpdate(bulkHeader + bulkBody, firstCommandTime,
                 std::get<3>(counters));
    std::get<3>(counters) = 0;
    std::get<2>(counters)++;
    bulkBody.clear();
    return;
  }
  if (command != ENDDYNBLOCKCMD && command != STARTDYNBLOCKCMD) {
    bulkBody.append(command);
    std::get<3>(counters)++;
    std::get<1>(counters)++;
    bulkBody.append(", ");
  }
}

//обработка фисированных блоков
void BulkBuilder::processFixedCommand(const std::string &command) {
  if (command != EMPTYCMD) {
    bulkBody.append(command);
    std::get<3>(counters)++;
    std::get<1>(counters)++;
    commandsCount++;
    if (commandsCount != bulkSize_) {
      bulkBody.append(", ");
    }
  }

  if (command == EMPTYCMD) {
    if (bulkBody.back() == ' ') {
      bulkBody.pop_back();
      bulkBody.pop_back();
    }
  }

  if (commandsCount == bulkSize_ || command == EMPTYCMD) {
    notifyUpdate(bulkHeader + bulkBody, firstCommandTime,
                 std::get<3>(counters));
    std::get<3>(counters) = 0;
    std::get<2>(counters)++;
    commandsCount = 0;
    bulkBody.clear();
  }
}
