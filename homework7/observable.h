#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>
#include "observer.h"

class Observable {
 public:
  void addObserver(Observer *observer) { _observers.push_back(observer); }
  void notifyUpdate(std::string data, std::time_t time = 0) {
    int size = _observers.size();
    for (int i = 0; i < size; i++) {
      _observers[i]->update(data, time);
    }
  }

 private:
  std::vector<Observer *> _observers;
};

#endif  // OBSERVABLE_H
