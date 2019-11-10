#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
#include <vector>

class Observer {
 public:
  virtual void update(std::string data, std::time_t time,
                      int commandsCount) = 0;
};

#endif  // OBSERVER_H
