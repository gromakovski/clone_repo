#include <iostream>

#include "print_ip.h"

int main(int argc, char const *argv[]) {
  printIp(char{-1});
  printIp(short{0});
  printIp(int{2130706433});
  printIp(long{8875824491850138409});
  printIp(std::string{"127.0.0.1"});
  printIp(std::vector<int>{127, 0, 0, 1});
  printIp(std::list<char>{'1', '0', '0', '1'});

  return 0;
}
