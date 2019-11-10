#include <cassert>
#include <iostream>
#include "bulk_builder.h"
#include "console_log_writer.h"
#include "file_writer.h"

// Run/executable              cat
// Run/Command Line Arguments ../homework7/input.txt | ./bulk

int main(int argc, char const* argv[]) {
  BulkBuilder builder(std::atoi(argv[1]));
  ConsoleLogWriter cwriter;
  FileWriter fwriter;
  builder.addObserver(&cwriter);
  builder.addObserver(&fwriter);

  while (true) {
    std::string command;
    std::getline(std::cin, command);
    builder.processCommand(command);
    if (command == "") break;
  }

  return 0;
}
