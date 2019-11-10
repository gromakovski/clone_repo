
#include <iostream>
#include <vector>

//функция делает 8 возможных ходов конем
//и если ход не выходит за пределы шахматной доски,
//инкрементирует счетчик успешных ходов - total
int testHorse(char letter, int number) {
  int total = 0;
  if (number + 2 <= 8 && letter + 1 <= 'h') total++;  //вверх
  if (number + 2 <= 8 && letter - 1 >= 'a') total++;  //вверх

  if (number - 2 >= 1 && letter + 1 <= 'h') total++;  //вниз
  if (number - 2 >= 1 && letter - 1 >= 'a') total++;  //вниз

  if (letter - 2 >= 'a' && number + 1 <= 8) total++;  //влево
  if (letter - 2 >= 'a' && number - 1 >= 1) total++;  //влево

  if (letter + 2 <= 'h' && number + 1 <= 8) total++;  //вправо
  if (letter + 2 <= 'h' && number - 1 >= 1) total++;  //вправо

  return total;
}

int main(int argc, char const *argv[]) {
  int n;
  std::vector<std::pair<char, int>> cells;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    std::string cell;
    std::cin >> cell;
    cells.push_back(std::make_pair<char &, int>(cell[0], atoi(&cell[1])));
  }

  for (auto cell : cells)
    std::cout << testHorse(cell.first, cell.second) << std::endl;

  return 0;
}
