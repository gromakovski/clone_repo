
#include <algorithm>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  int a, b, c;
  std::cin >> a >> b >> c;

  std::vector<int> v{a, b, c};
  std::sort(v.begin(), v.end());

  if (v.at(1) == 0 || v.at(1) == 1)
    std::cout << v.at(0) - v.at(1) - v.at(2);
  else
    std::cout << v.at(0) - (v.at(1) * v.at(2));

  return 0;
}
