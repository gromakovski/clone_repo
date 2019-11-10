

#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <vector>

std::vector<int> teacherDates;
std::vector<int> studentDates;

//вариант с итерацией по списку студента
int findNumbersStudentsLoop(std::vector<int>& teacherDates,
                            std::vector<int> studentDates) {
  int numbers = 0;
  for (auto& date : studentDates) {
    numbers +=
        std::binary_search(teacherDates.begin(), teacherDates.end(), date);
  }
  return numbers;
}
//вариант с итерацией по списку преподавателя
int findNumbersTeacherLoop(std::vector<int>& teacherDates,
                           std::vector<int> studentDates) {
  std::sort(studentDates.begin(), studentDates.end());

  int numbers = 0;
  for (auto& date : teacherDates) {
    auto res = std::equal_range(studentDates.begin(), studentDates.end(), date);

    numbers += std::distance(res.first, res.second);
  }
  return numbers;
}

int main(int argc, char const* argv[]) {
  teacherDates.reserve(15500);
  studentDates.reserve(1000001);
  std::ios_base::sync_with_stdio(false);
  int n;
  std::cin >> n;
  int date;
  for (int i = 0; i < n; i++) {
    std::cin >> date;
    if (teacherDates.back() != date) {
      teacherDates.push_back(date);
    }
  }
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::cin >> date;
    studentDates.push_back(date);
  }

  std::cout << findNumbersStudentsLoop(teacherDates, studentDates);

  return 0;
}
