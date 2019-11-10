#ifndef OBSERVER_H
#define OBSERVER_H

#include <chrono>
#include <memory>
#include <string>
#include <vector>

class Observer {
 public:
  virtual void update(std::string data, std::time_t time,
                      int commandsCount) = 0;
};

using ObserverSPtr = std::shared_ptr<Observer>;

#endif  // OBSERVER_H
