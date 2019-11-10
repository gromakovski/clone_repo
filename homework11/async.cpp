#include "async.h"
#include <iostream>
#include <sstream>

#include "command_queue.h"

namespace async {

CommandQueue cmd_queue;

void set_observer(ObserverSPtr observer) { cmd_queue.setObserver(observer); }

handle_t connect(std::size_t bulk) {
  // std::cout << "connect\n";
  return cmd_queue.connect(bulk);
}

void receive(handle_t handle, const char *data, std::size_t size) {
  // std::cout << "receive\n";
  BulkBuilder *builder_ptr = reinterpret_cast<BulkBuilder *>(handle);

  std::istringstream f(data);
  std::string cmd;
  while (std::getline(f, cmd, '\n')) {
    // std::cout << cmd << std::endl;
    if (!cmd.empty()) cmd_queue.pushCommand(builder_ptr, cmd);
  }
}

void disconnect(handle_t handle) {
  BulkBuilder *builder_ptr = reinterpret_cast<BulkBuilder *>(handle);
  cmd_queue.disconnect(builder_ptr);
  // std::cout << "disconnect\n";
}

void wait_queue_is_empty() {
  std::unique_lock<std::mutex> lck{cmd_queue.conditionMutex_};
  cmd_queue.isEmptyCondition_.wait(lck);
}

}  // namespace async
