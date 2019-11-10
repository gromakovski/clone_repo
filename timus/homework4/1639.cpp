
#include <iostream>

int main(int argc, char const *argv[]) {
  int width, height;
  std::cin >> width >> height;

  int res = width * height - 1;

  if (res % 2 != 0)
    std::cout << "[:=[first]";
  else
    std::cout << "[second]=:]";

  return 0;
}
