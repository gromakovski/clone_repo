
#include <iostream>

int main(int argc, char const *argv[]) {
  int k, n;
  std::cin >> k >> n;
  int totalVenicles = 0;
  for (int i = 0; i < n; i++) {
    int incomingVenicles = 0;
    std::cin >> incomingVenicles;
    totalVenicles += incomingVenicles;
    // std::cout << totalVenicles << std::endl;
    if (totalVenicles >= k)
      totalVenicles = totalVenicles - k;
    else
      totalVenicles = 0;
    // std::cout << totalVenicles << std::endl;
  }
  std::cout << totalVenicles;

  return 0;
}
