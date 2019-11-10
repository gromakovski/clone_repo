

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

std::multiset<std::string> submits;

void findSpamers(std::multiset<std::string>& submits) {
  std::multiset<std::string>::iterator result = submits.begin();
  while (true) {
    result = std::adjacent_find(result, submits.end());

    if (result == submits.end()) return;

    std::string aqq = *result;
    std::cout << aqq << std::endl;
    //итерируемся до окончания повторяющихся данных
    while (*result == aqq) {
      result++;
    }
  }
}

int main(int argc, char const* argv[]) {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::string accountName;
    std::cin >> accountName;
    submits.insert(accountName);
  }

  // test
  // submits = {"naucoder", "iceman", "abikbaev", "abikbaev", "petr",
  //           "abikbaev", "x",      "abikbaev", "acrush",   "x"};

  findSpamers(submits);

  return 0;
}
