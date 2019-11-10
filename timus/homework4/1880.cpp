
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

int main(int argc, char const* argv[]) {
  std::vector<int> numbers;
  for (int i = 0; i < 3; i++) {
    int n;
    std::cin >> n;
    int number;
    for (int j = 0; j < n; j++) {
      std::cin >> number;
      numbers.push_back(number);
    }
  }

  std::sort(numbers.begin(), numbers.end());

  //копируем уникальные элементы в отдельный вектор
  std::vector<int> uniqueNumbers;
  std::unique_copy(numbers.begin(), numbers.end(),
                   std::back_inserter(uniqueNumbers));

  //ищем последовательности из 3 одинаковых лементов из списка уникальных
  //элементов
  int total = 0;
  for (int elem : uniqueNumbers) {
    auto it = std::search_n(std::begin(numbers), std::end(numbers), 3, elem);
    if (it != std::end(numbers)) {
      total++;
    }
  }

  std::cout << total << std::endl;

  return 0;
}

////примитивный вариант решения
// int main(int argc, char const* argv[]) {
//  std::vector<int> numbers1;
//  std::vector<int> numbers2;
//  ////////////////
//  int n;
//  std::cin >> n;
//  int number;
//  for (int j = 0; j < n; j++) {
//    std::cin >> number;
//    numbers1.push_back(number);
//  }
//  /////////////////
//  std::cin >> n;
//  for (int j = 0; j < n; j++) {
//    std::cin >> number;
//    // std::cout << number << std::endl;
//    numbers2.push_back(number);
//  }
//  /////////
//  int total = 0;
//  std::cin >> n;
//  for (int j = 0; j < n; j++) {
//    std::cin >> number;
//    // std::cout << number << std::endl;
//    auto result1 = std::find(numbers1.begin(), numbers1.end(), number);
//    auto result2 = std::find(numbers2.begin(), numbers2.end(), number);
//    if (result1 != numbers1.end() && result2 != numbers2.end()) {
//      total++;
//    }
//  }

//  std::cout << total;

//  return 0;
//}
