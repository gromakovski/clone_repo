#include <cassert>
#include <iostream>
#include "bulk_builder.h"
#include "console_log_writer.h"
#include "file_writer.h"

// Run/executable              cat
// Run/Command Line Arguments ../homework10/input.txt | ./bulk

int main(int argc, char const* argv[]) {
  BulkBuilder builder(std::atoi(argv[1]));
  ConsoleLogWriter cwriter;
  FileWriter fwriter;
  builder.addObserver(&cwriter);
  builder.addObserver(&fwriter);

  while (true) {
    std::string command;
    std::getline(std::cin, command);
    if (command == "") break;
    builder.processCommand(command);
  }
  std::cout << "main поток - " << std::get<0>(builder.counters) << " строк, "
            << std::get<1>(builder.counters) << " команд, "
            << std::get<2>(builder.counters) << " блок\n";
  std::cout << "log поток - " << std::get<0>(cwriter.counters) << " блок, "
            << std::get<1>(cwriter.counters) << " команд\n";
  for (const auto& counters : fwriter.countersMap) {
    std::cout << "file " << counters.first << " поток - "
              << std::get<0>(counters.second) << " блок, "
              << std::get<1>(counters.second) << " команд\n";
  }

  return 0;
}
