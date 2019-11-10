
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

std::vector<std::string> sequences;

int main(int argc, char const *argv[]) {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::string seq;
    std::cin >> seq;
    sequences.emplace_back(seq);
  }
  std::string letter;
  std::cin >> letter;

  //простой вариант
  for (auto seq : sequences) {
    if (seq.find(letter) == 0) {
      std::cout << seq << std::endl;
    }
  }

  return 0;
}
