
#include <iostream>

int main(int argc, char const *argv[]) {
  int a1, b1;
  int a2, b2;
  int a3, b3;
  std::cin >> a1 >> b1;
  std::cin >> a2 >> b2;
  std::cin >> a3 >> b3;

  int berrysA = a1 - a3;
  int berrysB = b1 - b2;
  std::cout << berrysA << " " << berrysB;

  return 0;
}
