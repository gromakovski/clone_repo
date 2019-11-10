
#include <iostream>

int main(int argc, char const *argv[]) {
  int a, b;
  std::cin >> a >> b;

  int bottlesCount = (a + b) - 1;
  std::cout << bottlesCount - a << " " << bottlesCount - b << std::endl;

  return 0;
}
